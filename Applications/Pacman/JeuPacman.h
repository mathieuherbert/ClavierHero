/*
 * Pacman.h
 *
 *  Created on: 5 oct. 2012
 *      Author: killerider
 */

#ifndef JEUPACMAN_H_
#define JEUPACMAN_H_

#include <drivers/ClavierV.h>
#include <drivers/PortSerie.h>

#include "config.h"
#include "PlateauPacman.h"
#include "Algorithme/Dijkstra.h"

/**
 * @file Pacman.h
 * @class Pacman
 * @brief une description du jeu
 */


#include <sextant/Activite/Threads.h>

class JeuPacman : public Threads{
	PlateauPacman *lePlateau;
	ClavierV *clavier;
	EcranV *ecran;
public:

	JeuPacman(EcranV *e, ClavierV *c, PlateauPacman *plateau);
	void run();
	void launch();
	void update(int i);
	int initLevel();
	bool resolutionAutomatique();
	void initAccueil();
	void intro();
	void initPanel(int * score, int * vie);
	void updatePanel(int * score, int * vie);
	void AnimationVictoire();

};

#endif /* Pacman_H_ */
