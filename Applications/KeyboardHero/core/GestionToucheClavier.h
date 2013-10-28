/*
 * GestionToucheClavier.h
 *
 *  Created on: 25 oct. 2013
 *      Author: Julien Deray, Mathieu Cartaud, Mathieu Herbert
 */

#ifndef GESTIONTOUCHECLAVIER_H_
#define GESTIONTOUCHECLAVIER_H_

#include <drivers/ClavierV.h>
#include <sextant/Activite/Threads.h>
#include "Applications/KeyboardHero/ClavierHero.h"

class GestionToucheClavier : public Threads{
private:
	ClavierV *clavier;
	ClavierHero *clavierHero;
public:
	GestionToucheClavier(ClavierV *c, ClavierHero *ch);
	void run();
};


#endif /* GESTIONTOUCHECLAVIER_H_ */
