/*
 * Ennemi.h
 *
 *  Created on: 25 nov. 2011
 *      Author: Xan
 */

#ifndef ENNEMI_H_
#define ENNEMI_H_

#include "Attaque.h"

class Ennemi {
public:
	int pv;
	int vitesseDeplacement;
	int niveau;
	int horloge;
	int ralentissement;

	//constructeurs
	Ennemi(int pv, int avancement, int vitesseDeplacement, int niveau);
	Ennemi(int niveau);

	//retourne les points de vie totaux de l'ennemi
	int getPv();
	//retourne la vitesse de d�placement de l'ennemi
	int getVitesseDeplacement();
	//retourne le niveau de l'ennemi
	int getNiveau();
	//retourne true si l'ennemi a avanc�
	bool round();
	//retourne true si l'ennemi a subi une attaque
	bool subirAttaque(Attaque *attaque);

};

#endif /* ENNEMI_H_ */
