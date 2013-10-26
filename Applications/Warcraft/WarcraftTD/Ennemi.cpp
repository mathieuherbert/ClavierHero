/*
 * Ennemi.cpp
 *
 *  Created on: 25 nov. 2011
 *      Author: Xan
 */

#include "Ennemi.h"

Ennemi::Ennemi(int pv, int avancement, int vitesseDeplacement, int niveau):
pv(pv),vitesseDeplacement(vitesseDeplacement),niveau(niveau),horloge(0),ralentissement(0){}

Ennemi::Ennemi(int niveau):
									horloge(0),pv(10*niveau),vitesseDeplacement(1),niveau(niveau){}

int Ennemi::getPv(){
	return this->pv;
}

int Ennemi::getVitesseDeplacement(){
	return this->vitesseDeplacement;
}

int Ennemi::getNiveau(){
	return this->niveau;
}

bool Ennemi::round(){
	if(ralentissement--==0){
		vitesseDeplacement=1;
	}
	else if(horloge++>=vitesseDeplacement){
		horloge-=vitesseDeplacement;
		return true;
	}
	return false;
}
//Return: true si l'ennemi est mort de cette attaque, false sinon.
bool Ennemi::subirAttaque(Attaque *attaque){

	if(attaque->getParalysie()!=0){
		horloge-=2*attaque->getParalysie();
	}
	if(attaque->getRalentissement()!=0){
		ralentissement=attaque->getRalentissement()*7;
		vitesseDeplacement=2;
	}

	pv-=attaque->getDegats();
	return pv<=0;

}
