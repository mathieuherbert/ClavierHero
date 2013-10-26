/*
 * FabriqueDennemi.h
 *
 *  Created on: 12 déc. 2011
 *      Author: Math
 */

#ifndef FABRIQUEDENNEMI_H_
#define FABRIQUEDENNEMI_H_

#include <Applications/Warcraft/warcraftTD/Ennemi.h>

class FabriqueDennemi{
public:
	int lvl;
	int nombreVague;
	int horloge;
	int const static lvlmax=5;
	int const static pause=40;
	int cadence[lvlmax];
	int nombre[lvlmax];

public:
	//Constructeur
	FabriqueDennemi();
	//quand round est true alors getEnnemi est appellé
	Ennemi *getEnnemi();

	//met à jour l'horloge et renvoie true si un ennemi doit arriver sur la map
	bool round();

	//retourne le niveau de la vague d'ennemi
	int getlvl();
	//retourne le niveau maximum (i.e. de la dernière) vague d'ennemi
	int getlvlmax();



};

#endif /* FABRIQUEDENNEMI_H_ */
