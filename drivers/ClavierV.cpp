#include "ClavierV.h"

//extern bool modifBuf;
//extern char buf[256];
//extern int posBuf;

//extern Semaphore semaphoreClavier;


extern EcranV ecranV[6];

ClavierV::ClavierV(Semaphore *sem,char *buffeur){
	semaphoreClavierV = sem;
	buf=buffeur;
	positioncourante=0;
}


char ClavierV::getChar(){
//	ecranV[3].miniprintf("Test Avant P %d\n",semaphoreClavierV->Valeur());
	semaphoreClavierV->P();
//	ecranV[3].miniprintf("Test Apres P\n");

	if (positioncourante<(TAILLE_BUF_CLAVIER-1)) {
			positioncourante=positioncourante+1;
			return buf[positioncourante-1];
	}
	else {
		positioncourante=0;
		return buf[(TAILLE_BUF_CLAVIER-1)];
	}
}

char* ClavierV::getString(){

	tab = new char[256];
	int i=0;

	tab[i] = getChar();
	while (tab[i]!='\n') 	tab[++i] = getChar();
	tab[i]='\0';
	return tab;
}

void ClavierV::set_leds(void) {
//	ecrireOctet(0x60, 0xED);
}
