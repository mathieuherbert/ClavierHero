/*
 * Top.cpp
 *
 *  Created on: 29 dŽc. 2011
 *      Author: menaud
 */

#include "Top.h"

struct uneStruct *all_ready_thread;
struct uneStructWaiting *all_waiting_thread;

Top::Top(EcranV *e){
	ecran=e;
}

void Top::run(){
	while (1) print();
}

void Top::print(){

	all_ready_thread = getReadyThread();
	all_waiting_thread = getWaitingThread();
	ecran->effacerEcranV(NOIR);
	ecran->miniprintf("TOP\n");

	struct thread *running = getRunningThread();
	String *mypid = new String(running->pid);
	ecran->miniprintf("%s Running   Name %s | State : %s\n",
						String::format(mypid->getString(),3)->getString(),
						String::format(running->name,10)->getString(),
						String::format(print_state(running->state),12)->getString());

	for (int i=0;i<MAX_THREAD;i++) {
		if (all_ready_thread[i].free==0) {
			// Conversion pid numerique en String
			String *mypid =
					new String(all_ready_thread[i].thread->pid);

			// formatage pid sur 3 caracteres
			ecran->miniprintf("%s Ready   Q Name %s | State : %s\n",
					String::format(mypid->getString(),3)->getString(),
					String::format(all_ready_thread[i].thread->name,10)->getString(),
					String::format(print_state(all_ready_thread[i].thread->state),12)->getString());
		}
	}
	for (int i=0;i<MAX_THREAD;i++) {
		if (all_waiting_thread[i].free==0) {
			String *mypid =
						new String(all_waiting_thread[i].thread->pid);

			ecran->miniprintf("%s Waiting Q Name %s | State : %s\n",
					String::format(mypid->getString(),3)->getString(),
					String::format(all_waiting_thread[i].thread->name,10)->getString(),
					String::format(print_state(all_waiting_thread[i].thread->state),12)->getString());

		}
	}
	int j;
	for (int i=0;i<10000000;i++) {
		j=i*j;
	}
}
