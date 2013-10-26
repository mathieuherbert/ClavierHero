/*
 * PortSerie.cpp
 *
 *  Created on: 4 août 2008
 *      Author: jmenaud
 */

#include "PortSerie.h"

/* definition des registres du 8250 */
int RBR[4]={0x3F8, 0x2F8, 0x370, 0x270},
	THR[4]={0x3F8, 0x2F8, 0x370, 0x270},
	DLL[4]={0x3F8, 0x2F8, 0x370, 0x270},
	DLH[4]={0x3F9, 0x2F9, 0x371, 0x271},
	IER[4]={0x3F9, 0x2F9, 0x371, 0x271},
	IIR[4]={0x3FA, 0x2FA, 0x372, 0x272},
	LCR[4]={0x3FB, 0x2FB, 0x373, 0x273},
	MCR[4]={0x3FC, 0x2FC, 0x374, 0x274},
	LSR[4]={0x3FD, 0x2FD, 0x375, 0x275},
	MSR[4]={0x3FE, 0x2FE ,0x376, 0x276};

void PortSerie::init_Com(int port, long vitesse, int longueur, char parite, char stop) {
	unsigned char tempo;

	ecrireOctet(0,IER[port]);
	ecrireOctet(128,LCR[port]);

	tempo = (unsigned char)((115200 / vitesse)&0x000000FF);
	ecrireOctet(tempo,DLL[port]);

	tempo = (unsigned char)(((115200 / vitesse)&0x0000FF00)>>8);
	ecrireOctet(tempo,DLH[port]);

	switch(parite) {
		case 'P': tempo = PAIRE; break;
		case 'I': tempo = IMPAIRE; break;
		case 'S': tempo = SANS; break;
	}

	if (stop == 2)
			tempo = tempo | 0x04;
	tempo = tempo | (longueur - 5);
	ecrireOctet(tempo,LCR[port]);
}

void PortSerie::ecrireMot(const char *mot) {
    int i = 0;
    while(mot[i] != '\0'){
	ecrireOctet(mot[i], 0x3F8);
	i++;
    }
}

void PortSerie::ecrireCaractere(char c) {
	ecrireOctet(c, 0x3F8);
}

char PortSerie::lireCaractere() {
	char c;
	Lsr l;

	l.c = lireOctet(0x3F8+LELSR);
	while (l.s.DR==0){
		l.c = lireOctet(0x3F8+LELSR);
	}

	return lireOctet(0x3F8);

	if ((c=(lireOctet(0x3F8)) & 0x01)==1)
		return(c);
	else
		return(0);
}


void PortSerie::afficherChiffre(const int valeur){
	static const char num[] = {'0','1','2','3','4','5','6','7','8','9'};
	int i,j;
	char resultat[40];
	char chaine[36];
	int reste;
	int count=0;
	int quotient=valeur;

	if(quotient<0) quotient=-quotient;

	chaine[0]='0';

	if(quotient==0) count++;

	while (quotient!=0){
		reste = quotient % 10 ;
		// pour passer chiffre suivant
		quotient = (int) quotient/10;
		// conversion du chiffre en caractere
		chaine[count]=(char) num[reste];
		count=count+1;
	}

	// ajout du signe si valeur est negative
	if (valeur<0){
		chaine[count]='-';
		count=count+1;
	}

	for(i = 0, j=count-1 ; i< count ;i++, j--){
		resultat[j]=chaine[i];
	}

	// ajout du caractere de fin de chaine */
	resultat[count]='\0';

	ecrireMot(resultat);
}
