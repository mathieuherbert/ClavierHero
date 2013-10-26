/*
 * Missile.cpp
 *
 *  Created on: 5 nov. 2008
 *      Author: MATTHIEU
 */

#include "MissileCanon.h"
#include "Applications/SpaceInvaders/Espace.h"

MissileCanon *MissileCanon::singleton = NULL;

MissileCanon::MissileCanon(TimerSpaceInvaders *timer, int degats, int ligne,
		int colonne, char *a, int h, int l, Couleur c) :
			Missile(DEPL_HAUT, degats, ligne, colonne, a, 1, 1, c) {

	setSemaphore(timer->getMissileCanon());

}

MissileCanon *MissileCanon::lancerNouveauMissile(int positionColonne){
	if(missileDisponible()){
		singleton = new MissileCanon(timer, 1, 22, positionColonne, "|", 1, 1, VERT);
		singleton->start("SP Missiles (joueur)");
	}
	return singleton;
}

void MissileCanon::stop(){
	singleton = NULL;
	espace->setEntiteVide(positionLigne, positionColonne);
	Exit();
}

bool MissileCanon::missileDisponible(){
//	return 1;
	return singleton == NULL;
}

int MissileCanon::getNombre(){
	if(missileDisponible())
		return 0;
	return 1;
}
MissileCanon *MissileCanon::getMissileCanon(){
	return singleton;
}

void MissileCanon::reinitialiser(){
	singleton = NULL;
}
