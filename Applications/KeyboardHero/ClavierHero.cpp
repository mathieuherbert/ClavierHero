/*
 * ClavierHero.cpp
 *
 *  Created on: 23 oct. 2013
 *      Author: Julien Deray, Mathieu Cartaud, Mathieu Herbert
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
//le score
int ClavierHero::score = 0;
int ClavierHero::valScoreInf = -150;

//booleans definissant les zones ou la note est jouable.
//les zones valant tous les points et celles ne valant que la moitié sont aussi définies
bool ClavierHero::c1Dessus = false;
bool ClavierHero::c1ok= false;
bool ClavierHero::c1Dessous = false;

bool ClavierHero::c2Dessus = false;
bool ClavierHero::c2ok= false;
bool ClavierHero::c2Dessous = false;

bool ClavierHero::c3Dessus = false;
bool ClavierHero::c3ok= false;
bool ClavierHero::c3Dessous = false;

bool ClavierHero::c4Dessus = false;
bool ClavierHero::c4ok= false;
bool ClavierHero::c4Dessous = false;

//true si la note est validée sur sa colonne
bool ClavierHero::c1PieceValider = false;
bool ClavierHero::c2PieceValider = false;
bool ClavierHero::c3PieceValider = false;
bool ClavierHero::c4PieceValider = false;

//true si le score est inferieur à la limite définie
bool ClavierHero::scoreTropBas= false;
//constructeur
ClavierHero::ClavierHero(EcranV *e, ClavierV *c) {
	ecran = e;
	clavier = c;
	score = 0;
	timer = new Timer();
}

ClavierHero::~ClavierHero() {
}

void ClavierHero::run() {

		//menu de choix de partition
		ecran->effacerEcranV(NOIR);
		ecran->afficherMot(
				"Bienvenue dans ClavierHero\nDeux chansons sont disponible \n");
		ecran->afficherMot("l:Super Mario Bros\nm:Au Clair De La Lune\n");
		ecran->afficherMot(
				"Pour lancer le mode de votre choix taper la numero correspondant");
		char i = clavier->getChar();
		if (i == 'l') {
			//jeu en lui même
			mario();
		} else if (i == 'm') {
			lune();
		} else {
			mario();
		}
		//Fin de partie
		ecran->effacerEcranV(NOIR);
		ecran->afficherMot(15, 27, "Fin de la partie", ROUGE);
		ecran->afficherMot(16, 27, "score: ", ROUGE);
		ecran->afficherChiffre(16, 35, score);
		if (score < ClavierHero::valScoreInf) {
			ecran->afficherMot(20, 30, "Perdu !!!", ROUGE);
		} else {
			ecran->afficherMot(20, 30, "Tu Dechires !!!", ROUGE);
		}
}

void ClavierHero::afficherScore() {
	for(int i=65;i<COLONNES;i++){
		ecran->afficherCaractere(10,i,NOIR,NOIR,'_');
	}
	afficherChiffreCommente(ecran, 10, 65, "Score:", ClavierHero::score, 6);
}

void ClavierHero::init() {
	ecran->effacerEcranV(NOIR);
	//gestion du clavier
	GestionToucheClavier *lecteurClavier = new GestionToucheClavier(clavier,
			this);
	lecteurClavier->start("clavierHero");
	//affiche les lignes
	afficherScore();
	afficherLignes(EMPLACEMENT_COLONNE1, EMPLACEMENT_COLONNE2,
			EMPLACEMENT_COLONNE3, EMPLACEMENT_COLONNE4);
	afficherTouches(EMPLACEMENT_COLONNE1, EMPLACEMENT_COLONNE2,
			EMPLACEMENT_COLONNE3, EMPLACEMENT_COLONNE4);
	afficherLigneDeJeu(EMPLACEMENT_ZONE_JEU);

}

//lance la chanson super mario
void ClavierHero::mario() {
	init();
	Bibliotheque* bibliotheque = new Bibliotheque(ecran, timer);
	bibliotheque->superMario();
}

//lance la chanson au clair de la lune
void ClavierHero::lune() {
	init();
	Bibliotheque* bibliotheque = new Bibliotheque(ecran, timer);
	bibliotheque->auClairDeLaLune();
}

//affiche les lignes de défilement des notes
void ClavierHero::afficherLignes(int ligne1, int ligne2, int ligne3, int ligne4) {
	for (int lig = 0; lig < LIGNES; ++lig) {
		ecran->afficherCaractere(lig, ligne1, VERT, NOIR, DESIGN_LIGNE);
		ecran->afficherCaractere(lig, ligne2, ROUGE, NOIR, DESIGN_LIGNE);
		ecran->afficherCaractere(lig, ligne3, JAUNE, NOIR, DESIGN_LIGNE);
		ecran->afficherCaractere(lig, ligne4, BLEU, NOIR, DESIGN_LIGNE);
	}
}

//affiches les touches en bas des lignes
void ClavierHero::afficherTouches(int ligne1, int ligne2, int ligne3,
		int ligne4) {
	ecran->afficherMot(LIGNE_AFFICHAGE_TOUCHE, ligne1, "F1", VERT);
	ecran->afficherMot(LIGNE_AFFICHAGE_TOUCHE, ligne2, "F2", ROUGE);
	ecran->afficherMot(LIGNE_AFFICHAGE_TOUCHE, ligne3, "F3", JAUNE);
	ecran->afficherMot(LIGNE_AFFICHAGE_TOUCHE, ligne4, "F4", BLEU_LEGER);
}

//affiche la ligne définissant la zone de jeu
void ClavierHero::afficherLigneDeJeu(int col) {
	for (int lig = 0; lig < COLONNES - 15; ++lig) {
		ecran->afficherCaractere(col, lig, BLANC, NOIR, DESIGN_COLONNE);
	}
}

void ClavierHero::setToucheJouee(int t) {

	AfficherReussiteNote* aff = new AfficherReussiteNote(ecran);
	//En fonction de la touche appuyée et du positionnement des notes on incrémente ou décrémente le score avec un texte
	if (t == FUN) {
		if (ClavierHero::c1PieceValider == false) {
			if (ClavierHero::c1Dessous) {
				score += 1;
				aff->setReussite(1);
				ClavierHero::c1PieceValider = true;
			} else if (ClavierHero::c1ok) {
				score += 2;
				aff->setReussite(2);
				ClavierHero::c1PieceValider = true;
			} else if (ClavierHero::c1Dessus) {
				score += 1;
				aff->setReussite(1);
				ClavierHero::c1PieceValider = true;
			} else {
				score -= 2;
				aff->setReussite(0);
			}
		}
	} else if (t == FDEUX) {
		if (ClavierHero::c2PieceValider== false) {
			if (ClavierHero::c2Dessous) {
				score += 1;
				aff->setReussite(1);
				ClavierHero::c2PieceValider = true;
			} else if (ClavierHero::c2ok) {
				score += 2;
				aff->setReussite(2);
				ClavierHero::c2PieceValider = true;
			} else if (ClavierHero::c2Dessus) {
				score += 1;
				aff->setReussite(1);
				ClavierHero::c2PieceValider = true;
			} else {
				score -= 2;
				aff->setReussite(0);
			}
		}
	} else if (t == FTROIS) {
		if (ClavierHero::c3PieceValider == false) {
			if (ClavierHero::c3Dessous) {
				score += 1;
				aff->setReussite(1);
				ClavierHero::c3PieceValider = true;
			} else if (ClavierHero::c3ok) {
				score += 2;
				aff->setReussite(2);
				ClavierHero::c3PieceValider = true;
			} else if (ClavierHero::c3Dessus) {
				score += 1;
				aff->setReussite(1);
				ClavierHero::c3PieceValider = true;
			} else {
				score -= 2;
				aff->setReussite(0);
			}
		}
	} else if (t == FQUATRE) {
		if (ClavierHero::c4PieceValider == false) {
			if (ClavierHero::c4Dessous) {
				score += 1;
				aff->setReussite(1);
				ClavierHero::c4PieceValider = true;
			} else if (ClavierHero::c4ok) {
				score += 2;
				aff->setReussite(2);
				ClavierHero::c4PieceValider = true;
			} else if (ClavierHero::c4Dessus) {
				score += 1;
				aff->setReussite(1);
				ClavierHero::c4PieceValider = true;
			} else {
				score -= 2;
				aff->setReussite(0);
			}
		}
	}
	afficherScore();
	//affiche un commentaire sur la performance à droite de l'ecran
	aff->start("clavierHero");
}

void ClavierHero::afficherChiffreCommente(EcranV* l_ecran, int l, int c,
		const char* label, const int valeur, const int nbChiffres) {
	long nombreDeCaracteres = 0;
	char caractereActuel = 0;
	do {
		caractereActuel = label[nombreDeCaracteres];
		nombreDeCaracteres++;
	} while (caractereActuel != '\0'); // On boucle tant qu'on n'est pas arrivï¿½ ï¿½ l'\0
	nombreDeCaracteres--; // On retire 1 caractï¿½re de long pour ne pas compter l'\0

	l_ecran->afficherMot(l, c, label, JAUNE);

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
		l_ecran->afficherCaractere(l, i, NOIR, NOIR, ' ');
	l_ecran->afficherChiffre(l, c + nombreDeCaracteres + nbChiffres
			- tailleChiffre, valeur);
}
