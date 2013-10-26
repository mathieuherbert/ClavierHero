/*
 * Entite.cpp
 *
 *  Created on: 17 oct. 2008
 *      Author: Aurélien
 */

#include "EntiteBase.h"
#include "Applications/SpaceInvaders/Espace.h"

Espace* EntiteBase::espace = NULL;
EcranV* EntiteBase::ecran = NULL;


EntiteBase::EntiteBase(int v, int ligne, int colonne,
		char *a, int h, int l, Couleur c) {
	vie = v;
	vieInitiale = v;
	positionLigne = ligne;
	positionColonne = colonne;
	affichage = a;
	hauteur = h;
	largeur = l;
	couleur = c;

	semaphore.V();
}

EntiteBase::~EntiteBase(){
	delete &vie;
	delete &vieInitiale;
	delete &positionLigne;
	delete &positionColonne;
	delete affichage;
	delete &hauteur;
	delete &largeur;
	delete &couleur;
	delete this;

}

int EntiteBase::getPointsDeVie(){
	return vie;
}
int EntiteBase::getPointsDeVieInitiaux(){
	return vieInitiale;
}
int EntiteBase::getPositionLigne(){
	return positionLigne;
}
int EntiteBase::getPositionColonne(){
	return positionColonne;
}
int EntiteBase::getHauteur(){
	return hauteur;
}
int EntiteBase::getLargeur(){
	return largeur;
}
int EntiteBase::getColonneCentre(){
	return largeur/2 + positionColonne;
}

Couleur EntiteBase::getCouleur(){
	return couleur;
}

Semaphore *EntiteBase::getSemaphore(){
	return &semaphore;
}


void EntiteBase::deplacer(int direction){
	effacer();
	deplacerPosition(direction);
	dessiner();
}
void EntiteBase::deplacerPosition(int direction){
	semaphore.P();
	if(direction == DEPL_GAUCHE)
		positionColonne --;
	if(direction == DEPL_DROITE)
		positionColonne ++;
	if(direction == DEPL_HAUT)
		positionLigne --;
	if(direction == DEPL_BAS)
		positionLigne ++;
	semaphore.V();
}

void EntiteBase::dessiner(){
	for(int ligne=getPositionLigne(); ligne<getPositionLigne()+getHauteur(); ligne++){
		for(int colonne=getPositionColonne(); colonne<getPositionColonne()+getLargeur(); colonne++){
			espace->setEntite(this, ligne, colonne);
			ecran->afficherCaractere(ligne, colonne,
					couleur, espace->getCouleurArPlanAt(ligne, colonne),
					*(affichage + (ligne-positionLigne)*largeur +(colonne-positionColonne)));
		}
	}
}
void EntiteBase::effacer(){
	for(int ligne=positionLigne; ligne<positionLigne+getHauteur(); ligne++){
		for(int colonne=positionColonne; colonne<positionColonne+getLargeur(); colonne++){
			if(ligne>=0 && ligne<=25 && colonne>=0 && colonne<=80)
				espace->setEntiteVide(ligne, colonne);
		}
	}
}

void EntiteBase::setEcran(EcranV *ec){
	ecran = ec;
}
void EntiteBase::setEspace(Espace *es){
	espace = es;
}

