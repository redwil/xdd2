/*
 * XDD - a data movement and benchmarking toolkit
 *
 * Copyright (C) 1992-23 I/O Performance, Inc.
 * Copyright (C) 2009-23 UT-Battelle, LLC
 *
 * This is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public
 * License version 2, as published by the Free Software
 * Foundation.  See file COPYING.
 *
 */
#include "xint.h"
#include "xni.h"

#ifdef HAVE_SCHED_H
#include <sched.h>
#endif

/*----------------------------------------------------------------------------*/
/* xdd_worker_thread_init() - Initialization routine for a WorkerThread
 * This routine is passed a pointer to the Data Struct for this WorkerThread.
 * Return values: 0 is good, -1 is bad
 */
int32_t
xdd_worker_thread_init(worker_data_t *wdp) {
    int32_t  		status;
    target_data_t	*tdp;			// Pointer to this worker_thread's target Data Struct
    char			tmpname[XDD_BARRIER_MAX_NAME_LENGTH];	// Used to create unique names for the barriers

#if defined(HAVE_CPUSET_T) && defined(HAVE_PTHREAD_ATTR_SETAFFINITY_NP)
    // BWS Print the cpuset
    int i;
    cpu_set_t cpuset;
    CPU_ZERO(&cpuset);
    pthread_getaffinity_np(pthread_self(), sizeof(cpuset), &cpuset);
    printf("Thread %d bound to NUMA node", pthread_self());
    for (i = 0; i< 48; i++)
        if (CPU_ISSET(i, &cpuset))
            printf(" %d", i);
    printf("\n");
#endif

    // Get the Target Data Struct address as well
    tdp = wdp->wd_tdp;

#if (AIX)
	wdp->wd_thread_id = thread_self();
#elif (LINUX)
	wdp->wd_thread_id = syscall(SYS_gettid);
#else
	wdp->wd_thread_id = wdp->wd_pid;
#endif

	// The "my_current_state_mutex" is used by the WorkerThreads when checking or updating the state info
	status = pthread_mutex_init(&tdp->td_current_state_mutex, 0);
	if (status) {
		fprintf(xgp->errout,"%s: xdd_worker_thread_init: Target %d WorkerThread %d: ERROR: Cannot init my_current_state_mutex \n",
			xgp->progname, 
			tdp->td_target_number,
			wdp->wd_worker_number);
		fflush(xgp->errout);
		return(-1);
	}
	// The "mutex_this_worker_thread_is_available" is used by the WorkerThreads and the get_next_available_worker_thread() subroutines
	status = pthread_mutex_init(&wdp->wd_worker_thread_target_sync_mutex, 0);
	if (status) {
		fprintf(xgp->errout,"%s: xdd_worker_thread_init: Target %d WorkerThread %d: ERROR: Cannot init worker_thread_target_sync_mutex\n",
			xgp->progname, 
			tdp->td_target_number,
			wdp->wd_worker_number);
		fflush(xgp->errout);
		return(-1);
	}
	wdp->wd_worker_thread_target_sync = 0;

#if (HAVE_PREAD && HAVE_PWRITE)
        // Copy the file descriptor from the target thread (requires pread/pwrite support)
        status = xdd_target_shallow_open(wdp);
#else
	// Open the target device/file
	status = xdd_target_open(wdp->wd_tdp);
#endif
	if (status < 0) {
		fprintf(xgp->errout,"%s: xdd_worker_thread_init: Target %d WorkerThread %d: ERROR: Failed to open Target named '%s'\n",
			xgp->progname,
			tdp->td_target_number,
			wdp->wd_worker_number,
			tdp->td_target_full_pathname);
		return(-1);
	}
	
	// Initialize the tot_wait structure 
	status = pthread_cond_init(&wdp->wd_tot_wait.totw_condition, 0);
	if (0 != status) {
		fprintf(xgp->errout,"%s: xdd_worker_thread_init: Target %d WorkerThread %d: ERROR: Failed to initialize tot condition variable\n",
			xgp->progname,
			tdp->td_target_number,
			wdp->wd_worker_number);
		return(-1);
	}
	wdp->wd_tot_wait.totw_wdp = wdp;
	wdp->wd_tot_wait.totw_is_released = 0;
	wdp->wd_tot_wait.totw_nextp = 0;

	// Set up I/O buffer pointers
	if (xint_is_e2e(tdp)) {
		if (tdp->td_target_options & TO_E2E_DESTINATION) {
			// Buffer for destination is set after a receive
			wdp->wd_e2ep->xni_wd_buf = NULL;
			wdp->wd_task.task_datap = NULL;
			wdp->wd_e2ep->e2e_datap = NULL;
		} else {
			//TODO: I'd really like to move all of these buffer
			// request calls to something like ttd_before_io_op, but I
			// can't right now because later on in this function
			// xdd_datapattern_buffer_init() relies on the buffer
			// being present.  -nlmills

			// Request an I/O buffer from XNI			
			xni_request_target_buffer(tdp->td_e2ep->xni_td_conn, &wdp->wd_e2ep->xni_wd_buf);
			wdp->wd_task.task_datap = xni_target_buffer_data(wdp->wd_e2ep->xni_wd_buf);
			wdp->wd_e2ep->e2e_datap = wdp->wd_task.task_datap;
		}
	} else {
		// For non-E2E operations the data portion is the entire buffer
		const int32_t workernum = wdp->wd_worker_number;
		assert((uint32_t)workernum < tdp->io_buffers_count);
		wdp->wd_task.task_datap = tdp->io_buffers[workernum];
	}

	// Set the buffer data pattern for non-E2E operations or E2E sources
	if (!xint_is_e2e(tdp) || !(tdp->td_target_options & TO_E2E_DESTINATION)) {
		xdd_datapattern_buffer_init(wdp);
	}

	// Init the WorkerThread-TargetPass WAIT Barrier for this WorkerThread
	sprintf(tmpname,"T%04d:W%04d>worker_thread_targetpass_wait_barrier",tdp->td_target_number,wdp->wd_worker_number);
	status = xdd_init_barrier(tdp->td_planp, &wdp->wd_thread_targetpass_wait_for_task_barrier, 2, tmpname);
	if (status) {
		fprintf(xgp->errout,"%s: xdd_worker_thread_init: Target %d WorkerThread %d: ERROR: Cannot initialize WorkerThread TargetPass WAIT barrier.\n",
			xgp->progname, 
			tdp->td_target_number,
			wdp->wd_worker_number);
		fflush(xgp->errout);
		return(-1);
	}

	// Initialize the worker_thread ordering 
	status = pthread_cond_init(&wdp->wd_this_worker_thread_is_available_condition, 0);
	if (status) {
		fprintf(xgp->errout,"%s: xdd_worker_thread_init: Target %d WorkerThread %d: WARNING: Bad status from pthread_cond_init on wd_this_worker_thread_is_available_condition : status=%d, errno=%d\n",
			xgp->progname,
			tdp->td_target_number,
			wdp->wd_worker_number,
			status,
			errno);
	}

	// Indicate to the Target Thread that this WorkerThread is available
	pthread_mutex_lock(&tdp->td_any_worker_thread_available_mutex);
	tdp->td_any_worker_thread_available++;
	status = pthread_cond_broadcast(&tdp->td_any_worker_thread_available_condition);
	pthread_mutex_unlock(&tdp->td_any_worker_thread_available_mutex);
	if (status) {
		fprintf(xgp->errout,"%s: xdd_worker_thread_init: Target %d WorkerThread %d: WARNING: Bad status from sem_post on any_worker_thread_available semaphore: status=%d, errno=%d\n",
			xgp->progname,
			tdp->td_target_number,
			wdp->wd_worker_number,
			status,
			errno);
	}

	// Set up for an End-to-End operation (if requested)
	if (tdp->td_target_options & TO_ENDTOEND) {
		if (tdp->td_target_options & (TO_E2E_DESTINATION|TO_E2E_SOURCE)) {
			status = xdd_e2e_worker_init(wdp);
		} else { // Not sure which side of the E2E this target is supposed to be....
			fprintf(xgp->errout,"%s: xdd_worker_thread_init: Target %d WorkerThread %d: Cannot determine which side of the E2E operation this target is supposed to be.\n",
				xgp->progname,
				tdp->td_target_number,
				wdp->wd_worker_number);
			fprintf(xgp->errout,"%s: xdd_worker_thread_init: Check to be sure that the '-e2e issource' or '-e2e isdestination' was specified for this target.\n",
				xgp->progname);
				fflush(xgp->errout);
			return(-1);
		}

		if (status == -1) {
			fprintf(xgp->errout,"%s: xdd_worker_thread_init: Target %d WorkerThread %d: E2E %s initialization failed.\n",
				xgp->progname,
				tdp->td_target_number,
				wdp->wd_worker_number,
				(tdp->td_target_options & TO_E2E_DESTINATION) ? "DESTINATION":"SOURCE");
		return(-1);
		}
	} // End of end-to-end setup

	// All went well...
	return(0);

} // End of xdd_worker_thread_init()
 
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
