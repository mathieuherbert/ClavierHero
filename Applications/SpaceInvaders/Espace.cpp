/*
 * Espace.cpp
 *
 *  Created on: 17 oct. 2008
 *      Author: Aur�lien
 */

#include "Espace.h"

Espace::Espace(EcranV *ec, TimerSpaceInvaders *t, ClavierV *c, int n) {
	ecran = ec;
	timer = t;
	clavier = c;
	niveau = n;

	fondEspace = new FondEspace(Config::getCouleurFondEspace(niveau));

	EntiteBase::setEspace(this);
	MissileAlien::setNombreMaxMissiles(Config::getNombreMissilesAliensMax(
			niveau));

	timer->setTimerDeplacementAliens(Config::getVitesseDeplacementBlocAlien(
			niveau));
	timer->setTimerMissileAliens(Config::getVitesseMissileAlien(niveau));

	remplirEspaceVide();
	creerBunkers(Config::getNbBunkers(niveau), VERT_LEGER, 1);
	redessinerEspace();

	//Cr�ation du bloc alien.
	blocAliens = new BlocAliens(timer, this, niveau);
	//Cr�ation du canon.
	canon = EntiteFactory::creerCanon(timer, clavier, 23, 27);
}

Espace::~Espace(){
	delete blocAliens;
}

Couleur Espace::getCouleurArPlanAt(int ligne, int colonne) {
	return fondEspace->getCouleurArPlanAt(ligne, colonne);
}

Couleur Espace::getCouleurPrPlanAt(int ligne, int colonne) {
	return fondEspace->getCouleurPrPlanAt(ligne, colonne);
}

EntiteBase *Espace::getEntite(int ligne, int colonne) {
	return espace[ligne * LARGEUR + colonne];
}

void Espace::ajouterEntite(EntiteBase *entite) {
	entite->dessiner();
}
void Espace::setEntite(EntiteBase *entite, int ligne, int colonne) {
	espace[ligne * LARGEUR + colonne] = entite;
}

void Espace::setEntiteVide(int ligne, int colonne) {
	espace[ligne * LARGEUR + colonne] = fondEspace->getEntiteVide(ligne,
			colonne);
	getEntite(ligne, colonne)->dessiner();
}

void Espace::supprimerEntite(EntiteBase *entite) {
	entite->effacer();
}

void Espace::remplirEspaceVide() {
	for (int ligne = 1; ligne < HAUTEUR; ligne++) {
		for (int colonne = 0; colonne < LARGEUR; colonne++) {
			setEntiteVide(ligne, colonne);
		}
	}
}

void Espace::redessinerEspace() {
	for (int ligne = 1; ligne < HAUTEUR; ligne++) {
		for (int colonne = 0; colonne < LARGEUR; colonne++) {
			if (getEntite(ligne, colonne)->getPositionLigne() == ligne
					&& getEntite(ligne, colonne)->getPositionColonne()
							== colonne)
				getEntite(ligne, colonne)->dessiner();
		}
	}
	ecran->afficherMot(0, 0, " Ascii-Invaders", BLANC);
}

void Espace::creerBunkers(int nbBunker, Couleur couleur, int resistance) {
	int largeurBunker = 7;
	int hauteurBunker = 3;
	int bunkerX = (80 / nbBunker - largeurBunker / 2) / 2 - 1;
	int bunkerY = 22 - hauteurBunker;

	for (int numBunk = 0; numBunk < nbBunker; numBunk++) {
		for (int ligneBunk = 0; ligneBunk < hauteurBunker; ligneBunk++) {
			for (int colBunk = 0; colBunk < largeurBunker; colBunk++) {
				if (!(ligneBunk == 0 && (colBunk == 0 || colBunk
						== largeurBunker - 1) || ligneBunk == hauteurBunker - 1
						&& colBunk == largeurBunker / 2))
					ajouterEntite(EntiteFactory::creerBunker(bunkerY
							+ ligneBunk, bunkerX + colBunk + 80 / nbBunker
							* numBunk, couleur, resistance));
			}
		}
	}
}

void Espace::demarrerEspace() {
	blocAliens->start("SP BlocAliens");
	canon->start("SP Canon");
}
void Espace::stopperEspace() {
	timer->stopperTimer();
	int seconde = timer->getSecondes();
	while (timer->getSecondes() - seconde <= 2)
		timer->handler(this);
	ecran->effacerEcranV(BLEU);
	timer->handler(this);
	//while (true);
}

BlocAliens *Espace::getBlocAliens() {
	return blocAliens;
}
Canon *Espace::getCanon() {
	return canon;
}
const int Espace::getNiveau() {
	return niveau;
}

bool Espace::niveauTermine() {
	//return timer->getSecondes() > 5;
	return blocAliens->getNombreAliensRestants() == 0
			|| canon->getPointsDeVie() == 0;
}
