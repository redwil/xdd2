/* Copyright (C) 1992-2010 I/O Performance, Inc. and the
 * United States Departments of Energy (DoE) and Defense (DoD)
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program in a file named 'Copying'; if not, write to
 * the Free Software Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139.
 */
/* Principal Author:
 *      Tom Ruwart (tmruwart@ioperformance.com)
 * Contributing Authors:
 *       Steve Hodson, DoE/ORNL, (hodsonsw@ornl.gov)
 *       Steve Poole, DoE/ORNL, (spoole@ornl.gov)
 *       Bradly Settlemyer, DoE/ORNL (settlemyerbw@ornl.gov)
 *       Russell Cattelan, Digital Elves (russell@thebarn.com)
 *       Alex Elder
 * Funding and resources provided by:
 * Oak Ridge National Labs, Department of Energy and Department of Defense
 *  Extreme Scale Systems Center ( ESSC ) http://www.csm.ornl.gov/essc/
 *  and the wonderful people at I/O Performance, Inc.
 */

#ifdef HAVE_SCHED_H
#include <sched.h>
#endif

#define HOSTNAMELENGTH 1024

#define	E2E_ADDRESS_TABLE_ENTRIES 16
struct xdd_e2e_header {
	uint32_t 	magic;  			/**< Magic number */
	int32_t  	sendqnum;  			/**< Sender's QThread Number  */
	int64_t  	sequence; 			/**< Sequence number */
	nclk_t  	sendtime; 			/**< Time this packet was sent in global nano seconds */
	nclk_t  	recvtime; 			/**< Time this packet was received in global nano seconds */
	int64_t  	location; 			/**< Starting location in bytes for this operation relative to the beginning of the file*/
	int64_t  	length;  			/**< Length of the user data in bytes this operation */
};
typedef struct xdd_e2e_header xdd_e2e_header_t;

struct xdd_e2e_address_table_entry {
    char 	*address;					// Pointer to the ASCII string of the address 
    char 	hostname[HOSTNAMELENGTH];	// the ASCII string of the hostname associated with address 
    int	 	base_port;					// The Base Port number associated with this address entry
    int	 	port_count;					// Number of ports from "port" to "port+nports-1"
#if (HAVE_CPU_SET_T)
    cpu_set_t cpu_set;
#endif
};
typedef struct xdd_e2e_address_table_entry xdd_e2e_ate_t;
struct xdd_e2e_address_table {
	int		number_of_entries;		// Number of address table entries
	struct	xdd_e2e_address_table_entry e2eat_entry[1];
};
typedef struct xdd_e2e_address_table xdd_e2e_at_t;

// Things used in the various end_to_end subroutines.
#ifdef FD_SETSIZE
#undef FD_SETSIZE
#define FD_SETSIZE 128
#endif

#define MAXMIT_TCP     (1<<28)

// -------------------------------------------------------------------
// The xdd_e2e structure contains variables that are referenced by the 
// target thread and qthreads. 
//
struct xdd_e2e {
	char				*e2e_dest_hostname; 	// Name of the Destination machine 
	char				*e2e_src_hostname; 		// Name of the Source machine 
	char				*e2e_src_file_path;     // Full path of source file for destination restart file 
	time_t				e2e_src_file_mtime;     // stat -c %Y *e2e_src_file_path, i.e., last modification time
	in_addr_t			e2e_dest_addr;  		// Destination Address number of the E2E socket 
	in_port_t			e2e_dest_port;  		// Port number to use for the E2E socket 
	int32_t				e2e_sd;   				// Socket descriptor for the E2E message port 
	int32_t				e2e_nd;   				// Number of Socket descriptors in the read set 
	sd_t				e2e_csd[FD_SETSIZE];	// Client socket descriptors 
	fd_set				e2e_active;  			// This set contains the sockets currently active 
	fd_set				e2e_readset; 			// This set is passed to select() 
	struct sockaddr_in  e2e_sname; 				// used by setup_server_socket 
	uint32_t			e2e_snamelen; 			// the length of the socket name 
	struct sockaddr_in  e2e_rname; 				// used by destination machine to remember the name of the source machine 
	uint32_t			e2e_rnamelen; 			// the length of the source socket name 
	int32_t				e2e_current_csd; 		// the current csd used by the select call on the destination side
	int32_t				e2e_next_csd; 			// The next available csd to use 
	int32_t				e2e_iosize;   			// Number of bytes per End to End request - size of data buffer plus size of E2E Header
	int32_t				e2e_send_status; 		// Current Send Status
	int32_t				e2e_recv_status; 		// Current Recv status
#define PTDS_E2E_MAGIC 	0x07201959 				// The magic number that should appear at the beginning of each message 
#define PTDS_E2E_MAGIQ 	0x07201960 				// The magic number that should appear in a message signaling destination to quit 
	xdd_e2e_header_t 	e2e_header;				// Header (actually a trailer) in the data packet of each message sent/received
	int64_t				e2e_msg_sequence_number;// The Message Sequence Number of the most recent message sent or to be received
	int32_t				e2e_msg_sent; 			// The number of messages sent 
	int32_t				e2e_msg_recv; 			// The number of messages received 
	int64_t				e2e_prev_loc; 			// The previous location from a e2e message from the source 
	int64_t				e2e_prev_len; 			// The previous length from a e2e message from the source 
	int64_t				e2e_data_recvd; 		// The amount of data that is received each time we call xdd_e2e_dest_recv()
	int64_t				e2e_data_length; 		// The amount of data that is ready to be read for this operation 
	int64_t				e2e_total_bytes_written; // The total amount of data written across all restarts for this file
	nclk_t				e2e_wait_1st_msg;		// Time in nanosecs destination waited for 1st source data to arrive 
	nclk_t				e2e_first_packet_received_this_pass;// Time that the first packet was received by the destination from the source
	nclk_t				e2e_last_packet_received_this_pass;// Time that the last packet was received by the destination from the source
	nclk_t				e2e_first_packet_received_this_run;// Time that the first packet was received by the destination from the source
	nclk_t				e2e_last_packet_received_this_run;// Time that the last packet was received by the destination from the source
	nclk_t				e2e_sr_time; 			// Time spent sending or receiving data for End-to-End operation
	int32_t				e2e_address_table_host_count;	// Cumulative number of hosts represented in the e2e address table
	int32_t				e2e_address_table_port_count;	// Cumulative number of ports represented in the e2e address table
	int32_t				e2e_address_table_next_entry;	// Next available entry in the e2e_address_table
	xdd_e2e_ate_t		e2e_address_table[E2E_ADDRESS_TABLE_ENTRIES]; // Used by E2E to stripe over multiple IP Addresses
}; // End of struct xdd_e2e definition
typedef struct xdd_e2e xdd_e2e_t;

/*
 * Local variables:
 *  indent-tabs-mode: t
 *  default-tab-width: 4
 *  c-indent-level: 4
 *  c-basic-offset: 4
 * End:
 *
 * vim: ts=4 sts=4 sw=4 noexpandtab
 */