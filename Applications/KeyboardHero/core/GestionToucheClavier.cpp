/*
 * GestionToucheClavier.cpp
 *
 *  Created on: 25 oct. 2013
 *      Author: Julien Deray, Mathieu Cartaud, Mathieu Herbert
 */

#include "GestionToucheClavier.h"
#include <Applications/KeyboardHero/ClavierHero.h>
/*
 * Classe reccuperant la touche appuyé par l utilisateur et renvoyant vers ClavierHero
 */
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
			//a
			case 'a': clavierHero->setToucheJouee(ClavierHero::FUN);
			break;

			//z
			case 'z': clavierHero->setToucheJouee(ClavierHero::FDEUX);
			break;

			//e
			case 'e': clavierHero->setToucheJouee(ClavierHero::FTROIS);
			break;

			//r
			case 'r': clavierHero->setToucheJouee(ClavierHero::FQUATRE);
			break;
			}
		}
	}
}

