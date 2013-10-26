/*
 * Joueur.cpp
 *
 *  Created on: 12 déc. 2010
 *      Author: Frédéric
 */

#include "Joueur.h"
#include "Batiment.h"
#include "Unite.h"
#include "Position.h"
#include "Map.h"

Joueur::Joueur(bool humain){
	if(humain){
		batiments[0] = new Batiment(Batiment::QUARTIER_GENERAL,new Position(13,6));
	}
	else{
		batiments[0] = new Batiment(Batiment::QUARTIER_GENERAL,new Position(13,63));
	}
	population = 0;
	nbBatiment = 1;
	gold = 0;
	bois = 0;
}

bool Joueur::unitePerdDesPV(Position *positionDeLUnite,int pvPerdus){
	int i=0;
	for(;i<population;i++)
		if(unites[i]->position==positionDeLUnite)
			break;
	if(unites[i]->perdDesPV(pvPerdus)){
		delete(unites[i]);
		unites[i]=unites[--population];
		return true;
	}
	return false;
}

bool Joueur::batimentPerdDesPV(int pvPerdus){
	return batiments[0]->perdDesPV(pvPerdus);
}

void Joueur::attaquer(){

	for(int i=0;i<population;i++)
			if(!unites[i]->paysan)
				unites[i]->objectif = new Position(13,6);
}

void Joueur::attaquerHumain() {
	for(int i=0;i<population;i++)
			if(!unites[i]->paysan)
				unites[i]->objectif = new Position(13,63);
}

int Joueur::nombrePaysanBois(){
	int aRetourner = 0;
	for(int i=0;i<population;i++)
		if(unites[i]->paysan && unites[i]->objetRecherche==Map::BOIS)
			aRetourner++;
	return aRetourner;
}

int Joueur::nombrePaysanOr(){
	int aRetourner = 0;
	for(int i=0;i<population;i++)
		if(unites[i]->paysan && unites[i]->objetRecherche==Map::OR)
			aRetourner++;
	return aRetourner;
}

int Joueur::nombreGuerriers(){
	int aRetourner = 0;
	for(int i=0;i<population;i++)
		if(!unites[i]->paysan)
			aRetourner++;
	return aRetourner;
}

void Joueur::creerPaysan(int materiauRecherche,Position *position,Position *objectif){
	if(population<30)
		unites[population++] = new Unite(position,objectif,true,materiauRecherche);
}

void Joueur::creerGuerrier(Position *position){
	if(population<30)
		unites[population++] = new Unite(position,new Position(position),false,0);
}
