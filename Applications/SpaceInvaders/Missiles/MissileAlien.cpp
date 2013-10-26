/*
 * Missile.cpp
 *
 *  Created on: 5 nov. 2008
 *      Author: MATTHIEU
 */

#include "MissileAlien.h"
#include "Applications/SpaceInvaders/Espace.h"

MissileAlien *missilesAliens[MISSILES_ALIENS_MAX];
int MissileAlien::nombreMaxMissiles = MISSILES_ALIENS_MAX;

MissileAlien::MissileAlien(TimerSpaceInvaders *timer, int degats, int n, int ligne, int colonne,
		char *a, int h, int l, Couleur c) :
			Missile(DEPL_BAS, degats, ligne, colonne, a, h, l, c) {

	numeroMissile = n;
	setSemaphore(timer->getMissileAliens(numeroMissile));
	missilesAliens[numeroMissile] = this;
}

MissileAlien *MissileAlien::lancerNouveauMissile(int positionLigne, int positionColonne){
	if(missileDisponible()){
		int numero = 0;
		while(missilesAliens[numero]!=NULL && numero<=nombreMaxMissiles){
			numero++;
		}
		MissileAlien *missile;
		missile = new MissileAlien(timer, 1, numero, positionLigne, positionColonne, "|", 1, 1, ROUGE);
		missile->start("SP Missiles");
		return missile;
	}
	return NULL;
}

int MissileAlien::getNombre(){
	int nombreMissiles = 0;
	for(int i=0; i<nombreMaxMissiles; i++){
		if(missilesAliens[i] != NULL)
			nombreMissiles ++;
	}
	return nombreMissiles;
}

void MissileAlien::stop(){
	missilesAliens[numeroMissile] = NULL;
	espace->setEntiteVide(positionLigne, positionColonne);
	Exit();
}

bool MissileAlien::missileDisponible(){
	return getNombre() != nombreMaxMissiles;
}

MissileAlien *MissileAlien::getMissileAlien(int numero){
	return missilesAliens[numero];
}

void MissileAlien::setNombreMaxMissiles(int n){
	nombreMaxMissiles = n;
}

void MissileAlien::reinitialiser(){
	for(int i=0; i<MISSILES_ALIENS_MAX; i++)
		missilesAliens[i] = NULL;

}
