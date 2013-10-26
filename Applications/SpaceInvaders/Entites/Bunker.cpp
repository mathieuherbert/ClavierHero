/*
 * Bunker.cpp
 *
 *  Created on: 22 oct. 2008
 *      Author: Aurélien
 */

#include "Bunker.h"
#include "Applications/SpaceInvaders/Espace.h"

Bunker::Bunker(int v, int ligne, int colonne, char *a, Couleur c) :
	EntiteBase(v, ligne, colonne, a, 1, 1, c){}

void Bunker::infligerDegats(int degats){
	vie -= degats;
	if(vie <= 0)
		espace->supprimerEntite(this);
}
