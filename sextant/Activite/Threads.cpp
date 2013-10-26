/*
 * Thread.cpp
 *
 *  Created on: 1 oct. 2008
 *      Author: Jean-Marc Menaud
 */
#include "Threads.h"

//Threads::Threads() {};

	/*	maThread = create_kernel_thread(
				(kernel_thread_start_routine_t) Thread::start,
				(void*) this);
}

void Threads::exit_thread(vaddr_t stack_vaddr) {

}*/
void Threads::suspend(int suspID){
	sched_set_waiting(thread_get_current(),suspID);
}
void Threads::resume(int suspID){
	sched_set_ready(pop_in_waiting_queue(suspID));
}



