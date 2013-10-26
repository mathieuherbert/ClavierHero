/*
 * FondEspace.cpp
 *
 *  Created on: 23 oct. 2008
 *      Author: Aurélien
 */

#include "FondEspace.h"


FondEspace::FondEspace(int niveau) {
	fondEspace = "                                                                                                                                                                                                                                                                                                                                                                                                                                         _____                                                                          \057  ___|                                                                         \134 `--. _ __   __ _  ___ ___                                                      `--. \134 '_ \134 \057 _` |\057 __\057 _ \134                                                    \057\134__\057 \057 |_) | (_| | (_|  __\057                                                    \134____\057| .__\057 \134__,_|\134___\134___|                                              _____       | |          _                                                     |_   _|      |_|         | |                                                      | | _ ____   ____ _  __| | ___ _ __ ___                                         | || '_ \134 \134 \057 \057 _` |\057 _` |\057 _ \134 '__\057 __|                                       _| || | | \134 V \057 (_| | (_| |  __\057 |  \134__ \134                                       \134___\057_| |_|\134_\057 \134__,_|\134__,_|\134___|_|  |___\057                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                     ********************************************************************************";

	for(int index=0; index<LARGEUR*HAUTEUR; index++){
		couleurArPlanEspace[index] = NOIR;
		couleurPrPlanEspace[index] = Config::getCouleurFondEspace(niveau);
	}

	for(int ligne=0; ligne<HAUTEUR; ligne++) {
		for(int colonne=0; colonne<LARGEUR; colonne++) {
			espaceVide[ligne*LARGEUR + colonne] = new EntiteVide(ligne, colonne, getCharAt(ligne, colonne), getCouleurPrPlanAt(ligne, colonne));
		}
	}
}

char* FondEspace::getCharAt(int ligne, int colonne) {
	return &fondEspace[ligne*LARGEUR + colonne];
}
Couleur FondEspace::getCouleurPrPlanAt(int ligne, int colonne) {
	return couleurPrPlanEspace[ligne*LARGEUR + colonne];
}
Couleur FondEspace::getCouleurArPlanAt(int ligne, int colonne) {
	return couleurArPlanEspace[ligne*LARGEUR + colonne];
}

EntiteVide *FondEspace::getEntiteVide(int ligne, int colonne) {
	return espaceVide[ligne*LARGEUR + colonne];
}
