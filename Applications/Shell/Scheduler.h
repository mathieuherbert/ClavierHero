/*
 * Scheduler.h
 *
 *  Created on: 8 déc. 2010
 *      Author: jonathan
 */

#ifndef SCHEDULER_H_
#define SCHEDULER_H_

#include <sextant/ordonnancements/preemptif/thread.h>
#include <sextant/ordonnancements/preemptif/sched.h>
#include <Applications/Shell/ListeDouble.h>

struct PID_to_THREADS{

	int PID;
	ListeDouble<thread>* listeThreads;
};

class Scheduler {
private:

	ListeDouble<PID_to_THREADS>* listeAPPLIS;

public:
	Scheduler();
	virtual ~Scheduler();

	bool addThread(thread* t, int pid);
	bool enleverThread(thread* t);
	bool enleverThreads(int pid);
};

#endif /* SCHEDULER_H_ */
