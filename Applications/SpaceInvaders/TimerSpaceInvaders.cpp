/*
 * TimerSpaceInvaders.cpp
 *
 *  Created on: 27 oct. 2008
 *      Author: Aur�lien
 */

#include "TimerSpaceInvaders.h"
#include <Applications/SpaceInvaders/SpaceInvaders.h>
#include <Applications/SpaceInvaders/Missiles/MissileCanon.h>
#include <Applications/SpaceInvaders/Missiles/MissileAlien.h>
#include <sextant/memoire/Memoire.h>

//extern Semaphore semaphoreTicHandler;
bool modifTic=true;

extern int number_thread_waiting;
extern int number_thread_ready;
//int compt = 0;
//int b = 0;

int compteurTicHandler = 0;
int secondes_al =0;

void ticTacSpaceInvader() {
	compteurTicHandler++;
	modifTic = true;
	if(compteurTicHandler%1000==0)
		secondes_al++;
}

TimerSpaceInvaders::TimerSpaceInvaders(EcranV *ec) {
	ecran = ec;
	secondesTimer = 0;

	for(int i=0; i<MISSILES_ALIENS_MAX; i++)
		missileAliens[i] = new Semaphore();
	missileCanon = new Semaphore();
	deplacementAliens = new Semaphore();

	timerMissilesCanon = VITESSE_MISSILE_CANON;
	timerMissileAliens = 1000;
	timerDeplacementAliens = 1000;
}
void TimerSpaceInvaders::afficherTemps(int l, int c, int temps){
	ecran->afficherMot(l, c, "Time:", BLANC);
	ecran->afficherChiffre(l, c+9, temps%10);
	temps = temps/10;
	ecran->afficherChiffre(l, c+8, temps%6);
	ecran->afficherCaractere(l, c+7, BLANC, NOIR, ':');
	temps = temps/6;
	ecran->afficherChiffre(l, c+6, temps%10);
	temps = temps/10;
	ecran->afficherChiffre(l, c+5, temps%6);
}

void TimerSpaceInvaders::afficherChiffreCommente(int l, int c, const char* label,
		const int valeur, const int nbChiffres) {
	long nombreDeCaracteres = 0;
	char caractereActuel = 0;
	do {
		caractereActuel = label[nombreDeCaracteres];
		nombreDeCaracteres++;
	} while (caractereActuel != '\0'); // On boucle tant qu'on n'est pas arriv� � l'\0
	nombreDeCaracteres--; // On retire 1 caract�re de long pour ne pas compter l'\0

	ecran->afficherMot(l, c, label, BLANC);

	bool negatif = valeur < 0;
	int tailleChiffre = 6, exposant = 1000000;
	while (valeur < exposant && !negatif || -valeur < exposant && negatif) {
		exposant = exposant / 10;
		tailleChiffre--;
	}
	if (tailleChiffre <= 0)
		tailleChiffre = 1;

	for (int i = c + nombreDeCaracteres; i < c + nombreDeCaracteres
			+ nbChiffres; i++)
		ecran->afficherCaractere(l, i, NOIR, NOIR, ' ');
	ecran->afficherChiffre(l, c + nombreDeCaracteres + nbChiffres - tailleChiffre,
			valeur);
}

int previoustimerDeplacementAliens=0;
int previoustimerMissileAliens=0;
int previoustimerMissilesCanon=0;

void TimerSpaceInvaders::handler(Espace *espace){
	//La boucle devrait �tre mise ici. Le s�maphore devrait garantir
	//la mise � jour � chaque interruption..
	//Espace sert pour l'affichage.

	int past=0;
	modifTic=false;

	while(!modifTic){
		compteurTicHandler=gettime();
		if (compteurTicHandler!=past) {modifTic = true;past=compteurTicHandler;}
		else thread_yield();
	}



	if(compteurTicHandler%1000==0)
		secondes_al++;

	if((compteurTicHandler-(previoustimerDeplacementAliens+(timerDeplacementAliens))) > 0){
		previoustimerDeplacementAliens=previoustimerDeplacementAliens+(timerDeplacementAliens);
		deplacementAliens->V();
	}


	if((compteurTicHandler-(previoustimerMissileAliens+(timerMissileAliens))) > 0){
		previoustimerMissileAliens=previoustimerMissileAliens+(timerMissileAliens);
		for(int i=0; i<MISSILES_ALIENS_MAX; i++)
			missileAliens[i]->V();
	}

	if((compteurTicHandler-(previoustimerMissilesCanon+(timerMissilesCanon))) > 0){
		previoustimerMissilesCanon=previoustimerMissilesCanon+timerMissilesCanon;
		missileCanon->V();
	}

	afficherTemps(0, 69, compteurTicHandler/1000);
	afficherChiffreCommente(0, 19, "Score:", SpaceInvaders::score, 6);
	afficherChiffreCommente(0, 34, "Lives remaining:", espace->getCanon()->getPointsDeVie(), 1);
	afficherChiffreCommente(0, 55, "Level:", espace->getNiveau(), 1);

	if(false){
		int posLigne = 2;
		int posColonne = 60;
		afficherChiffreCommente(posLigne++, posColonne, "Timer (ms):", compteurTicHandler, 5);
		posLigne ++;
		afficherChiffreCommente(posLigne++, posColonne, "Sem. Alien:", deplacementAliens->Valeur(), 5);
		afficherChiffreCommente(posLigne++, posColonne, "Nbre MissC:", MissileCanon::getNombre(), 5);
		afficherChiffreCommente(posLigne++, posColonne, "Nbre MissA:", MissileAlien::getNombre(), 5);
		posLigne ++;
//		ecran->afficherChiffreCommente(posLigne++, posColonne, "Nbr Threads:", getNbThreads(), 2);
		afficherChiffreCommente(posLigne++, posColonne, "NbrThrReady:", number_thread_ready, 2);
		afficherChiffreCommente(posLigne++, posColonne, "NbThrWaiting:", number_thread_waiting, 2);
		posLigne ++;
		BlocAliens *bloc;
		bloc = espace->getBlocAliens();
		afficherChiffreCommente(posLigne++, posColonne, "PositBlocLigne:", bloc->getPositionLigne(), 2);
		afficherChiffreCommente(posLigne++, posColonne, "PosBlocColonne:", bloc->getPositionColonne(), 2);
		afficherChiffreCommente(posLigne++, posColonne, "Direction Bloc:", bloc->getDirection(), 2);
		posLigne ++;
		afficherChiffreCommente(posLigne++, posColonne, "LargeurBloc:", bloc->getLargeur(), 2);
		afficherChiffreCommente(posLigne++, posColonne, "ecartGauche:", bloc->getEcartGauche(), 2);
		afficherChiffreCommente(posLigne++, posColonne, "HauteurBloc:", bloc->getHauteur() , 2);
		afficherChiffreCommente(posLigne++, posColonne, "NombreAlien:", bloc->getNombreAliensRestants() , 2);
	}

	//}
}

Semaphore *TimerSpaceInvaders::getMissileAliens(int numeroMissile){
	return missileAliens[numeroMissile];
}
Semaphore *TimerSpaceInvaders::getMissileCanon(){
	return missileCanon;
}
Semaphore *TimerSpaceInvaders::getDeplacementAliens(){
	return deplacementAliens;
}


void TimerSpaceInvaders::setTimerMissileAliens(int ms){
	timerMissileAliens = ms;
}
void TimerSpaceInvaders::setTimerMissileCanon(int ms){
	timerMissilesCanon = ms;
}
void TimerSpaceInvaders::setTimerDeplacementAliens(int ms){
	timerDeplacementAliens = ms;
}
int TimerSpaceInvaders::getTimerDeplacementAliens(){
	return timerDeplacementAliens;
}

int TimerSpaceInvaders::getTemps(){
	return secondesTimer;
}

void TimerSpaceInvaders::demarrerTimer(){
/*	deplacementAliens->reset();
	for(int i=0; i<MISSILES_ALIENS_MAX; i++)
		missileAliens[i]->reset();
	missileCanon->reset();
	compteurSecondesOn = true;*/
}

void TimerSpaceInvaders::stopperTimer(){
	deplacementAliens->V();
	for(int i=0; i<MISSILES_ALIENS_MAX; i++)
		missileAliens[i]->V();
	missileCanon->V();
	compteurSecondesOn = false;
}
