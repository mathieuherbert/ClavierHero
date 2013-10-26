/*
 * Batiment.cpp
 *
 *  Created on: 12 déc. 2010
 *      Author: Frédéric
 */
#include "Batiment.h"
#include "Position.h"

Batiment::Batiment(int type,Position *position):type(type),position(position),pv(20){}

bool Batiment::perdDesPV(int pvPerdus){
	pv-=pvPerdus;
	return pv<1;
}
