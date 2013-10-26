/*
 * Shell.cpp
 *
 *  Created on: 24 nov. 2010
 *      Author: pouda
 */

#include "Shell.h"
#include <Applications/Shell/ListeDouble.h>
#include <Applications/Shell/ShellV.h>
#include <Applications/Shell/IntApp.h>
#include <Applications/Shell/ImpApp.cpp>
#include <Applications/AppliShell/Compteur.h>

Shell::Shell(EcranV listeEcran[], ClavierV *listeClavier[],int nbEcrans){
	Scheduler *sched = new Scheduler();
	for(int i=0;i<nbEcrans;i++){
		ShellV *newShell = new ShellV(&listeEcran[i], listeClavier[i],this,i, sched);
		newShell->start("Shell");
	}
	Disponible = new ListeDouble<String>();
	Encours = new ListeDouble<IntApp>();
	// ajout des applications disponibles

	//	IntApp* cpt = new Compteur(0,0);
	String *s1 = new String("Compteur");
	Disponible->ajouterDebut(*s1);
	String *s2 = new String("Demenageur");
	Disponible->ajouterDebut(*s2);
	String *s3 = new String("War (Warcraft)");
	Disponible->ajouterDebut(*s3);
	String *s4 = new String("Top");
	Disponible->ajouterDebut(*s4);
	String *s5 = new String("SP (SpaceInvaders");
	Disponible->ajouterDebut(*s5);
	String *s6 = new String("Pacman");
	Disponible->ajouterDebut(*s6);
	String *s7 = new String("CH (Clavier Hero)");
	Disponible->ajouterDebut(*s7);
}

ListeDouble<IntApp> *Shell::getEncours(){
	return Encours;
}

ListeDouble<String> *Shell::getDisponible(){
	return Disponible;
}
