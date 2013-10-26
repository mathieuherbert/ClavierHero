/*
 * SpaceInvader.cpp
 *
 *  Created on: 17 oct. 2008
 *      Author: Aur�lien
 */

#include "SpaceInvaders.h"

int SpaceInvaders::score = 0;

SpaceInvaders::SpaceInvaders(EcranV *ec, ClavierV *c) {
	ecran = ec;
	clavier = c;
	//timer = t;
	timer = new TimerSpaceInvaders(ecran);
	score = 0;
	EntiteBase::setEcran(ecran);
	MissileCanon::setTimer(timer);
	espace = NULL;

//	do{
//		//On fixe ici le timer du d�placement des aliens, en ms.
//		//Par d�faut : voir timerspaceinvaders.h
//		//timer->setTimerDeplacementAliens(1000);
//		niveau++;
//		ecran->effacerEcranV(NOIR);
//		Missile::reinitialiser();
//		Espace* ancienEspace = espace;
//		espace = new Espace(ecran, timer, clavier, niveau);
//		if(ancienEspace!=NULL)
//			delete ancienEspace;
//		/**
//		 * Une attente est effectu�e ici afin de ne pas effacer la pile du jeu.
//		 * Des missiles sont cr��s en continu (test)
//		 */
//		asm volatile("sti\n");//Autorise les interruptions
//		espace->demarrerEspace();
//		while (!espace->niveauTermine())
//			timer->handler(espace);
//
//		//espace->stopperEspace();
//		//ec->miniprintf("GAME FINISHED");
//	}while(espace->getCanon()->getPointsDeVie()>0 && niveau<=10);
//	ecran->effacerEcranV(NOIR);
//	if(espace->getCanon()->getPointsDeVie()>0){
//		ecran->afficherMot(HAUTEUR/2,LARGEUR/2-5,"WELL DONE!", BLANC);
//	}
//	else{
//		ecran->afficherMot(HAUTEUR/2, LARGEUR/2-5, "GAME OVER", BLANC);
//	}
//	espace->stopperEspace();

}

SpaceInvaders::~SpaceInvaders(){
	delete espace;
}

void SpaceInvaders::run(){
	int niveau =0;

do{
		//On fixe ici le timer du d�placement des aliens, en ms.
		//Par d�faut : voir timerspaceinvaders.h
		//timer->setTimerDeplacementAliens(1000);
		niveau++;
		ecran->effacerEcranV(NOIR);
		Missile::reinitialiser();
		Espace* ancienEspace = espace;
		espace = new Espace(ecran, timer, clavier, niveau);
		if(ancienEspace!=NULL)
			delete ancienEspace;
		/**
		 * Une attente est effectu�e ici afin de ne pas effacer la pile du jeu.
		 * Des missiles sont cr��s en continu (test)
		 */
		asm volatile("sti\n");//Autorise les interruptions
		espace->demarrerEspace();
		while (!espace->niveauTermine())
			timer->handler(espace);

		//espace->stopperEspace();
		//ec->miniprintf("GAME FINISHED");
	}while(espace->getCanon()->getPointsDeVie()>0 && niveau<=10);
	ecran->effacerEcranV(NOIR);
	if(espace->getCanon()->getPointsDeVie()>0){
		ecran->afficherMot(HAUTEUR/2,LARGEUR/2-5,"WELL DONE!", BLANC);
	}
	else{
		ecran->afficherMot(HAUTEUR/2, LARGEUR/2-5, "GAME OVER", BLANC);
	}
	espace->stopperEspace();
}

