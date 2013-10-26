/*
 * CasePacman.cpp
 *
 *  Created on: 5 oct. 2012
 *      Author: killerider
 */

#include "CasePacman.h"

void CasePacman::init(int xx, int yy, EcranV *e) {
	x = xx ;
	y = yy ;
	setCaseVide();
	ecran=e;
}

bool CasePacman::estMur(){
	return etat==MUR;
}

bool CasePacman::estFruit(){
	return etat==FRUIT;
}

bool CasePacman::estTeleportG(){
	return etat==TELEPORTG;
}

bool CasePacman::estTeleportD(){
	return etat==TELEPORTD;
}
int CasePacman::getEtat() {
	return etat;
}

void CasePacman::setEcran(EcranV *e) {
	ecran = e;
}

EcranV *CasePacman::getEcran() {
	return ecran;
}

int CasePacman::getx(){
	return x;
}

int CasePacman::gety(){
	return y;
}

void CasePacman::setCaseVide(){
	etat=VIDE;
}

void CasePacman::setCaseMur(){
	etat=MUR;
}

void CasePacman::setCaseFruit(){
	etat=FRUIT;
}

void CasePacman::setCaseTeleportG(){
	etat=TELEPORTG;
}

void CasePacman::setCaseTeleportD(){
	etat=TELEPORTD;
}


void CasePacman::paint(){

	switch(etat) {
	case VIDE:
		ecran->afficherCaractere(x, y, NOIR, NOIR, ' ');
		break;
	case MUR:
		ecran->afficherCaractere(x, y, BLEU, BLEU, ' ');
		break;
	case FRUIT:
		ecran->afficherCaractere(x, y, JAUNE, NOIR, 250);
		break;
	case TELEPORTD:
		ecran->afficherCaractere(x, y, VERT, NOIR, 175);
		break;
	case TELEPORTG:
		ecran->afficherCaractere(x, y, VERT, NOIR, 174);
		break;
	}

}



