/*
 * ShellV.h
 *
 *  Created on: 8 déc. 2010
 *      Author: pouda
 */

#include <sextant/Activite/Threads.h>
#include <Applications/Shell/ListeDouble.h>
#include <Applications/Shell/IntApp.h>
#include <drivers/ClavierV.h>
#include <drivers/EcranV.h>
#include <Applications/Shell/Shell.h>
#include <Applications/Shell/Scheduler.h>

#ifndef SHELLV_H_
#define SHELLV_H_

class ShellV : public Threads{
private:
	int numeroEcran;
	Shell *shellPere;
	EcranV *ecran;
	ClavierV *clavier;
	Scheduler *sched;
	Semaphore sem;
	ListeDouble<String> *historique;

public:
	ShellV(EcranV *ecran, ClavierV *clavier, Shell *shellPere, int numeroEcran, Scheduler *sched);
	void AfficherAide();
	void listerApplis(ListeDouble<String> *liste);
	void listerApplisEncours(ListeDouble<IntApp> *liste);
	IntApp* getAppli(int pid);
	String* getAppliAlancer(String nom);
	int dixPuissance(int i);
	String getClavier();
	void run();
	int getCommande(String s);
	String getArgument(String s, int i);
	void ls(String cmd);
	void top(String cmd);
	void ps();
	void killAppli(String cmd);
	void runAppli(String cmd, int numThread);

	char* lectureLigne();
};

#endif /* SHELLV_H_ */
