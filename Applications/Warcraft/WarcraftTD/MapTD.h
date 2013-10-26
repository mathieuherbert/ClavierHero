/*
 * MapTD.h
 *
 *  Created on: 30 nov. 2011
 *      Author: Xan
 */

#ifndef MAPTD_H_
#define MAPTD_H_

#include <drivers/EcranV.h>
#include <drivers/ClavierV.h>
#include <sextant/Activite/Threads.h>
#include <Applications/Warcraft/WarcraftTD/FabriqueDennemi.h>
#include <Applications/Warcraft/Position.h>
#include "Tour.h"
#include <Applications/Warcraft/WarcraftTD/Ennemi.h>


class MapTD {
public:
	static const int H=26;
	static const int L=70;

	//le chemin doit avoir moins de 1023 cases,
	//ce nombre est utilisé pour indiqué qu'un ennemi n'est plus sur le chemin
	static const int out=1023;

	EcranV *ecr;

	//liste des ennemis sur la carte
	Ennemi *ennemi[H*L];
	int nombreEnnemi;

	//liste de la position de chaque ennemi
	int position[H*L];

	//taille du chemin
	int tailleChemin;

	//liste des cases du chemin
	Position *che[H*L];

	FabriqueDennemi *fabrique;

	Tour *tours[H*L];
	Position *positionsTours[H*L];
	int nombreTours;



	MapTD(EcranV *ecr);
	void initialiserMap();
	void initialiserChemin(int n);
	bool estDansLeTableau(int x,int y);
	bool contientEnnemi(int n);
	int gererLesEnnemi();
	int gererLesTours();
	int construireTour(char c,int x,int y, int gold);
	bool attaquer(Tour *tour,Position *p);
	int attaquerZone(Tour *tour,Position *p);
	Tour *getInfo(int x,int y);
	int abs(int x);

	static const int ENNEMI=2;
	static const int CHEMIN=32;
	static const int TERRAIN=176;
};

#endif /* MAPTD_H_ */
