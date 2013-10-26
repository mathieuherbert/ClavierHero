#ifndef SON_H
#define SON_H

#include <sextant/types.h>
#include "../drivers/ClavierV.h"
#include "../hal/fonctionsES.h"
/**
 * @file Son.h
 * @class Son
 * @brief Gestion de la sortie son
 */

class Son {

public :

	int octave;

	void jouer(int nFrequence);
	void stop();
	void note(char touche);
	int puissance(int value, int pow);
};

#endif
