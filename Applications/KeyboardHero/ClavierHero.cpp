/*
 * ClavierHero.cpp
 *
 *  Created on: 23 oct. 2013
 *      Author: mathieu
 */

#include "ClavierHero.h"
#include "Note.h"
#include "model/Hauteur.h"
#include "model/Octave.h"
#include "model/Puls.h"
#include "model/Touche.h"
#include "Partition.h"
#include "lib/String.h"
#include "core/GestionToucheClavier.h"
#include "ihm/AfficherReussiteNote.h"
#include "Bibliotheque.h"

int ClavierHero::score = 0;

bool ClavierHero::C1DESSUS = false;
bool ClavierHero::C1OK = false;
bool ClavierHero::C1DESSOUS = false;

bool ClavierHero::C2DESSUS = false;
bool ClavierHero::C2OK = false;
bool ClavierHero::C2DESSOUS = false;

bool ClavierHero::C3DESSUS = false;
bool ClavierHero::C3OK = false;
bool ClavierHero::C3DESSOUS = false;

bool ClavierHero::C4DESSUS = false;
bool ClavierHero::C4OK = false;
bool ClavierHero::C4DESSOUS = false;

bool ClavierHero::C1PIECEVALIDER = false;
bool ClavierHero::C2PIECEVALIDER = false;
bool ClavierHero::C3PIECEVALIDER = false;
bool ClavierHero::C4PIECEVALIDER = false;

bool ClavierHero::SCORE_TROP_BAS = false;
int ClavierHero::VAL_SCORE_INF = -150;

ClavierHero::ClavierHero(EcranV *e, ClavierV *c) {
	ecran = e;
	clavier = c;
	score = 0;
	timer = new Timer();
}

ClavierHero::~ClavierHero() {
}

void ClavierHero::run() {
	ecran->effacerEcranV(NOIR);
	init();
}

void ClavierHero::afficherScore()
{
    afficherChiffreCommente(10, 65, "Score:", ClavierHero::score, 6);
}

void ClavierHero::init() {

	GestionToucheClavier *lecteurClavier = new GestionToucheClavier(clavier,
			this);
	lecteurClavier->start("clavierHero");

	afficherScore();
	afficherLignes(EMPLACEMENT_COLONNE1, EMPLACEMENT_COLONNE2,
			EMPLACEMENT_COLONNE3, EMPLACEMENT_COLONNE4);
	afficherTouches(EMPLACEMENT_COLONNE1, EMPLACEMENT_COLONNE2,
			EMPLACEMENT_COLONNE3, EMPLACEMENT_COLONNE4);
	afficherLigneDeJeu(EMPLACEMENT_ZONE_JEU);

	Bibliotheque* bibliotheque = new Bibliotheque(ecran, timer);
	bibliotheque->superMario();

}

void ClavierHero::afficherLignes(int ligne1, int ligne2, int ligne3, int ligne4) {
	for (int lig = 0; lig < LIGNES; ++lig) {
		ecran->afficherCaractere(lig, ligne1, BLANC, NOIR, DESIGN_LIGNE);
		ecran->afficherCaractere(lig, ligne2, BLANC, NOIR, DESIGN_LIGNE);
		ecran->afficherCaractere(lig, ligne3, BLANC, NOIR, DESIGN_LIGNE);
		ecran->afficherCaractere(lig, ligne4, BLANC, NOIR, DESIGN_LIGNE);
	}
}

void ClavierHero::afficherTouches(int ligne1, int ligne2, int ligne3, int ligne4) {
	ecran->afficherMot(LIGNE_AFFICHAGE_TOUCHE, ligne1, "F1", JAUNE);
	ecran->afficherMot(LIGNE_AFFICHAGE_TOUCHE, ligne2, "F2", JAUNE);
	ecran->afficherMot(LIGNE_AFFICHAGE_TOUCHE, ligne3, "F3", JAUNE);
	ecran->afficherMot(LIGNE_AFFICHAGE_TOUCHE, ligne4, "F4", JAUNE);
}

void ClavierHero::afficherLigneDeJeu(int col) {
	for (int lig = 0; lig < COLONNES - 15; ++lig) {
		ecran->afficherCaractere(col, lig, JAUNE, NOIR, DESIGN_COLONNE);
	}
}

void ClavierHero::setToucheJouee(int t) {

	AfficherReussiteNote* aff = new AfficherReussiteNote(ecran);

	if (t == FUN) {
		if (ClavierHero::C1PIECEVALIDER == false) {
			if (ClavierHero::C1DESSOUS) {
				score += 1;
				aff->setReussite(1);
				ClavierHero::C1PIECEVALIDER = true;
			} else if (ClavierHero::C1OK) {
				score += 2;
				aff->setReussite(2);
				ClavierHero::C1PIECEVALIDER = true;
			} else if (ClavierHero::C1DESSUS) {
				score += 1;
				aff->setReussite(1);
				ClavierHero::C1PIECEVALIDER = true;
			} else {
				score -= 2;
				aff->setReussite(0);
			}
		}
	} else if (t == FDEUX) {
		if (ClavierHero::C2PIECEVALIDER == false) {
			if (ClavierHero::C2DESSOUS) {
				score += 1;
				aff->setReussite(1);
				ClavierHero::C2PIECEVALIDER = true;
			} else if (ClavierHero::C2OK) {
				score += 2;
				aff->setReussite(2);
				ClavierHero::C2PIECEVALIDER = true;
			} else if (ClavierHero::C2DESSUS) {
				score += 1;
				aff->setReussite(1);
				ClavierHero::C2PIECEVALIDER = true;
			} else {
				score -= 2;
				aff->setReussite(0);
			}
		}
	} else if (t == FTROIS) {
		if (ClavierHero::C3PIECEVALIDER == false) {
			if (ClavierHero::C3DESSOUS) {
				score += 1;
				aff->setReussite(1);
				ClavierHero::C3PIECEVALIDER = true;
			} else if (ClavierHero::C3OK) {
				score += 2;
				aff->setReussite(2);
				ClavierHero::C3PIECEVALIDER = true;
			} else if (ClavierHero::C3DESSUS) {
				score += 1;
				aff->setReussite(1);
				ClavierHero::C3PIECEVALIDER = true;
			} else {
				score -= 2;
				aff->setReussite(0);
			}
		}
	} else if (t == FQUATRE) {
		if (ClavierHero::C4PIECEVALIDER == false) {
			if (ClavierHero::C4DESSOUS) {
				score += 1;
				aff->setReussite(1);
				ClavierHero::C4PIECEVALIDER = true;
			} else if (ClavierHero::C4OK) {
				score += 2;
				aff->setReussite(2);
				ClavierHero::C4PIECEVALIDER = true;
			} else if (ClavierHero::C4DESSUS) {
				score += 1;
				aff->setReussite(1);
				ClavierHero::C4PIECEVALIDER = true;
			} else {
				score -= 2;
				aff->setReussite(0);
			}
		}
	}
	afficherScore();
	aff->start("clavierHero");
}

void ClavierHero::afficherChiffreCommente(int l, int c, const char* label,
		const int valeur, const int nbChiffres) {
	long nombreDeCaracteres = 0;
	char caractereActuel = 0;
	do {
		caractereActuel = label[nombreDeCaracteres];
		nombreDeCaracteres++;
	} while (caractereActuel != '\0'); // On boucle tant qu'on n'est pas arriv� � l'\0
	nombreDeCaracteres--; // On retire 1 caract�re de long pour ne pas compter l'\0

	ecran->afficherMot(l, c, label, JAUNE);

	bool negatif = valeur < 0;
	int tailleChiffre = 6, exposant = 1000000;
	while (valeur < exposant && !negatif || -valeur < exposant && negatif) {
		exposant = exposant / 10;
		tailleChiffre--;
	}
	if (tailleChiffre <= 0)
		tailleChiffre = 1;

	for (int i = c + nombreDeCaracteres; i < c + nombreDeCaracteres
			+ nbChiffres; i++)
		ecran->afficherCaractere(l, i, NOIR, NOIR, ' ');
	ecran->afficherChiffre(l, c + nombreDeCaracteres + nbChiffres
			- tailleChiffre, valeur);
}
