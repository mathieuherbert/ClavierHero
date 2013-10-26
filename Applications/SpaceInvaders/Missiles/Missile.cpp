/*
 * Missile.cpp
 *
 *  Created on: 7 nov. 2008
 *      Author: Aurélien
 */

#include "Missile.h"
#include "Applications/SpaceInvaders/Espace.h"

TimerSpaceInvaders *Missile::timer = NULL;

Missile::Missile(int dir, int deg, int ligne, int colonne, char *a, int h, int l,
		Couleur c) :
			EntiteBase(0, ligne, colonne, a, h, l, c) {
	direction = dir;
	degats = deg;
}

void Missile::setSemaphore(Semaphore *s) {
	semaphore = s;
}

void Missile::run() {
	dessiner();
	semaphore->reset();
	while (getPositionLigne()>1 && getPositionLigne()<24 && !espace->niveauTermine()) {
		semaphore->P();
		if(espace->niveauTermine())
			Exit();
		if(!espace->niveauTermine()){
			chercherCollision();
			deplacer(direction);
		}
	}

	stop();
}

void Missile::chercherCollision(){
	int depl = 0;
	if(direction == DEPL_HAUT)
		depl = -1;
	if(direction == DEPL_BAS)
		depl = 1;

	espace->getEntite(positionLigne+depl, positionColonne)->getSemaphore()->P();
	EntiteBase *entite;
	entite = espace->getEntite(positionLigne+depl, positionColonne);
	if(!entite->estEntiteVide() && !entite->estMissile()){
		entite->infligerDegats(degats);
		entite->getSemaphore()->V();
		this->stop();
	}
	entite->getSemaphore()->V();
}

void Missile::setTimer(TimerSpaceInvaders *t){
	timer = t;
}

void Missile::reinitialiser(){
	MissileCanon::reinitialiser();
	MissileAlien::reinitialiser();
}
