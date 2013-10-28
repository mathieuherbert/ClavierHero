/*
 * SonClavierHero.cpp
 *
 *  Created on: 24 oct. 2013
 *      Author: Julien Deray, Mathieu Cartaud, Mathieu Herbert
 */

#include "SonClavierHero.h"
#include <drivers/timer.h>

SonClavierHero::SonClavierHero(EcranV *anEcran, Note* const t_note, int t_duree) {
	ecran = anEcran;
	m_note=t_note;
	duree=t_duree;
}

SonClavierHero::~SonClavierHero(){

}

void SonClavierHero::jouer(int nFrequence){

		int Div;
	    int tmp;
	       //Set the PIT to the desired frequency
	    //Div = 1193180 / nFrequence;//on defini la valeur de compte a rebours a partir de la frequence et de la vitesse de l'oscillateur
	    Div = nFrequence/100;

	    ecrireOctet( 0xb6,0x43);//on informe le timer 2 qu'on va lui envoyer une nouvelle valeur de compte a rebours


	    ecrireOctet((int) (Div) ,0x42);//on envoie le bit bas
	    ecrireOctet((int) (Div >> 8),0x42);//on envoie le bit haut
	       //And play the sound using the PC speaker

	    tmp = lireOctet(0x61);//on connecte le timer 2 au speaker
	     if (tmp != (tmp | 3)) {//en binaire 3 = 11
	    	 tmp = (tmp | 3);
	    	 // ---->>>>> il faut Žcrire 'tmp' dans le port du speaker. Voir etape 3 du fichier Sound Generatrion.doc du rŽpertoire support
	    	 ecran->afficherMot(20,20,"sssss",BLANC);
	    	 ecrireOctet(tmp,0x61);
	    }

}

void SonClavierHero::stop(){
	int tmp = lireOctet(0x61);
	if (tmp != (tmp & 252)) {//en binaire, 252 = 11111100
		ecrireOctet(tmp & 252,0x61);//on deconnecte le timer deux du speaker en mettant les deux derniers bits a 0
	}
	//ecrireOctet(tmp & 252,0x61);
}

int SonClavierHero::puissance(int value, int oct){
	int tmp=value;
	int j=1;
	for(int i=0;i<oct;i++){
		tmp=tmp*2+j;
		j=-j;
	}
	return tmp;
}

void SonClavierHero::compterJusquA(int seconds){
	int temp=0;
	Timer* timer = new Timer();
	temp=timer->getSecondes();
	int temp2 =0;
	while(temp2<temp+seconds){
		temp2=timer->getSecondes();
	}
	//killsoft();
}

void SonClavierHero::note(Note* note, int time){
	jouer(puissance(note->getHauteur(),note->getOctave()));
	//compterJusquA(time);
	//int tmp = lireOctet(0x61);
	Timer* timer = new Timer();
	int from = timer->getCsecondes();
	int to = from + time;
	while (from < to) {
		from = timer->getCsecondes();
	}
	//jouer(1193180 );
	//stop();
}
void SonClavierHero::run(){
	note(m_note,duree);
}
