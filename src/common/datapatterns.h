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

struct xdd_data_pattern {
	unsigned char		*data_pattern; 				// Data pattern for write operations for each target - 
													//      This is the ASCII string representation of the pattern 
	unsigned char		*data_pattern_value; 		// This is the 64-bit hex value  
	size_t				data_pattern_length; 		// Length of ASCII data pattern for write operations for each target 
	unsigned char		*data_pattern_prefix; 		// Data pattern prefix which is a string of hex digits less than 8 bytes (16 nibbles) 
	size_t				data_pattern_prefix_length; // Data pattern prefix 
	unsigned char		*data_pattern_prefix_value; // This is the N-bit prefix value fully shifted to the right 
	uint64_t			data_pattern_prefix_binary; // This is the 64-bit prefix value fully shifted to the left 
	unsigned char		*data_pattern_name; 		// Data pattern name which is an ASCII string  
	int32_t				data_pattern_name_length;	// Length of the data pattern name string 
	char				*data_pattern_filename; 	// Name of a file that contains a data pattern to use 
	int64_t				data_pattern_compare_errors;	// Number of content/sequence compare errors from the verify() subroutines
}; 
typedef struct xdd_data_pattern xdd_data_pattern_t;
#ifdef XDD_DATA_PATTERN
/*----------------------------------------------------------------------------*/
/* 
 * Various data patterns for 8b10b testing
 */
unsigned char lfpat[]={    0xab,0xab,0xab,0xab, 0xab,0xab,0xab,0xab, 0xab,0xab,0xab,0xab, 0xab,0xab,0xab,0xab, // Need a bunch 0xab bytes 
                           0xab,0xab,0xab,0xab, 0xab,0xab,0xab,0xab, 0xab,0xab,0xab,0xab, 0xab,0xab,0xab,0xab, // 
                           0xab,0xab,0xab,0xab, 0xab,0xab,0xab,0xab, 0xab,0xab,0xab,0xab, 0xab,0xab,0xab,0xab, // 
                           0xab,0xab,0xab,0xab, 0xab,0xab,0xab,0xab, 0xab,0xab,0xab,0xab, 0xab,0xab,0xab,0xab, // 
                           0xab,0xab,0xab,0xab, 0xab,0xab,0xab,0xab, 0xab,0xab,0xab,0xab, 0xab,0xab,0xab,0xab, // 
                           0xab,0xab,0xab,0xab, 0xab,0xab,0xab,0xab, 0xab,0xab,0xab,0xab, 0xab,0xab,0xab,0xab, // 
                           0xab,0xab,0xab,0xab, 0xab,0xab,0xab,0xab, 0xab,0xab,0xab,0xab, 0xab,0xab,0xab,0xab, // 
                           0xab,0xab,0xab,0xab, 0xab,0xab,0xab,0xab, 0xab,0xab,0xab,0xab, 0xab,0xab,0xab,0xab, // 

                           0xeb,0x54,0x54,0x54, 0x54,0x54,0x54,0x54, 0x54,0x54,0x54,0x54, 0x54,0x54,0x54,0x54, // need a bunch of 0x54 bytes
                           0x54,0x54,0x54,0x54, 0x54,0x54,0x54,0x54, 0x54,0x54,0x54,0x54, 0x54,0x54,0x54,0x54, // 
                           0x54,0x54,0x54,0x54, 0x54,0x54,0x54,0x54, 0x54,0x54,0x54,0x54, 0x54,0x54,0x54,0x54, // 
                           0x54,0x54,0x54,0x54, 0x54,0x54,0x54,0x54, 0x54,0x54,0x54,0x54, 0x54,0x54,0x54,0x54, // 
                           0x54,0x54,0x54,0x54, 0x54,0x54,0x54,0x54, 0x54,0x54,0x54,0x54, 0x54,0x54,0x54,0x54, // 
                           0x54,0x54,0x54,0x54, 0x54,0x54,0x54,0x54, 0x54,0x54,0x54,0x54, 0x54,0x54,0x54,0x54, // 
                           0x54,0x54,0x54,0x54, 0x54,0x54,0x54,0x54, 0x54,0x54,0x54,0x54, 0x54,0x54,0x54,0x54, // 
                           0x54,0x54,0x54,0x54, 0x54,0x54,0x54,0x54, 0x54,0x54,0x54,0x54, 0x54,0xf4,0xab,0xab
}; // End of lfpat
unsigned char ltpat[] = {  0xee,0xfe,0xc7,0xf1, 0xfe,0x27,0x7e,0x7e, 0x7e,0x7e,0x7e,0x7e, 0xfc,0xe3,0xfc,0xe3, // Need a bunch of these - should be 512 bytes total
                           0x7e,0x7e,0x7e,0x7e, 0x7e,0x7e,0x7e,0x7e, 0x7e,0x7e,0x7e,0x7e, 0x7e,0x7e,0x7e,0x7e, //
                           0x7e,0x7e,0x7e,0x7e, 0x7e,0x7e,0x7e,0x7e, 0x7e,0x7e,0x7e,0x7e, 0x7e,0x7e,0x7e,0x7e, //
                           0x7e,0x7e,0x7e,0x7e, 0x7e,0x7e,0x7e,0x7e, 0x7e,0x7e,0x7e,0x7e, 0x7e,0x7e,0x7e,0x7e, //
                           0x7e,0x7e,0x7e,0x7e, 0x7e,0x7e,0x7e,0x7e, 0x7e,0x7e,0x7e,0x7e, 0x7e,0x7e,0x7e,0x7e, //
                           0x7e,0x7e,0x7e,0x7e, 0x7e,0x7e,0x7e,0x7e, 0x7e,0x7e,0x7e,0x7e, 0x7e,0x7e,0x7e,0x7e, //
                           0x7e,0x7e,0x7e,0x7e, 0x7e,0x7e,0x7e,0x7e, 0x7e,0x7e,0x7e,0x7e, 0x7e,0x7e,0x7e,0x7e, //
                           0x7e,0x7e,0x7e,0x7e, 0x7e,0x7e,0x7e,0x7e, 0x7e,0x7e,0x7e,0x7e, 0x7e,0x7e,0x7e,0x7e, //
                           0x7e,0x7e,0x7e,0x7e, 0x7e,0x7e,0x7e,0x7e, 0x7e,0x7e,0x7e,0x7e, 0x7e,0x7e,0x7e,0x7e, //
                           0x7e,0x7e,0x7e,0x7e, 0x7e,0x7e,0x7e,0x7e, 0x7e,0x7e,0x7e,0x7e, 0x7e,0x7e,0x7e,0x7e, //
                           0x7e,0x7e,0x7e,0x7e, 0x7e,0x7e,0x7e,0x7e, 0x7e,0x7e,0x7e,0x7e, 0x7e,0x7e,0x7e,0x7e, //
                           0x7e,0x7e,0x7e,0x7e, 0x7e,0x7e,0x7e,0x7e, 0x7e,0x7e,0x7e,0x7e, 0x7e,0x7e,0x7e,0x7e, //
                           0x7e,0x7e,0x7e,0x7e, 0x7e,0x7e,0x7e,0x7e, 0x7e,0x7e,0x7e,0x7e, 0x7e,0x7e,0x7e,0x7e, //
                           0x7e,0x7e,0x7e,0x7e, 0x7e,0x7e,0x7e,0x7e, 0x7e,0x7e,0x7e,0x7e, 0x7e,0x7e,0x7e,0x7e, //
                           0x7e,0x7e,0x7e,0x7e, 0x7e,0x7e,0x7e,0x7e, 0x7e,0x7e,0x7e,0x7e, 0x7e,0x7e,0x7e,0x7e, //
                           0x7e,0x7e,0x7e,0x7e, 0x7e,0x7e,0x7e,0x7e, 0x7e,0x7e,0x7e,0x7e, 0x7e,0x7e,0x7e,0x7e, //
                           0x7e,0x7e,0x7e,0x7e, 0x7e,0x7e,0x7e,0x7e, 0x7e,0x7e,0x7e,0x7e, 0x7e,0x7e,0x7e,0x7e, //
                           0x7e,0x7e,0x7e,0x7e, 0x7e,0x7e,0x7e,0x7e, 0x7e,0x7e,0x7e,0x7e, 0x7e,0x7e,0x7e,0x7e, //
                           0x7e,0x7e,0x7e,0x7e, 0x7e,0x7e,0x7e,0x7e, 0x7e,0x7e,0x7e,0x7e, 0x7e,0x7e,0x7e,0x7e, //
                           0x7e,0x7e,0x7e,0x7e, 0x7e,0x7e,0x7e,0x7e, 0x7e,0x7e,0x7e,0x7e, 0x7e,0x7e,0x7e,0x7e, //
                           0x7e,0x7e,0x7e,0x7e, 0x7e,0x7e,0x7e,0x7e, 0x7e,0x7e,0x7e,0x7e, 0x7e,0x7e,0x7e,0x7e, //
                           0x7e,0x7e,0x7e,0x7e, 0x7e,0x7e,0x7e,0x7e, 0x7e,0x7e,0x7e,0x7e, 0x7e,0x7e,0x7e,0x7e, //
                           0x7e,0x7e,0x7e,0x7e, 0x7e,0x7e,0x7e,0x7e, 0x7e,0x7e,0x7e,0x7e, 0x7e,0x7e,0x7e,0x7e, //
                           0x7e,0x7e,0x7e,0x7e, 0x7e,0x7e,0x7e,0x7e, 0x7e,0x7e,0x7e,0x7e, 0x7e,0x7e,0x7e,0x7e, //
                           0x7e,0x7e,0x7e,0x7e, 0x7e,0x7e,0x7e,0x7e, 0x7e,0x7e,0x7e,0x7e, 0x7e,0x7e,0x7e,0x7e, //
                           0x7e,0x7e,0x7e,0x7e, 0x7e,0x7e,0x7e,0x7e, 0x7e,0x7e,0x7e,0x7e, 0x7e,0x7e,0x7e,0x7e, //
                           0x7e,0x7e,0x7e,0x7e, 0x7e,0x7e,0x7e,0x7e, 0x7e,0x7e,0x7e,0x7e, 0x7e,0x7e,0x7e,0x7e, //
                           0x7e,0x7e,0x7e,0x7e, 0x7e,0x7e,0x7e,0x7e, 0x7e,0x7e,0x7e,0x7e, 0x7e,0x7e,0x7e,0x7e, //
                           0x7e,0x7e,0x7e,0x7e, 0x7e,0x7e,0x7e,0x7e, 0x7e,0x7e,0x7e,0x7e, 0x7e,0x7e,0x7e,0x7e, //
                           0x7e,0x7e,0x7e,0x7e, 0x7e,0x7e,0x7e,0x7e, 0x7e,0x7e,0x7e,0x7e, 0x7e,0x7e,0x7e,0x7e, //
                           0x7e,0x7e,0x7e,0x7e, 0x7e,0x7e,0x7e,0x7e, 0x7e,0x7e,0x7e,0x7e, 0x7e,0x7e,0x7e,0x7e, //
                           0x7e,0x7e,0x7e,0x7e, 0x7e,0x7e,0x7e,0x7e, 0x7e,0x7e,0x7e,0x7e, 0xfc,0xe3,0xfc,0xe3  // 
}; // End of ltpat
unsigned char cjtpat[] = { 0xbc,0x95,0xb5,0xb5, 0xbc,0x95,0xb5,0xb5, 0xbc,0x95,0xb5,0xb5, 0xbc,0x95,0xb5,0xb5, 0xbc,0x95,0xb5,0xb5, 0xbc,0x95,0xb5,0xb5, // 6 Idle Primitives
                           0xbc,0xb5,0x36,0x36, // SOFn3 Pimitive
                           0x7e,0x7e,0x7e,0x7e, 0x7e,0x7e,0x7e,0x7e, 0x7e,0x7e,0x7e,0x7e, 0x7e,0x7e,0x7e,0x7e, // 4 Low Density transition pattern
                           0x7e,0x7e,0x7e,0x7e, 0x7e,0x7e,0x7e,0x7e, 0x7e,0x7e,0x7e,0x7e, 0x7e,0x7e,0x7e,0x7e, // 8
                           0x7e,0x7e,0x7e,0x7e, 0x7e,0x7e,0x7e,0x7e, 0x7e,0x7e,0x7e,0x7e, 0x7e,0x7e,0x7e,0x7e, //16
                           0x7e,0x7e,0x7e,0x7e, 0x7e,0x7e,0x7e,0x7e, 0x7e,0x7e,0x7e,0x7e, 0x7e,0x7e,0x7e,0x7e, //20
                           0x7e,0x7e,0x7e,0x7e, 0x7e,0x7e,0x7e,0x7e, 0x7e,0x7e,0x7e,0x7e, 0x7e,0x7e,0x7e,0x7e, //24
                           0x7e,0x7e,0x7e,0x7e, 0x7e,0x7e,0x7e,0x7e, 0x7e,0x7e,0x7e,0x7e, 0x7e,0x7e,0x7e,0x7e, //28
                           0x7e,0x7e,0x7e,0x7e, 0x7e,0x7e,0x7e,0x7e, 0x7e,0x7e,0x7e,0x7e, 0x7e,0x7e,0x7e,0x7e, //32
                           0x7e,0x7e,0x7e,0x7e, 0x7e,0x7e,0x7e,0x7e, 0x7e,0x7e,0x7e,0x7e, 0x7e,0x7e,0x7e,0x7e, //36
                           0x7e,0x7e,0x7e,0x7e, 0x7e,0x7e,0x7e,0x7e, 0x7e,0x7e,0x7e,0x7e, 0x7e,0x7e,0x7e,0x7e, //40
                           0x7e,0x7e,0x7e,0x7e, // 41
                           0x7e,0x7e,0x7e,0x74, 0x7e,0xab,0xb5,0xb5, // Transition from low to high transition densities
                           0xb5,0xb5,0xb5,0xb5, 0xb5,0xb5,0xb5,0xb5, 0xb5,0xb5,0xb5,0xb5, 0xb5,0xb5,0xb5,0xb5, // High density transition density pattern
                           0xb5,0xb5,0xb5,0xb5, 0xb5,0xb5,0xb5,0xb5, 0xb5,0xb5,0xb5,0xb5, 0xb5,0xb5,0xb5,0xb5, //8
                           0xb5,0xb5,0xb5,0xb5, 0xb5,0xb5,0xb5,0xb5, 0xb5,0xb5,0xb5,0xb5, 0xb5,0xb5,0xb5,0xb5, //12
                           0xb5,0x5e,0x4a,0x7e, 0x7e,0x7e,0x7e,0xfe, // Transitioning from high to low densities
                           0xf5,0x2e,0xf6,0xdd, // CRC 
                           0xbc,0xb5,0xd5,0xd5  // EOFn
}; // End of cjtpat 
unsigned char crpat[] =  { 0xbc,0x95,0xb5,0xb5, 0xbc,0x95,0xb5,0xb5, 0xbc,0x95,0xb5,0xb5, 0xbc,0x95,0xb5,0xb5, 0xbc,0x95,0xb5,0xb5, 0xbc,0x95,0xb5,0xb5, // 6 Idle Primitives
                           0xbc,0xb5,0x36,0x36, // SOFn3 Pimitive
                           0xbe,0xd7,0x23,0x47, 0x6b,0x8f,0xb3,0x14, 0x5e,0xfb,0x35,0x59, // modified RPAT pattern repeated 16 times
                           0xbe,0xd7,0x23,0x47, 0x6b,0x8f,0xb3,0x14, 0x5e,0xfb,0x35,0x59, // 
                           0xbe,0xd7,0x23,0x47, 0x6b,0x8f,0xb3,0x14, 0x5e,0xfb,0x35,0x59, // 
                           0xbe,0xd7,0x23,0x47, 0x6b,0x8f,0xb3,0x14, 0x5e,0xfb,0x35,0x59, // 
                           0xbe,0xd7,0x23,0x47, 0x6b,0x8f,0xb3,0x14, 0x5e,0xfb,0x35,0x59, // 
                           0xbe,0xd7,0x23,0x47, 0x6b,0x8f,0xb3,0x14, 0x5e,0xfb,0x35,0x59, // 
                           0xbe,0xd7,0x23,0x47, 0x6b,0x8f,0xb3,0x14, 0x5e,0xfb,0x35,0x59, // 
                           0xbe,0xd7,0x23,0x47, 0x6b,0x8f,0xb3,0x14, 0x5e,0xfb,0x35,0x59, // 
                           0xbe,0xd7,0x23,0x47, 0x6b,0x8f,0xb3,0x14, 0x5e,0xfb,0x35,0x59, // 
                           0xbe,0xd7,0x23,0x47, 0x6b,0x8f,0xb3,0x14, 0x5e,0xfb,0x35,0x59, // 
                           0xbe,0xd7,0x23,0x47, 0x6b,0x8f,0xb3,0x14, 0x5e,0xfb,0x35,0x59, // 
                           0xbe,0xd7,0x23,0x47, 0x6b,0x8f,0xb3,0x14, 0x5e,0xfb,0x35,0x59, // 
                           0xbe,0xd7,0x23,0x47, 0x6b,0x8f,0xb3,0x14, 0x5e,0xfb,0x35,0x59, // 
                           0xbe,0xd7,0x23,0x47, 0x6b,0x8f,0xb3,0x14, 0x5e,0xfb,0x35,0x59, // 
                           0xbe,0xd7,0x23,0x47, 0x6b,0x8f,0xb3,0x14, 0x5e,0xfb,0x35,0x59, // 
                           0xbe,0xd7,0x23,0x47, 0x6b,0x8f,0xb3,0x14, 0x5e,0xfb,0x35,0x59, // 
                           0xee,0x23,0x55,0x16, // CRC
                           0xbc,0xb5,0xd5,0xd5  // EOFn
}; // End of crpat 
unsigned char cspat[] =  { 0xbc,0x95,0xb5,0xb5, 0xbc,0x95,0xb5,0xb5, 0xbc,0x95,0xb5,0xb5, 0xbc,0x95,0xb5,0xb5, 0xbc,0x95,0xb5,0xb5, 0xbc,0x95,0xb5,0xb5, // 6 Idle Primitives
                           0xbc,0xb5,0x36,0x36, // SOFn3 Pimitive
                           0x7f,0x7f,0x7f,0x7f, 0x7f,0x7f,0x7f,0x7f, 0x7f,0x7f,0x7f,0x7f, 0x7f,0x7f,0x7f,0x7f, // Supply noise pattern = 2012 bytes
                           0x7f,0x7f,0x7f,0x7f, 0x7f,0x7f,0x7f,0x7f, 0x7f,0x7f,0x7f,0x7f, 0x7f,0x7f,0x7f,0x7f, // 
                           0x7f,0x7f,0x7f,0x7f, 0x7f,0x7f,0x7f,0x7f, 0x7f,0x7f,0x7f,0x7f, 0x7f,0x7f,0x7f,0x7f, // 
                           0x7f,0x7f,0x7f,0x7f, 0x7f,0x7f,0x7f,0x7f, 0x7f,0x7f,0x7f,0x7f, 0x7f,0x7f,0x7f,0x7f, // 
                           0x7f,0x7f,0x7f,0x7f, 0x7f,0x7f,0x7f,0x7f, 0x7f,0x7f,0x7f,0x7f, 0x7f,0x7f,0x7f,0x7f, // 
                           0x7f,0x7f,0x7f,0x7f, 0x7f,0x7f,0x7f,0x7f, 0x7f,0x7f,0x7f,0x7f, 0x7f,0x7f,0x7f,0x7f, // 
                           0x7f,0x7f,0x7f,0x7f, 0x7f,0x7f,0x7f,0x7f, 0x7f,0x7f,0x7f,0x7f, 0x7f,0x7f,0x7f,0x7f, // 
                           0x7f,0x7f,0x7f,0x7f, 0x7f,0x7f,0x7f,0x7f, 0x7f,0x7f,0x7f,0x7f, 0x7f,0x7f,0x7f,0x7f, // 
                           0x7f,0x7f,0x7f,0x7f, 0x7f,0x7f,0x7f,0x7f, 0x7f,0x7f,0x7f,0x7f, 0x7f,0x7f,0x7f,0x7f, // 
                           0x7f,0x7f,0x7f,0x7f, 0x7f,0x7f,0x7f,0x7f, 0x7f,0x7f,0x7f,0x7f, 0x7f,0x7f,0x7f,0x7f, // 
                           0x7f,0x7f,0x7f,0x7f, 0x7f,0x7f,0x7f,0x7f, 0x7f,0x7f,0x7f,0x7f, 0x7f,0x7f,0x7f,0x7f, // 
                           0x7f,0x7f,0x7f,0x7f, 0x7f,0x7f,0x7f,0x7f, 0x7f,0x7f,0x7f,0x7f, 0x7f,0x7f,0x7f,0x7f, // 
                           0x7f,0x7f,0x7f,0x7f, 0x7f,0x7f,0x7f,0x7f, 0x7f,0x7f,0x7f,0x7f, 0x7f,0x7f,0x7f,0x7f, // 
                           0x7f,0x7f,0x7f,0x7f, 0x7f,0x7f,0x7f,0x7f, 0x7f,0x7f,0x7f,0x7f, 0x7f,0x7f,0x7f,0x7f, // 
                           0x7f,0x7f,0x7f,0x7f, 0x7f,0x7f,0x7f,0x7f, 0x7f,0x7f,0x7f,0x7f, 0x7f,0x7f,0x7f,0x7f, // 
                           0x7f,0x7f,0x7f,0x7f, 0x7f,0x7f,0x7f,0x7f, 0x7f,0x7f,0x7f,0x7f, 0x7f,0x7f,0x7f,0x7f, // 
                           0x7f,0x7f,0x7f,0x7f, 0x7f,0x7f,0x7f,0x7f, 0x7f,0x7f,0x7f,0x7f, 0x7f,0x7f,0x7f,0x7f, // 
                           0x7f,0x7f,0x7f,0x7f, 0x7f,0x7f,0x7f,0x7f, 0x7f,0x7f,0x7f,0x7f, 0x7f,0x7f,0x7f,0x7f, // 
                           0x7f,0x7f,0x7f,0x7f, 0x7f,0x7f,0x7f,0x7f, 0x7f,0x7f,0x7f,0x7f, 0x7f,0x7f,0x7f,0x7f, // 
                           0x7f,0x7f,0x7f,0x7f, 0x7f,0x7f,0x7f,0x7f, 0x7f,0x7f,0x7f,0x7f, 0x7f,0x7f,0x7f,0x7f, // 
                           0x7f,0x7f,0x7f,0x7f, 0x7f,0x7f,0x7f,0x7f, 0x7f,0x7f,0x7f,0x7f, 0x7f,0x7f,0x7f,0x7f, // 
                           0x7f,0x7f,0x7f,0x7f, 0x7f,0x7f,0x7f,0x7f, 0x7f,0x7f,0x7f,0x7f, 0x7f,0x7f,0x7f,0x7f, // 
                           0x7f,0x7f,0x7f,0x7f, 0x7f,0x7f,0x7f,0x7f, 0x7f,0x7f,0x7f,0x7f, 0x7f,0x7f,0x7f,0x7f, // 
                           0x7f,0x7f,0x7f,0x7f, 0x7f,0x7f,0x7f,0x7f, 0x7f,0x7f,0x7f,0x7f, 0x7f,0x7f,0x7f,0x7f, // 
                           0x7f,0x7f,0x7f,0x7f, 0x7f,0x7f,0x7f,0x7f, 0x7f,0x7f,0x7f,0x7f, 0x7f,0x7f,0x7f,0x7f, // 
                           0x7f,0x7f,0x7f,0x7f, 0x7f,0x7f,0x7f,0x7f, 0x7f,0x7f,0x7f,0x7f, 0x7f,0x7f,0x7f,0x7f, // 
                           0x7f,0x7f,0x7f,0x7f, 0x7f,0x7f,0x7f,0x7f, 0x7f,0x7f,0x7f,0x7f, 0x7f,0x7f,0x7f,0x7f, // 
                           0x7f,0x7f,0x7f,0x7f, 0x7f,0x7f,0x7f,0x7f, 0x7f,0x7f,0x7f,0x7f, 0x7f,0x7f,0x7f,0x7f, // 
                           0x7f,0x7f,0x7f,0x7f, 0x7f,0x7f,0x7f,0x7f, 0x7f,0x7f,0x7f,0x7f, 0x7f,0x7f,0x7f,0x7f, // 
                           0x7f,0x7f,0x7f,0x7f, 0x7f,0x7f,0x7f,0x7f, 0x7f,0x7f,0x7f,0x7f, 0x7f,0x7f,0x7f,0x7f, // 
                           0x7f,0x7f,0x7f,0x7f, 0x7f,0x7f,0x7f,0x7f, 0x7f,0x7f,0x7f,0x7f, 0x7f,0x7f,0x7f,0x7f, // 
                           0x7f,0x7f,0x7f,0x7f, 0x7f,0x7f,0x7f,0x7f, 0x7f,0x7f,0x7f,0x7f, 0x7f,0x7f,0x7f,0x7f, // 
                           0x7f,0x7f,0x7f,0x7f, 0x7f,0x7f,0x7f,0x7f, 0x7f,0x7f,0x7f,0x7f, 0x7f,0x7f,0x7f,0x7f, // 
                           0x7f,0x7f,0x7f,0x7f, 0x7f,0x7f,0x7f,0x7f, 0x7f,0x7f,0x7f,0x7f, 0x7f,0x7f,0x7f,0x7f, // 
                           0x7f,0x7f,0x7f,0x7f, 0x7f,0x7f,0x7f,0x7f, 0x7f,0x7f,0x7f,0x7f, 0x7f,0x7f,0x7f,0x7f, // 
                           0x7f,0x7f,0x7f,0x7f, 0x7f,0x7f,0x7f,0x7f, 0x7f,0x7f,0x7f,0x7f, 0x7f,0x7f,0x7f,0x7f, // 
                           0x7f,0x7f,0x7f,0x7f, 0x7f,0x7f,0x7f,0x7f, 0x7f,0x7f,0x7f,0x7f, 0x7f,0x7f,0x7f,0x7f, // 
                           0x7f,0x7f,0x7f,0x7f, 0x7f,0x7f,0x7f,0x7f, 0x7f,0x7f,0x7f,0x7f, 0x7f,0x7f,0x7f,0x7f, // 
                           0x7f,0x7f,0x7f,0x7f, 0x7f,0x7f,0x7f,0x7f, 0x7f,0x7f,0x7f,0x7f, 0x7f,0x7f,0x7f,0x7f, // 
                           0x7f,0x7f,0x7f,0x7f, 0x7f,0x7f,0x7f,0x7f, 0x7f,0x7f,0x7f,0x7f, 0x7f,0x7f,0x7f,0x7f, // 
                           0x7f,0x7f,0x7f,0x7f, 0x7f,0x7f,0x7f,0x7f, 0x7f,0x7f,0x7f,0x7f, 0x7f,0x7f,0x7f,0x7f, // 
                           0x7f,0x7f,0x7f,0x7f, 0x7f,0x7f,0x7f,0x7f, 0x7f,0x7f,0x7f,0x7f, 0x7f,0x7f,0x7f,0x7f, // 
                           0x7f,0x7f,0x7f,0x7f, 0x7f,0x7f,0x7f,0x7f, 0x7f,0x7f,0x7f,0x7f, 0x7f,0x7f,0x7f,0x7f, // 
                           0x7f,0x7f,0x7f,0x7f, 0x7f,0x7f,0x7f,0x7f, 0x7f,0x7f,0x7f,0x7f, 0x7f,0x7f,0x7f,0x7f, // 
                           0x7f,0x7f,0x7f,0x7f, 0x7f,0x7f,0x7f,0x7f, 0x7f,0x7f,0x7f,0x7f, 0x7f,0x7f,0x7f,0x7f, // 
                           0x7f,0x7f,0x7f,0x7f, 0x7f,0x7f,0x7f,0x7f, 0x7f,0x7f,0x7f,0x7f, 0x7f,0x7f,0x7f,0x7f, // 
                           0x7f,0x7f,0x7f,0x7f, 0x7f,0x7f,0x7f,0x7f, 0x7f,0x7f,0x7f,0x7f, 0x7f,0x7f,0x7f,0x7f, // 
                           0x7f,0x7f,0x7f,0x7f, 0x7f,0x7f,0x7f,0x7f, 0x7f,0x7f,0x7f,0x7f, 0x7f,0x7f,0x7f,0x7f, // 
                           0x7f,0x7f,0x7f,0x7f, 0x7f,0x7f,0x7f,0x7f, 0x7f,0x7f,0x7f,0x7f, 0x7f,0x7f,0x7f,0x7f, // 
                           0x7f,0x7f,0x7f,0x7f, 0x7f,0x7f,0x7f,0x7f, 0x7f,0x7f,0x7f,0x7f, 0x7f,0x7f,0x7f,0x7f, // 
                           0x7f,0x7f,0x7f,0x7f, 0x7f,0x7f,0x7f,0x7f, 0x7f,0x7f,0x7f,0x7f, 0x7f,0x7f,0x7f,0x7f, // 
                           0x7f,0x7f,0x7f,0x7f, 0x7f,0x7f,0x7f,0x7f, 0x7f,0x7f,0x7f,0x7f, 0x7f,0x7f,0x7f,0x7f, // 
                           0x7f,0x7f,0x7f,0x7f, 0x7f,0x7f,0x7f,0x7f, 0x7f,0x7f,0x7f,0x7f, 0x7f,0x7f,0x7f,0x7f, // 
                           0x7f,0x7f,0x7f,0x7f, 0x7f,0x7f,0x7f,0x7f, 0x7f,0x7f,0x7f,0x7f, 0x7f,0x7f,0x7f,0x7f, // 
                           0x7f,0x7f,0x7f,0x7f, 0x7f,0x7f,0x7f,0x7f, 0x7f,0x7f,0x7f,0x7f, 0x7f,0x7f,0x7f,0x7f, // 
                           0x7f,0x7f,0x7f,0x7f, 0x7f,0x7f,0x7f,0x7f, 0x7f,0x7f,0x7f,0x7f, 0x7f,0x7f,0x7f,0x7f, // 
                           0x7f,0x7f,0x7f,0x7f, 0x7f,0x7f,0x7f,0x7f, 0x7f,0x7f,0x7f,0x7f, 0x7f,0x7f,0x7f,0x7f, // 
                           0x7f,0x7f,0x7f,0x7f, 0x7f,0x7f,0x7f,0x7f, 0x7f,0x7f,0x7f,0x7f, 0x7f,0x7f,0x7f,0x7f, // 
                           0x7f,0x7f,0x7f,0x7f, 0x7f,0x7f,0x7f,0x7f, 0x7f,0x7f,0x7f,0x7f, 0x7f,0x7f,0x7f,0x7f, // 
                           0x7f,0x7f,0x7f,0x7f, 0x7f,0x7f,0x7f,0x7f, 0x7f,0x7f,0x7f,0x7f, 0x7f,0x7f,0x7f,0x7f, // 
                           0x7f,0x7f,0x7f,0x7f, 0x7f,0x7f,0x7f,0x7f, 0x7f,0x7f,0x7f,0x7f, 0x7f,0x7f,0x7f,0x7f, // 
                           0x7f,0x7f,0x7f,0x7f, 0x7f,0x7f,0x7f,0x7f, 0x7f,0x7f,0x7f,0x7f, 0x7f,0x7f,0x7f,0x7f, // 
                           0x7f,0x7f,0x7f,0x7f, 0x7f,0x7f,0x7f,0x7f, 0x7f,0x7f,0x7f,0x7f, 0x7f,0x7f,0x7f,0x7f, // 
                           0x7f,0x7f,0x7f,0x7f, 0x7f,0x7f,0x7f,0x7f, 0x7f,0x7f,0x7f,0x7f, 0x7f,0x7f,0x7f,0x7f, // 
                           0x7f,0x7f,0x7f,0x7f, 0x7f,0x7f,0x7f,0x7f, 0x7f,0x7f,0x7f,0x7f, 0x7f,0x7f,0x7f,0x7f, // 
                           0x7f,0x7f,0x7f,0x7f, 0x7f,0x7f,0x7f,0x7f, 0x7f,0x7f,0x7f,0x7f, 0x7f,0x7f,0x7f,0x7f, // 
                           0x7f,0x7f,0x7f,0x7f, 0x7f,0x7f,0x7f,0x7f, 0x7f,0x7f,0x7f,0x7f, 0x7f,0x7f,0x7f,0x7f, // 
                           0x7f,0x7f,0x7f,0x7f, 0x7f,0x7f,0x7f,0x7f, 0x7f,0x7f,0x7f,0x7f, 0x7f,0x7f,0x7f,0x7f, // 
                           0x7f,0x7f,0x7f,0x7f, 0x7f,0x7f,0x7f,0x7f, 0x7f,0x7f,0x7f,0x7f, 0x7f,0x7f,0x7f,0x7f, // 
                           0x7f,0x7f,0x7f,0x7f, 0x7f,0x7f,0x7f,0x7f, 0x7f,0x7f,0x7f,0x7f, 0x7f,0x7f,0x7f,0x7f, // 
                           0x7f,0x7f,0x7f,0x7f, 0x7f,0x7f,0x7f,0x7f, 0x7f,0x7f,0x7f,0x7f, 0x7f,0x7f,0x7f,0x7f, // 
                           0x7f,0x7f,0x7f,0x7f, 0x7f,0x7f,0x7f,0x7f, 0x7f,0x7f,0x7f,0x7f, 0x7f,0x7f,0x7f,0x7f, // 
                           0x7f,0x7f,0x7f,0x7f, 0x7f,0x7f,0x7f,0x7f, 0x7f,0x7f,0x7f,0x7f, 0x7f,0x7f,0x7f,0x7f, // 
                           0x7f,0x7f,0x7f,0x7f, 0x7f,0x7f,0x7f,0x7f, 0x7f,0x7f,0x7f,0x7f, 0x7f,0x7f,0x7f,0x7f, // 
                           0x7f,0x7f,0x7f,0x7f, 0x7f,0x7f,0x7f,0x7f, 0x7f,0x7f,0x7f,0x7f, 0x7f,0x7f,0x7f,0x7f, // 
                           0x7f,0x7f,0x7f,0x7f, 0x7f,0x7f,0x7f,0x7f, 0x7f,0x7f,0x7f,0x7f, 0x7f,0x7f,0x7f,0x7f, // 
                           0x7f,0x7f,0x7f,0x7f, 0x7f,0x7f,0x7f,0x7f, 0x7f,0x7f,0x7f,0x7f, 0x7f,0x7f,0x7f,0x7f, // 
                           0x7f,0x7f,0x7f,0x7f, 0x7f,0x7f,0x7f,0x7f, 0x7f,0x7f,0x7f,0x7f, 0x7f,0x7f,0x7f,0x7f, // 
                           0x7f,0x7f,0x7f,0x7f, 0x7f,0x7f,0x7f,0x7f, 0x7f,0x7f,0x7f,0x7f, 0x7f,0x7f,0x7f,0x7f, // 
                           0x7f,0x7f,0x7f,0x7f, 0x7f,0x7f,0x7f,0x7f, 0x7f,0x7f,0x7f,0x7f, 0x7f,0x7f,0x7f,0x7f, // 
                           0x7f,0x7f,0x7f,0x7f, 0x7f,0x7f,0x7f,0x7f, 0x7f,0x7f,0x7f,0x7f, 0x7f,0x7f,0x7f,0x7f, // 
                           0x7f,0x7f,0x7f,0x7f, 0x7f,0x7f,0x7f,0x7f, 0x7f,0x7f,0x7f,0x7f, 0x7f,0x7f,0x7f,0x7f, // 
                           0x7f,0x7f,0x7f,0x7f, 0x7f,0x7f,0x7f,0x7f, 0x7f,0x7f,0x7f,0x7f, 0x7f,0x7f,0x7f,0x7f, // 
                           0x7f,0x7f,0x7f,0x7f, 0x7f,0x7f,0x7f,0x7f, 0x7f,0x7f,0x7f,0x7f, 0x7f,0x7f,0x7f,0x7f, // 
                           0x7f,0x7f,0x7f,0x7f, 0x7f,0x7f,0x7f,0x7f, 0x7f,0x7f,0x7f,0x7f, 0x7f,0x7f,0x7f,0x7f, // 
                           0x7f,0x7f,0x7f,0x7f, 0x7f,0x7f,0x7f,0x7f, 0x7f,0x7f,0x7f,0x7f, 0x7f,0x7f,0x7f,0x7f, // 
                           0x7f,0x7f,0x7f,0x7f, 0x7f,0x7f,0x7f,0x7f, 0x7f,0x7f,0x7f,0x7f, 0x7f,0x7f,0x7f,0x7f, // 
                           0x7f,0x7f,0x7f,0x7f, 0x7f,0x7f,0x7f,0x7f, 0x7f,0x7f,0x7f,0x7f, 0x7f,0x7f,0x7f,0x7f, // 
                           0x7f,0x7f,0x7f,0x7f, 0x7f,0x7f,0x7f,0x7f, 0x7f,0x7f,0x7f,0x7f, 0x7f,0x7f,0x7f,0x7f, // 
                           0x7f,0x7f,0x7f,0x7f, 0x7f,0x7f,0x7f,0x7f, 0x7f,0x7f,0x7f,0x7f, 0x7f,0x7f,0x7f,0x7f, // 
                           0x7f,0x7f,0x7f,0x7f, 0x7f,0x7f,0x7f,0x7f, 0x7f,0x7f,0x7f,0x7f, 0x7f,0x7f,0x7f,0x7f, // 
                           0x7f,0x7f,0x7f,0x7f, 0x7f,0x7f,0x7f,0x7f, 0x7f,0x7f,0x7f,0x7f, 0x7f,0x7f,0x7f,0x7f, // 
                           0x7f,0x7f,0x7f,0x7f, 0x7f,0x7f,0x7f,0x7f, 0x7f,0x7f,0x7f,0x7f, 0x7f,0x7f,0x7f,0x7f, // 
                           0x7f,0x7f,0x7f,0x7f, 0x7f,0x7f,0x7f,0x7f, 0x7f,0x7f,0x7f,0x7f, 0x7f,0x7f,0x7f,0x7f, // 
                           0x7f,0x7f,0x7f,0x7f, 0x7f,0x7f,0x7f,0x7f, 0x7f,0x7f,0x7f,0x7f, 0x7f,0x7f,0x7f,0x7f, // 
                           0x7f,0x7f,0x7f,0x7f, 0x7f,0x7f,0x7f,0x7f, 0x7f,0x7f,0x7f,0x7f, 0x7f,0x7f,0x7f,0x7f, // 
                           0x7f,0x7f,0x7f,0x7f, 0x7f,0x7f,0x7f,0x7f, 0x7f,0x7f,0x7f,0x7f, 0x7f,0x7f,0x7f,0x7f, // 
                           0x7f,0x7f,0x7f,0x7f, 0x7f,0x7f,0x7f,0x7f, 0x7f,0x7f,0x7f,0x7f, 0x7f,0x7f,0x7f,0x7f, // 
                           0x7f,0x7f,0x7f,0x7f, 0x7f,0x7f,0x7f,0x7f, 0x7f,0x7f,0x7f,0x7f, 0x7f,0x7f,0x7f,0x7f, // 
                           0x7f,0x7f,0x7f,0x7f, 0x7f,0x7f,0x7f,0x7f, 0x7f,0x7f,0x7f,0x7f, 0x7f,0x7f,0x7f,0x7f, // 
                           0x7f,0x7f,0x7f,0x7f, 0x7f,0x7f,0x7f,0x7f, 0x7f,0x7f,0x7f,0x7f, 0x7f,0x7f,0x7f,0x7f, // 
                           0x7f,0x7f,0x7f,0x7f, 0x7f,0x7f,0x7f,0x7f, 0x7f,0x7f,0x7f,0x7f, 0x7f,0x7f,0x7f,0x7f, // 
                           0x7f,0x7f,0x7f,0x7f, 0x7f,0x7f,0x7f,0x7f, 0x7f,0x7f,0x7f,0x7f, 0x7f,0x7f,0x7f,0x7f, // 
                           0x7f,0x7f,0x7f,0x7f, 0x7f,0x7f,0x7f,0x7f, 0x7f,0x7f,0x7f,0x7f, 0x7f,0x7f,0x7f,0x7f, // 
                           0x7f,0x7f,0x7f,0x7f, 0x7f,0x7f,0x7f,0x7f, 0x7f,0x7f,0x7f,0x7f, 0x7f,0x7f,0x7f,0x7f, // 
                           0x7f,0x7f,0x7f,0x7f, 0x7f,0x7f,0x7f,0x7f, 0x7f,0x7f,0x7f,0x7f, 0x7f,0x7f,0x7f,0x7f, // 
                           0x7f,0x7f,0x7f,0x7f, 0x7f,0x7f,0x7f,0x7f, 0x7f,0x7f,0x7f,0x7f, 0x7f,0x7f,0x7f,0x7f, // 
                           0x7f,0x7f,0x7f,0x7f, 0x7f,0x7f,0x7f,0x7f, 0x7f,0x7f,0x7f,0x7f, 0x7f,0x7f,0x7f,0x7f, // 
                           0x7f,0x7f,0x7f,0x7f, 0x7f,0x7f,0x7f,0x7f, 0x7f,0x7f,0x7f,0x7f, 0x7f,0x7f,0x7f,0x7f, // 
                           0x7f,0x7f,0x7f,0x7f, 0x7f,0x7f,0x7f,0x7f, 0x7f,0x7f,0x7f,0x7f, 0x7f,0x7f,0x7f,0x7f, // 
                           0x7f,0x7f,0x7f,0x7f, 0x7f,0x7f,0x7f,0x7f, 0x7f,0x7f,0x7f,0x7f, 0x7f,0x7f,0x7f,0x7f, // 
                           0x7f,0x7f,0x7f,0x7f, 0x7f,0x7f,0x7f,0x7f, 0x7f,0x7f,0x7f,0x7f, 0x7f,0x7f,0x7f,0x7f, // 
                           0x7f,0x7f,0x7f,0x7f, 0x7f,0x7f,0x7f,0x7f, 0x7f,0x7f,0x7f,0x7f, 0x7f,0x7f,0x7f,0x7f, // 
                           0x7f,0x7f,0x7f,0x7f, 0x7f,0x7f,0x7f,0x7f, 0x7f,0x7f,0x7f,0x7f, 0x7f,0x7f,0x7f,0x7f, // 
                           0x7f,0x7f,0x7f,0x7f, 0x7f,0x7f,0x7f,0x7f, 0x7f,0x7f,0x7f,0x7f, 0x7f,0x7f,0x7f,0x7f, // 
                           0x7f,0x7f,0x7f,0x7f, 0x7f,0x7f,0x7f,0x7f, 0x7f,0x7f,0x7f,0x7f, 0x7f,0x7f,0x7f,0x7f, // 
                           0x7f,0x7f,0x7f,0x7f, 0x7f,0x7f,0x7f,0x7f, 0x7f,0x7f,0x7f,0x7f, 0x7f,0x7f,0x7f,0x7f, // 
                           0x7f,0x7f,0x7f,0x7f, 0x7f,0x7f,0x7f,0x7f, 0x7f,0x7f,0x7f,0x7f, 0x7f,0x7f,0x7f,0x7f, // 
                           0x7f,0x7f,0x7f,0x7f, 0x7f,0x7f,0x7f,0x7f, 0x7f,0x7f,0x7f,0x7f, 0x7f,0x7f,0x7f,0x7f, // 
                           0x7f,0x7f,0x7f,0x7f, 0x7f,0x7f,0x7f,0x7f, 0x7f,0x7f,0x7f,0x7f, 0x7f,0x7f,0x7f,0x7f, // 
                           0x7f,0x7f,0x7f,0x7f, 0x7f,0x7f,0x7f,0x7f, 0x7f,0x7f,0x7f,0x7f, 0x7f,0x7f,0x7f,0x7f, // 
                           0x7f,0x7f,0x7f,0x7f, 0x7f,0x7f,0x7f,0x7f, 0x7f,0x7f,0x7f,0x7f, 0x7f,0x7f,0x7f,0x7f, // 
                           0x7f,0x7f,0x7f,0x7f, 0x7f,0x7f,0x7f,0x7f, 0x7f,0x7f,0x7f,0x7f, 0x7f,0x7f,0x7f,0x7f, // 
                           0x7f,0x7f,0x7f,0x7f, 0x7f,0x7f,0x7f,0x7f, 0x7f,0x7f,0x7f,0x7f, 0x7f,0x7f,0x7f,0x7f, // 
                           0x7f,0x7f,0x7f,0x7f, 0x7f,0x7f,0x7f,0x7f, 0x7f,0x7f,0x7f,0x7f, 0x7f,0x7f,0x7f,0x7f, // 
                           0x7f,0x7f,0x7f,0x7f, 0x7f,0x7f,0x7f,0x7f, 0x7f,0x7f,0x7f,0x7f, // 
                           0xf1,0x96,0xdb,0x97, // CRC 
                           0xbc,0xb5,0xd5,0xd5  // EOFn
}; // End of cspat 
#endif
 
/*
 * Local variables:
 *  indent-tabs-mode: t
 *  c-indent-level: 4
 *  c-basic-offset: 4
 * End:
 *
 * vim: ts=4 sts=4 sw=4 noexpandtab
 */
/*
 * Local variables:
 *  indent-tabs-mode: t
 *  c-indent-level: 4
 *  c-basic-offset: 4
 * End:
 *
 * vim: ts=4 sts=4 sw=4 noexpandtab
 */
