/*
 * Compteur.h
 *
 *  Created on: 8 déc. 2010
 *      Author: Antoine
 */

#ifndef COMPTEUR_H_
#define COMPTEUR_H_
#include <drivers/ClavierV.h>
#include <sextant/types.h>
#include <drivers/timer.h>
#include <Applications/Shell/ShellV.h>
//#include <Applications/Shell/ImpApp.cpp>
#include <sextant/Activite/Threads.h>

class Compteur : public Threads {
private:
	Timer *timer;
	EcranV *ecran;

public:
	Compteur( EcranV *myecranV);

//	Compteur(ShellV *myshellV, EcranV *ecranV):ImpApp(new String("compteur"), myshellV, ecranV){
//		shellV=myshellV;
//		//timer=timer;
//
//	}
	//Compteur(ShellV *shellV, EcranV *ecranV,Timer *timer);

	void run();
	void compter();
	void killSoft();

	//IntApp* getClone(EcranV* ecran);

};

#endif /* COMPTEUR_H_ */
