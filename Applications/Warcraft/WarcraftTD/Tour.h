/*
 * Tour.h
 *
 *  Created on: 25 nov. 2011
 *      Author: Fredo
 */

#ifndef TOUR_H_
#define TOUR_H_

/*#include "MapTD.h"*/
#include "Attaque.h"


class Tour{
public:
	int vitesseAttaque;
	int portee;
	int cout;
	int x,y;
	int horloge;
	int logo;
	int niveau;
	char caractere;

	//Constructeur
	Tour(char caractere, int x, int y);

	bool round();
	//Tous les getters
	int getVitesseAttaque();
	int getX();
	int getY();
	int getPortee();
	int getCout();

	//Retourne l'attaque produite par la tour
	Attaque *attaquer();
};

#endif /* TOUR_H_ */
