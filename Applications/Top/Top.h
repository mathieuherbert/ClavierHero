/*
 * Top.h
 *
 *  Created on: 29 déc. 2011
 *      Author: menaud
 */

#ifndef TOP_H_
#define TOP_H_
#include <sextant/Activite/Threads.h>
#include <drivers/EcranV.h>
#include <sextant/ordonnancements/preemptif/sched.h>

class Top : public Threads {
	EcranV *ecran;

public :
	Top(EcranV*);

	void run();

	void print();
};

#endif /* TOP_H_ */
