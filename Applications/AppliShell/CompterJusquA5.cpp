/*
 * CompterJusquA5.cpp
 *
 *  Created on: 8 déc. 2010
 *      Author: Antoine
 */

#include "CompterJusquA5.h"

CompterJusquA5::CompterJusquA5(ShellV *myshellV, EcranV *myecranV,Timer *mytimer){

	shellV=myshellV;
	timer=mytimer;
	ecranV=myecranV;
}

void CompterJusquA5::run() {
	compterJusquA5();
}
void CompterJusquA5::compterJusquA5(){
	int temp=0;
	temp=timer->getSecondes();

	while(temp<temp+5){
	ecranV->afficherChiffre(1,42,temp);
	temp=timer->getSecondes();
	}
	killSoft();
}
void CompterJusquA5::killSoft(){
	//à faire
}
static IntApp* CompterJusquA5::getClone(EcranV* ecranV){
	return new CompterJusquA5(shellV, ecranV, timer);
}
