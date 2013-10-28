/*
 * AfficherReussiteNote.cpp
 *
 *  Created on: 27 oct. 2013
 *      Author: mathieu
 */

#include "AfficherReussiteNote.h"
#include "lib/String.h"
#include "Applications/Horloge/Horloge.h"
/*
 * Affiche Perfect or Good or Bad en fonction de la synchronisation entre l'appuie de la touche et le passage sur la ligne de validation
 */
AfficherReussiteNote::AfficherReussiteNote(EcranV* e){
	ecran = e;
}

void AfficherReussiteNote::run(){
	Timer* timer = new Timer();
	//affiche le texte pendant 1 seconde
	afficherReussite();
	int temp=0;
	temp=timer->getSecondes();

	int temp2=0;
	temp2=timer->getSecondes();
	while(temp2 < temp+1){
		temp2=timer->getSecondes();
	}
	//effacement du texte
	effacerReussite();
}

void AfficherReussiteNote::afficherReussite(){
	char* mot = selectionnerMot();
	effacerReussite();
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
