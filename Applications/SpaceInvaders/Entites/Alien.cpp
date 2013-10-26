/*
 * Alien.cpp
 *
 *  Created on: 22 oct. 2008
 *      Author: Aurélien
 */

#include "Alien.h"
#include "Applications/SpaceInvaders/Espace.h"

Alien::Alien(int v, char *a, int h, int l, Couleur c) :
	EntiteBase(v, 0, 0, a, h, l, c){}

Alien::~Alien(){}

void Alien::infligerDegats(int degats){
	vie -= degats;
	if(vie <= 0)
		espace->getBlocAliens()->retirerAlien(this);
}

void Alien::setPositionLigne(int p){
	positionLigne = p;
}
void Alien::setPositionColonne(int p){
	positionColonne = p;
}
