/*
 * LecteurClavier.h
 *
 *  Created on: 22 oct. 2012
 *      Author: Administrateur
 */

#ifndef LECTEURTOUCHE_H_
#define LECTEURTOUCHE_H_

#include <drivers/ClavierV.h>
#include <drivers/PortSerie.h>

#include "config.h"
#include "PlateauPacman.h"
#include <sextant/Activite/Threads.h>

class LecteurTouche : public Threads{
	PlateauPacman *lePlateau;
	ClavierV *clavier;
	//EcranV *ecran;
public:
	LecteurTouche(ClavierV *c, PlateauPacman *plateau);
	void run();
};

#endif /* LECTEURCLAVIER_H_ */
