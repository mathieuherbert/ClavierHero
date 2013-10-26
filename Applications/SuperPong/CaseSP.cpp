#include "CaseSP.h"

/**
 * @file Case.cpp
 * Implémentation des méthodes de la classes Case.
 */

void CaseSP::init(int xx, int yy) {
	x = xx ; y = yy ;
	setCaseVide();
};

int CaseSP::getEtat() {
	return etat;
};

void CaseSP::setEcran(EcranV* e) {
	ecran = e;
}

EcranV* CaseSP::getEcran() {
	return ecran;
}

void CaseSP::setCaseVide(){
	etat=VIDE;
};

void CaseSP::setCaseTrou(){
	etat=TROU;
};

void CaseSP::setCaseBord(){
	etat=BORD;
};

void CaseSP::paint(){
	ecran->afficherCaractere(x, y, couleurPr(),couleurAr(),Caractere());
};

Couleur CaseSP::couleurPr() {
	switch(etat){
	case VIDE :
		return NOIR;
	case BORD :
		return JAUNE;
	case TROU :
		return NOIR;
	default :
		return BLEU_LEGER;
	}
}

Couleur CaseSP::couleurAr() {
		return GRIS_SOMBRE;
}

char CaseSP::Caractere(){
	switch(etat){
	case VIDE :
		return ' ';
	case BORD :
	case TROU :
		return 219;
	case BALLE :
		return '0';
	default :
		return 'X';
	}
}

/* Ajout TP2
 */

void CaseSP::occupe() {
	etatold=etat;
	etat = BALLE;
	paint();
};

void CaseSP::libere() {
	etat=etatold;
	paint();
};

int CaseSP::EtatOld() {
	return etatold;
};

int CaseSP::Etat() {
	return etat;
};

