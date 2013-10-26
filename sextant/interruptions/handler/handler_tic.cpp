#include "handler_tic.h"

int a = 0;
int b = 0;
int c = 0;
/**
 * Permet de compter le nombre d'interruption de l'horloge.
 */
int compt = 0;
int secondes =0;
int dsecondes = 0;
int csecondes = 0;

int getseconds(){
	return secondes;
}

int getdseconds(){
	return dsecondes;
}

int gettime(){
return compt;
}

void ticTac(int o) {
	compt++;
	if(compt%1000==0) {
		secondes++;
		if(a == 9)
			a=0;
		else
			a++;
	}
	if(compt%100==0) {
		dsecondes++;
		if(b == 9)
			b=0;
		else
			b++;
	}
	if(compt%10==0) {
		csecondes++;
		if(c == 9)
			c = 0;
		else c++;
	}
}
