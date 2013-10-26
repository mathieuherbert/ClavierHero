/*
 * FabriqueDennemi.cpp
 *
 *  Created on: 12 déc. 2011
 *      Author: Math
 */

#include <Applications/Warcraft/warcraftTD/FabriqueDennemi.h>

FabriqueDennemi::FabriqueDennemi():lvl(0),horloge(0),nombreVague(0){
	for (int i=0;i<lvlmax;i++){
		cadence[i]=10;
		nombre[i]=20;
	}


}

Ennemi *FabriqueDennemi::getEnnemi(){
	horloge-=cadence[lvl];
	int l=lvl;
	nombreVague++;
	if(nombreVague>=nombre[lvl]){
		horloge-=pause;
		nombreVague=0;
		++lvl;
	}
	return new Ennemi(1+l);
}

bool FabriqueDennemi::round(){
	return (++horloge==cadence[lvl])&&(lvl<lvlmax);
}

int FabriqueDennemi::getlvl(){
	return lvl;
}

int FabriqueDennemi::getlvlmax(){
	return lvlmax;
}


