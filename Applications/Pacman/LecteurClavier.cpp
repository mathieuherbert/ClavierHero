/*
 * LecteurClavier.cpp
 *
 *  Created on: 22 oct. 2012
 *      Author: Administrateur
 */

#include "LecteurClavier.h"

#include "JeuPacman.h"
#include "PlateauPacman.h"

LecteurClavier::LecteurClavier(/*EcranV *e,*/ClavierV *c, PlateauPacman *plateau){
	//ecran=e;
	clavier=c;
	lePlateau = plateau;
}

void LecteurClavier::run(){
	PortSerie *p;
	char src;
	while (lePlateau->jouer){
		//recuperation de la commande du joueur
		if(src=clavier->getChar()){
			switch(src){
			//haut
			case 'z': lePlateau->getPacman()->setDirectionNext(HAUT);
			p->ecrireMot("HAUT\n");
			if(lePlateau->getPacman()->getDirectionNext() == HAUT){
				p->ecrireMot("\tINIT HAUT OK\n");
			}else{
				p->ecrireMot("\tINIT HAUT NOK\n");

			}
			break;

			//gauche
			case 'q':lePlateau->getPacman()->setDirectionNext(GAUCHE);
			break;

			//bas
			case 's':lePlateau->getPacman()->setDirectionNext(BAS);
			break;

			//droite
			case 'd':lePlateau->getPacman()->setDirectionNext(DROITE);
			break;
			}
		}
	}
}
