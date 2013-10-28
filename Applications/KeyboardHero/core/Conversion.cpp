/*
 * Conversion.cpp
 *
 *  Created on: 20 oct. 2013
 *      Author: Julien Deray, Mathieu Cartaud, Mathieu Herbert
 */

#include "Conversion.h"
double Conversion::fromBPMtoSec(int bpm) {
	//return 60 * pow(bpm, -1);
	return 60.0 *(1.0/(double)bpm);
}
