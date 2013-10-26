/*
 * IntApp.h
 *
 *  Created on: 24 nov. 2010
 *      Author: pouda
 */

#ifndef INTAPP_H_
#define INTAPP_H_
#include<sextant/Activite/Threads.h>
#include<lib/String.h>
#include"../../drivers/EcranV.h"
#include <sextant/ordonnancements/preemptif/thread.h>

//#include<sextant/Activite/Threads.cpp>
class IntApp : public thread{
private :
	int pid;
	//Threads *listThread;
public :

	virtual void killSoft()=0;
	virtual void ajouterThread(Threads *thread)=0;
	virtual void killThread(Threads *thread)=0;
	virtual String* getNom()=0;
	virtual int getPid() =0;
	virtual void killHard()=0;
	//virtual IntApp* getClone(EcranV* ecran)=0;
	virtual int getNumShell()=0;
	virtual EcranV* getEcran()=0;
};

#endif /* INTAPP_H_ */
