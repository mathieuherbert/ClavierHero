/*
 * BlocAliens.cpp
 *
 *  Created on: 27 oct. 2008
 *      Author: Aurélien
 */

#include "BlocAliens.h"
#include "SpaceInvaders.h"

BlocAliens::BlocAliens(TimerSpaceInvaders *t, Espace *e, const int niveau, int posL, int posC) {
	timer = t;
	espace = e;

	direction = DEPL_DROITE;
	vitesseBlocInitiale = Config::getVitesseDeplacementBlocAlien(niveau);
	ecartGauche = 0;
	positionLigne = posL;
	positionColonne = posC;
	largeur = Config::getLargeurBlocAlien(niveau);
	hauteur = Config::getHauteurBlocAlien(niveau);

	if(niveau%2 == 0){
		//Boss
		ajouterAlien(0, 0, EntiteFactory::creerBoss(niveau));
	} else {
		for (int i = 0; i < largeur; i++) {
			int ligne = 0;
			ajouterAlien(ligne++, i, EntiteFactory::creerAlienRobot(niveau));
			if(hauteur >= 6)
				ajouterAlien(ligne++, i, EntiteFactory::creerAlienRobot(niveau));
			ajouterAlien(ligne++, i, EntiteFactory::creerAlienBat(niveau));
			ajouterAlien(ligne++, i, EntiteFactory::creerAlienBat(niveau));
			ajouterAlien(ligne++, i, EntiteFactory::creerAlienDoob(niveau));
			if(hauteur >= 5)
				ajouterAlien(ligne++, i, EntiteFactory::creerAlienBat(niveau));
		}
	}

	nombreAliensInitial = calculerNombreAliensRestants();
	ajusterVitesse();
}

BlocAliens::~BlocAliens(){
	delete blocAliens;
}

int BlocAliens::getPositionLigne() {
	return positionLigne;
}
int BlocAliens::getPositionColonne() {
	return positionColonne;
}
int BlocAliens::getEcartGauche() {
	return ecartGauche;
}
int BlocAliens::getHauteur() {
	return hauteur;
}
int BlocAliens::getLargeur() {
	return largeur;
}
int BlocAliens::getDirection() {
	return direction;
}

int BlocAliens::calculerNombreAliensRestants() {
	int sommeAliens = 0;
	for (int ligne = 0; ligne < hauteur; ligne++) {
		for (int colonne = ecartGauche; colonne < ecartGauche+largeur; colonne++) {
			if (getAlien(ligne, colonne) != NULL)
				sommeAliens++;
		}
	}
	nombreAliens = sommeAliens;
	return nombreAliens;
}
int BlocAliens::getNombreAliensRestants() {
	return nombreAliens;
}

Alien *BlocAliens::getAlien(int ligne, int colonne) {
	return blocAliens[ligne * LARGEUR_BLOC_ALIEN_MAX + colonne];
}
int BlocAliens::getPositionLigne(Alien *alien) {
	return (alien->getPositionLigne() - positionLigne) / ALIGN_VERT;
}
int BlocAliens::getPositionColonne(Alien *alien) {
	return (alien->getPositionColonne() - positionColonne) / ALIGN_HORI;
}

void BlocAliens::effacer() {
	for (int ligne = 0; ligne < hauteur; ligne++) {
		for (int colonne = ecartGauche; colonne < ecartGauche+largeur; colonne++) {
			if (getAlien(ligne, colonne) != NULL) {
				getAlien(ligne, colonne)->effacer();
			}
		}
	}
}
void BlocAliens::dessiner() {
	for (int ligne = 0; ligne < hauteur; ligne++) {
		for (int colonne = ecartGauche; colonne < ecartGauche+largeur; colonne++) {
			if (getAlien(ligne, colonne) != NULL) {
				getAlien(ligne, colonne)->dessiner();
			}
		}
	}
}
void BlocAliens::deplacer() {
	effacer();
	for (int ligne = 0; ligne < hauteur; ligne++) {
		for (int colonne = ecartGauche; colonne < ecartGauche+largeur; colonne++) {
			if (getAlien(ligne, colonne) != NULL) {
				getAlien(ligne, colonne)->deplacerPosition(direction);
			}
		}
	}
	dessiner();
	switch (direction) {
	case DEPL_BAS:
		positionLigne++;
		break;
	case DEPL_HAUT:
		positionLigne--;
		break;
	case DEPL_DROITE:
		positionColonne++;
		break;
	case DEPL_GAUCHE:
		positionColonne--;
		break;
	}
}

void BlocAliens::ajouterAlien(int ligne, int colonne, Alien *alien) {
	//Position des Aliens dans l'espace
	alien->setPositionLigne(positionLigne + ligne * ALIGN_VERT);
	alien->setPositionColonne(positionColonne + colonne * ALIGN_HORI);

	blocAliens[ligne * LARGEUR_BLOC_ALIEN_MAX + colonne] = alien;
}
void BlocAliens::retirerAlien(Alien *alien) {
	//	ecran->afficherChiffreCommente(22, 1, "Suppr si colo:", largeur+ecartGauche-1, 2);
	//	ecran->afficherChiffreCommente(23, 1, "PositionLigne:", getPositionLigne(alien), 2);
	//	ecran->afficherChiffreCommente(24, 1, "PositionColon:", getPositionColonne(alien), 2);

	blocAliens[getPositionLigne(alien) * LARGEUR_BLOC_ALIEN_MAX + getPositionColonne(
			alien)] = NULL;
	SpaceInvaders::score += alien->getPointsDeVieInitiaux();
	alien->effacer();

	if (getPositionColonne(alien) == ecartGauche)
		ajusterDimensionAGauche();
	if (getPositionColonne(alien) == largeur + ecartGauche - 1)
		ajusterDimensionADroite();
	if (getPositionLigne(alien) == hauteur - 1)
		ajusterDimensionEnBas();

	calculerNombreAliensRestants();
	ajusterVitesse();
}

void BlocAliens::ajusterVitesse() {
	for (int i = 2; i <= 4; i *= 2) {
		if(nombreAliensInitial != 1){
			if (nombreAliens <= nombreAliensInitial / i)
				timer->setTimerDeplacementAliens(vitesseBlocInitiale / (i));
		} else {
			if (getAlien(0, 0)->getPointsDeVie() <= getAlien(0, 0)->getPointsDeVieInitiaux() / i)
				timer->setTimerDeplacementAliens(vitesseBlocInitiale / (i));
		}
	}
}

void BlocAliens::tirerMissile() {
	int posC = 0;
	int posL = 0;
	int compteur = 0;

	if(largeur == hauteur == 1){
		if(nombreAliensInitial == 1)
			posC = positionColonne + 4;
		else
			posC = positionColonne + 2;
		posL = positionLigne + 3;
	} else {
		bool alienPresent = false;
		int numCol = 0;
		do {
			numCol = random.nextInt(largeur) + ecartGauche;
			for (int i = 0; i < hauteur; i++) {
				if (getAlien(i, numCol) != NULL) {
					alienPresent = true;
					posL = getPositionLigne() + (i + 1) * (ALIGN_VERT) - 1;
				}
			}
			compteur ++;
		} while (!alienPresent && compteur < 10);
		posC = (numCol - 1) * ALIGN_HORI + 1 + getPositionColonne();
	}
	MissileAlien::lancerNouveauMissile(posL, posC);
}

void BlocAliens::ajusterDimensionsBloc() {
	ajusterDimensionADroite();
	ajusterDimensionAGauche();
	ajusterDimensionEnBas();
}

void BlocAliens::ajusterDimensionAGauche() {
	if(largeur == 0)
		return;
	int somme = 0;
	for (int i = 0; i < hauteur; i++) {
		if (getAlien(i, ecartGauche) != NULL)
			somme++;
	}
	if (somme == 0) {
		largeur--;
		ecartGauche++;
		ajusterDimensionAGauche();
	}
}
void BlocAliens::ajusterDimensionADroite() {
	if(largeur == 0)
		return;
	int somme = 0;
	for (int i = 0; i < hauteur; i++) {
		if (getAlien(i, largeur + ecartGauche - 1) != NULL)
			somme++;
	}
	if (somme == 0) {
		largeur--;
		ajusterDimensionADroite();
	}
}
void BlocAliens::ajusterDimensionEnBas() {
	if(hauteur == 0)
		return;
	int somme = 0;
	for (int i = ecartGauche; i < ecartGauche+largeur; i++) {
		if (getAlien(hauteur - 1, i) != NULL)
			somme++;
	}
	if (somme == 0) {
		hauteur--;
		ajusterDimensionEnBas();
	}
}

/*

 // Question : est-ce que les aliens font tous la même largeur, hauteur ???*
 // Ou se fait la gestion de la collision avec le missile ou le bunker, qui remplace l'alien par l'entite vide et
 // et à jour le bloc ???
 // Peut-on faire un bloc rectangulaire composé d'alien et d'entité vide (espace) de même largeur, ça faciliterait
 // pas mal la gestion.

 //Les aliens font tous du 4*3 ça m'arrange bien


 */

void BlocAliens::run() {
	dessiner();

	while (true) {
		timer->getDeplacementAliens()->P();
		if(espace->niveauTermine())
			Exit();

		if (direction == DEPL_BAS) {
			if (positionColonne <= 1) {
				direction = DEPL_DROITE;
			} else {
				direction = DEPL_GAUCHE;
			}
		} else if (((positionColonne + (largeur + ecartGauche) * ALIGN_HORI)
				>= LARGEUR + 1 && direction == DEPL_DROITE) || (positionColonne
						+ ecartGauche * ALIGN_HORI <= 1 && direction == DEPL_GAUCHE)) {
			direction = DEPL_BAS;
		}

		deplacer();
		tirerMissile();
	}
}
