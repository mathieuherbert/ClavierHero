/*
 * AffichageFin.h
 *
 *  Created on: 29 oct. 2013
 *      Author: mathieu
 */

#ifndef AFFICHAGEFIN_H_
#define AFFICHAGEFIN_H_

#include "drivers/ClavierV.h"

class AffichageFin {
public:
	static void afficherBonneFin(EcranV* e);
	static void afficherMauvaiseFin(EcranV* e);
};

#endif /* AFFICHAGEFIN_H_ */
