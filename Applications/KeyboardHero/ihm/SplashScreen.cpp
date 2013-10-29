/*
 * SplashScreen.cpp
 *
 *  Created on: 29 oct. 2013
 *      Author: mathieu
 */

#include "SplashScreen.h"

void SpashScreen::printSplashScreen(EcranV* e){
	e->afficherCaractere(5, 20, ROUGE, NOIR, 219);
	e->afficherCaractere(6, 20, ROUGE, NOIR, 219);
	e->afficherCaractere(7, 20, ROUGE, NOIR, 219);
	e->afficherCaractere(8, 20, ROUGE, NOIR, 219);
	e->afficherCaractere(9, 20, ROUGE, NOIR, 219);
	e->afficherCaractere(10, 20, ROUGE, NOIR, 219);
	e->afficherCaractere(11, 02, ROUGE, NOIR, 219);
}
