#include "Unite.h"

Unite::Unite(Position *position,Position *objectif,bool paysan,int objetRecherche){
	this->position = position;
	this->objectif = objectif;
	this->paysan = paysan;
	this->objetRecherche = objetRecherche;
	if(paysan)
		pv = 2;
	else
		pv = 6;
	objetPorte = -1;
}

bool Unite::perdDesPV(int pvPerdus){
	pv-=pvPerdus;
	return pv<1;
}
