/*
 * LecteurClavier.h
 *
 *  Created on: 22 oct. 2012
 *      Author: Administrateur
 */

#ifndef LECTEURCLAVIER_H_
#define LECTEURCLAVIER_H_

#include <drivers/ClavierV.h>
#include <drivers/PortSerie.h>

#include "config.h"
#include "PlateauPacman.h"
#include <sextant/Activite/Threads.h>

class LecteurClavier : public Threads{
	PlateauPacman *lePlateau;
	ClavierV *clavier;
	//EcranV *ecran;
public:
	LecteurClavier(/*EcranV *e,*/ClavierV *c, PlateauPacman *plateau);
	void run();
};

#endif /* LECTEURCLAVIER_H_ */
