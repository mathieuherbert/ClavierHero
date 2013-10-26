/*
 * Attaque.cpp
 *
 *  Created on: 12 déc. 2011
 *      Author: Fabien
 */

#include "Attaque.h"

Attaque::Attaque(int degats, int ralentissement, int paralysie, int zone){

	this->ralentissement=ralentissement;
	this->degats=degats;
	this->paralysie=paralysie;
	this->zone=zone;
}

int Attaque::getRalentissement(){
	return this->ralentissement;
}
int Attaque::getDegats(){
	return this->degats;
}

int Attaque::getParalysie(){
	return this->paralysie;
}
int Attaque::getZone(){
	return this->zone;
}


