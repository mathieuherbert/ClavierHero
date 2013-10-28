/*
 * GestionToucheClavier.cpp
 *
 *  Created on: 25 oct. 2013
 *      Author: Julien Deray, Mathieu Cartaud, Mathieu Herbert
 */

#include "GestionToucheClavier.h"
#include <Applications/KeyboardHero/ClavierHero.h>

GestionToucheClavier::GestionToucheClavier(ClavierV *c, ClavierHero *ch){
	clavier = c;
	clavierHero = ch;
}

void GestionToucheClavier::run(){
	char src;
	while (true){
		//recuperation de la commande du joueur
		if(src=clavier->getChar()){
			switch(src){
			//F1
			case 'a': clavierHero->setToucheJouee(ClavierHero::FUN);
			break;

			//F2
			case 'z': clavierHero->setToucheJouee(ClavierHero::FDEUX);
			break;

			//F3
			case 'e': clavierHero->setToucheJouee(ClavierHero::FTROIS);
			break;

			//F4
			case 'r': clavierHero->setToucheJouee(ClavierHero::FQUATRE);
			break;
			}
		}
	}
}

