#include "ClavierP.h"

extern bool modifBuf;
extern char buf[256];
extern int posBuf;

extern int console; // numero de la console active

extern Semaphore *semaphoreClavier;


//char *tab;

//int console;

int position[MAXCONSOLE];
Semaphore *semClavierV[MAXCONSOLE];
char buffeur[MAXCONSOLE][TAILLE_BUF_CLAVIER];

ClavierP::ClavierP(EcranV *e){
	ecran=e;
	positioncourante=0;
	for (int i=0;i < MAXCONSOLE; i++) position[i]=-1;
	for (int i=0;i < MAXCONSOLE; i++) semClavierV[i]= new Semaphore();
}


void ClavierP::run(){

while(true) {
//	ecran->miniprintf("Avant P Caractere console %d\n",console);
	semaphoreClavier->P();
//	ecran->miniprintf("Après P Caractere console %d\n",console);

	if (positioncourante<(TAILLE_BUF_CLAVIER-1)) {
			positioncourante=positioncourante+1;
			if (position[console]<(TAILLE_BUF_CLAVIER-1)) {
				position[console]++;
				buffeur[console][position[console]] = buf[positioncourante-1];
			}
			else {
				position[console]=0;
				buffeur[console][position[console]] = buf[positioncourante-1];
			}
	}
	else {
		positioncourante=0;
		if (position[console]<(TAILLE_BUF_CLAVIER-1)) {
			position[console]++;
			buffeur[console][position[console]] = buf[(TAILLE_BUF_CLAVIER-1)];
		}
		else {
			position[console]=0;
			buffeur[console][position[console]] = buf[(TAILLE_BUF_CLAVIER-1)];
		}
	}
//	ecran->miniprintf("Caractere %c, dans console %d\n",buffeur[console][position[console]],console);
	semClavierV[console]->V();
}
}
