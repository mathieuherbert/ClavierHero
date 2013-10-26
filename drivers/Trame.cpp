/*
 * Trame.cpp
 *
 *  Created on: 30 nov. 2009
 *      Author: menaud
 */


#include "Trame.h"

Trame::Trame(){
	maTrame.deb_fan='[';
	maTrame.fin_fan=']';
}

void Trame::emettreTrame(const char *message){
	int i=0;

	while (message[i]!='\0' && i<MAXTRAME) {maTrame.monMessage[i]=message[i];i++;}
	maTrame.monMessage[i]=maTrame.fin_fan;

	monportserie.ecrireCaractere(maTrame.deb_fan);
	i=0;
	do {
		monportserie.ecrireCaractere(maTrame.monMessage[i]);
		i++;
	} while(maTrame.monMessage[i-1]!=maTrame.fin_fan);
}

message *Trame::recevoirTrame(){
	int i=0;

	while (monportserie.lireCaractere()!=maTrame.deb_fan) ; // boucler tant que l'on a pas recu le debut de la trame
	do {
		maTrame.monMessage[i]=monportserie.lireCaractere();
		i++;
	} while (maTrame.monMessage[i-1]!=maTrame.fin_fan) ;

	maTrame.monMessage[i-1]='\0';

	return &(maTrame.monMessage);
}
