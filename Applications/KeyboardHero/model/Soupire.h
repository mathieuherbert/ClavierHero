/*
 * Soupire.h
 *
 *  Created on: 20 oct. 2013
 *      Author: julienderay
 */

#ifndef SOUPIRE_H_
#define SOUPIRE_H_
#include "../Note.h"
#include "Puls.h"
class Soupire : public Note {

public:
	Soupire(Puls* temps, EcranV *anEcran, Timer *aTimer);
};


#endif /* SOUPIRE_H_ */
