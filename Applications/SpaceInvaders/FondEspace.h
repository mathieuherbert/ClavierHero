/*
 * FondEspace.h
 *
 *  Created on: 23 oct. 2008
 *      Author: Aurélien
 */

#ifndef FONDESPACE_H_
#define FONDESPACE_H_

#include "sextant/types.h"
#include "ConfigSpaceInvader.h"
#include "Entites/EntiteVide.h"


class FondEspace {

private:
	char *fondEspace; // Table de caractères du fond de l'espace.
	Couleur couleurPrPlanEspace[LARGEUR*HAUTEUR];
	Couleur couleurArPlanEspace[LARGEUR*HAUTEUR];

	/**
	 * Tableau d'entités vides représentant l'espace.
	 */
	EntiteVide *espaceVide[LARGEUR*HAUTEUR];

	char* getCharAt(int ligne, int colonne);

public:
	FondEspace(int niveau);

	Couleur getCouleurPrPlanAt(int ligne, int colonne);
	Couleur getCouleurArPlanAt(int ligne, int colonne);

	EntiteVide *getEntiteVide(int ligne, int colonne);
};

#endif /* FONDESPACE_H_ */
