/*
 * Conversion.h
 *
 *  Created on: 20 oct. 2013
 *      Author: julienderay
 */

#ifndef CONVERSION_H_
#define CONVERSION_H_

#include "../model/Hauteur.h"
#include "../model/Puls.h"
#include "../model/Octave.h"
#include "../model/Touche.h"
#define MULTIPLICATEUR 4
class Conversion {
public:
	static double fromBPMtoSec(int bpm);
};


#endif /* CONVERSION_H_ */
