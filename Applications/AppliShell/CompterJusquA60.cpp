/*
 * CompterJusquA60.cpp
 *
 *  Created on: 8 déc. 2010
 *      Author: Antoine
 */

#include "CompterJusquA60.h"

CompterJusquA60::CompterJusquA60(ShellV *shellV, EcranV *ecranV,Timer *timer) {
	shellV=shellV;
	timer=timer;

}

void CompterJusquA60::run() {
	compterJusquA60();
}
void CompterJusquA60::compterJusquA60(){
	int temp=0;
	temp=timer->getSecondes();

	while(temp<temp+60){
	ecranV->afficherChiffre(2,42,temp);
	temp=timer->getSecondes();
	}
	killsoft();
}
void CompterJusquA60::killSoft(){
	//à faire
}
static IntApp CompterJusquA60::getClone(){
	return new CompterJusquA60();
}
