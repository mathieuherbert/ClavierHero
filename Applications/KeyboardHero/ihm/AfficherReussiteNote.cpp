/*
 * AfficherReussiteNote.cpp
 *
 *  Created on: 27 oct. 2013
 *      Author: mathieu
 */

#include "AfficherReussiteNote.h"
#include "lib/String.h"
#include "Applications/Horloge/Horloge.h"

AfficherReussiteNote::AfficherReussiteNote(EcranV* e){
	ecran = e;
}

void AfficherReussiteNote::run(){
	Timer* timer = new Timer();

	afficherReussite();
	int temp=0;
	temp=timer->getSecondes();

	int temp2=0;
	temp2=timer->getSecondes();
	while(temp2 < temp+1){
		temp2=timer->getSecondes();
	}
	effacerReussite();
}

void AfficherReussiteNote::afficherReussite(){
	char* mot = selectionnerMot();
	ecran->afficherMot(13, 65, mot, ROUGE);
}

char* AfficherReussiteNote::selectionnerMot(){
	char* mot = "";
	if (reussite == 2) {
		mot = "Perfect";
	} else if (reussite == 1) {
		mot = "Good";
	} else if (reussite == 0) {
		mot = "Bad";
	}
	return mot;
}

void AfficherReussiteNote::effacerReussite(){
	ecran->afficherMot(13, 65, "TTTTTTTTTTTTTTTTT", NOIR);
}

void AfficherReussiteNote::setReussite(int i){
	reussite = i;
}
