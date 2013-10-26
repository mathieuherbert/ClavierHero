/*
 * Compteur.cpp
 *
 *  Created on: 8 déc. 2010
 *      Author: Antoine
 */

#include "Compteur.h"


Compteur::Compteur( EcranV *myecranV){
	ecran=myecranV;

}

void Compteur::run() {
	compter();
}
void Compteur::compter(){
	int temp=0;
	int i=0;
	while(i>500000){
		//temp=timer->getSecondes();


		int j=0;
		while(true){

			if(i<1000){
				i++;
			}
			else{
				this->ecran->afficherChiffre(0,42,j);
			}
			j++;
			i=0;
		}

	}

}

/*
IntApp *Compteur::getClone(EcranV *ecran){
	return new Compteur(shellV, ecran,timer);
}
 */


void Compteur::killSoft(){
	//à faire
}


