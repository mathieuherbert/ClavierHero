#include "EcranP.h"
#include <sextant/interruptions/handler/handler_clavier.h>
#include <sextant/memoire/op_memoire.h>
// Ici nous allons manipuler un tableau ecran dont on fixe l'origine au d�but de la zone m�moire video.

volatile caseEcran* EcranP::origine = (volatile caseEcran*)VIDEO;



EcranP::EcranP(EcranV *ecr){
	ecran = ecr;
	ecranActif = &(ecran[0]);
}

void EcranP::setEcran(int index){
	ecranActif = &(ecran[index]);
	memcpy((void*)origine, ecranActif->tab, LIGNES*COLONNES*sizeof(caseEcran));
}

EcranV *EcranP::getEcranActif(){
	return ecranActif;
}

void EcranP::raffraichir(){
	memcpy((void*)origine, ecranActif->tab, LIGNES*COLONNES*sizeof(caseEcran));
}






