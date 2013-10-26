/*
 * LecteurTouche.cpp
 *
 *  Created on: 22 oct. 2012
 *      Author: Administrateur
 */

#include "LecteurTouche.h"

#include "JeuPacman.h"
#include "PlateauPacman.h"

LecteurTouche::LecteurTouche(ClavierV *c, PlateauPacman *plateau){
	//ecran=e;
	clavier=c;
	lePlateau = plateau;
}

void LecteurTouche::run(){
	PortSerie *p;
	char src;
	while (true){
		//recuperation de la commande du joueur
		if(src=clavier->getChar()){
			lePlateau->touche = true;
			break;
		}
	}
}
