#ifndef GRILLE_H
#define GRILLE_H

#include "CaseSP.h"
#include "Raquette.h"
#include "config.h"

/**
 * @file Grille.h
 * @class Grille
 * @brief La grille du jeu avec des murs, deux raquettes et des balles.
 */

class Grille {

	/*
	 * Tableau des cases du jeu.
	 */

	CaseSP tab[LARGEUR][LARGEUR];

	/**
	 * Nombre de balles créées lors de l'initialisation du jeu.
	 */
	Raquette raqg, raqd;


public :
	/**
	 * Construit la grille avec les murs, les zones privées, le nombre de verrous associés, les raquettes et les trous.
	 */
	Grille(EcranV *);
	Grille();

	/**
	 * Associe un écran à la grille et affiche cette dernière.
	 */
	void affiche();
	void init(EcranV *);

	CaseSP* getCase(int x,int y);

	void monterRaquette(int gd);
	void descendreRaquette(int gd);
	void initRaquette(int y,int lg);


};
#endif
