/*
 * Note.cpp
 *
 *  Created on: 20 oct. 2013
 *      Author: julienderay
 */

#include "Note.h"
#include "model/Hauteur.h"
#include "model/Octave.h"
#include "core/SonClavierHero.h"

Note::Note(Puls* aTemps, int aHauteur, int aTouche, int anOctave,
		EcranV *anEcran, Timer *aTimer) {
	temps = aTemps;
	hauteur = aHauteur;
	touche = aTouche;
	octave = anOctave;
	ecran = anEcran;
	timer = aTimer;
	duree = 0;
}

Puls* Note::getTempsNum() {
	return temps;
}

int Note::getFrequence() {
	return (int) (hauteur * octave);
}

int Note::getHauteur() {
	return hauteur;
}

int Note::getOctave() {
	return octave;
}

//String Note::toString() {
//	return touche . "     -> " . hauteur . " | " . temps . " | " . getFrequence();
//}

void Note::setDiese() {
	switch (hauteur) {
	case DO:
		hauteur = DOD;
		break;
	case DOD:
		hauteur = RE;
		break;
	case RE:
		hauteur = RED;
		break;
	case RED:
		hauteur = MI;
		break;
	case MI:
		hauteur = FA;
		break;
	case FA:
		hauteur = FAD;
		break;
	case FAD:
		hauteur = SOL;
		break;
	case SOLD:
		hauteur = SOLD;
		break;
	case LA:
		hauteur = LA;
		break;
	case LAD:
		hauteur = LAD;
		break;
	case SI:
		hauteur = SI;
		break;
	}
}

int Note::getToucheCol() {
	switch (touche) {
	case 1:
		return ClavierHero::EMPLACEMENT_COLONNE1;
	case 2:
		return ClavierHero::EMPLACEMENT_COLONNE2;
	case 3:
		return ClavierHero::EMPLACEMENT_COLONNE3;
	case 4:
		return ClavierHero::EMPLACEMENT_COLONNE4;
	default:
		return 0;
	}
}

void Note::run() {
	for (int i = 0; i < ClavierHero::EMPLACEMENT_ZONE_JEU + 3; i++) {
		int from = timer->getCsecondes();
		int to = from + 200 / (ClavierHero::EMPLACEMENT_ZONE_JEU - 2);
		while (from < to) {
			from = timer->getCsecondes();
		}
		setIcon(i);
	}
	eraseIcon();
}

void Note::verificationDeValidationColUn(int & col, int & ligne) {
	if (col == ClavierHero::EMPLACEMENT_COLONNE1) {
		if (ligne == 0) {
			ClavierHero::C1PIECEVALIDER = false;
		}
		if (ligne == ClavierHero::EMPLACEMENT_ZONE_JEU) {
			ClavierHero::C1OK = true;
			ClavierHero::C1DESSUS = false;
			ClavierHero::C1DESSOUS = false;
		} else if (ligne == ClavierHero::EMPLACEMENT_ZONE_JEU_DESSOUS) {
			ClavierHero::C1OK = false;
			ClavierHero::C1DESSOUS = true;
			ClavierHero::C1DESSUS = false;
		} else if (ligne == ClavierHero::EMPLACEMENT_ZONE_JEU_DESSUS) {
			ClavierHero::C1OK = false;
			ClavierHero::C1DESSUS = true;
			ClavierHero::C1DESSOUS = false;
		} else if (ligne == ClavierHero::EMPLACEMENT_ZONE_JEU_TROP_TARD) {
			ClavierHero::C1OK = false;
			ClavierHero::C1DESSUS = false;
			ClavierHero::C1DESSOUS = false;
			ClavierHero::C1PIECEVALIDER = false;
		}

	}

}

void Note::verificationDeValidationColDeux(int & col, int & ligne) {
	if (col == ClavierHero::EMPLACEMENT_COLONNE2) {
		if (ligne == 0) {
			ClavierHero::C2PIECEVALIDER = false;
		}
		if (ligne == ClavierHero::EMPLACEMENT_ZONE_JEU) {
			ClavierHero::C2OK = true;
			ClavierHero::C2DESSUS = false;
			ClavierHero::C2DESSOUS = false;
		} else if (ligne == ClavierHero::EMPLACEMENT_ZONE_JEU_DESSOUS) {
			ClavierHero::C2OK = false;
			ClavierHero::C2DESSOUS = true;
			ClavierHero::C2DESSUS = false;
		} else if (ligne == ClavierHero::EMPLACEMENT_ZONE_JEU_DESSUS) {
			ClavierHero::C2OK = false;
			ClavierHero::C2DESSUS = true;
			ClavierHero::C2DESSOUS = false;
		} else if (ligne == ClavierHero::EMPLACEMENT_ZONE_JEU_TROP_TARD) {
			ClavierHero::C2OK = false;
			ClavierHero::C2DESSUS = false;
			ClavierHero::C2DESSOUS = false;
			ClavierHero::C2PIECEVALIDER = false;
		}

	}

}

void Note::verificationDeValidationColTrois(int & col, int & ligne) {
	if (col == ClavierHero::EMPLACEMENT_COLONNE3) {
		if (ligne == 0) {
			ClavierHero::C3PIECEVALIDER = false;
		}
		if (ligne == ClavierHero::EMPLACEMENT_ZONE_JEU) {
			ClavierHero::C3OK = true;
			ClavierHero::C3DESSUS = false;
			ClavierHero::C3DESSOUS = false;
		} else if (ligne == ClavierHero::EMPLACEMENT_ZONE_JEU_DESSOUS) {
			ClavierHero::C3OK = false;
			ClavierHero::C3DESSOUS = true;
			ClavierHero::C3DESSUS = false;
		} else if (ligne == ClavierHero::EMPLACEMENT_ZONE_JEU_DESSUS) {
			ClavierHero::C3OK = false;
			ClavierHero::C3DESSUS = true;
			ClavierHero::C3DESSOUS = false;
		} else if (ligne == ClavierHero::EMPLACEMENT_ZONE_JEU_TROP_TARD) {
			ClavierHero::C3OK = false;
			ClavierHero::C3DESSUS = false;
			ClavierHero::C3DESSOUS = false;
			ClavierHero::C3PIECEVALIDER = false;
		}

	}

}

void Note::verificationDeValidationColQuatre(int & col, int & ligne) {
	if (col == ClavierHero::EMPLACEMENT_COLONNE4) {
		if (ligne == 0) {
			ClavierHero::C4PIECEVALIDER = false;
		}
		if (ligne == ClavierHero::EMPLACEMENT_ZONE_JEU) {
			ClavierHero::C4OK = true;
			ClavierHero::C4DESSUS = false;
			ClavierHero::C4DESSOUS = false;
		} else if (ligne == ClavierHero::EMPLACEMENT_ZONE_JEU_DESSOUS) {
			ClavierHero::C4OK = false;
			ClavierHero::C4DESSOUS = true;
			ClavierHero::C4DESSUS = false;
		} else if (ligne == ClavierHero::EMPLACEMENT_ZONE_JEU_DESSUS) {
			ClavierHero::C4OK = false;
			ClavierHero::C4DESSUS = true;
			ClavierHero::C4DESSOUS = false;
		} else if (ligne == ClavierHero::EMPLACEMENT_ZONE_JEU_TROP_TARD) {
			ClavierHero::C4OK = false;
			ClavierHero::C4DESSUS = false;
			ClavierHero::C4DESSOUS = false;
			ClavierHero::C4PIECEVALIDER = false;
		}

	}

}

void Note::setIcon(int ligne) {

	int col = getToucheCol();
	verificationDeValidationColUn(col, ligne);
	verificationDeValidationColDeux(col, ligne);
	verificationDeValidationColTrois(col, ligne);
	verificationDeValidationColQuatre(col, ligne);
	if(ligne == ClavierHero::EMPLACEMENT_ZONE_JEU){
		SonClavierHero* son = new SonClavierHero(ecran,this,duree);
		son->start("son");
	}
	ecran->afficherCaractere(ligne - 3, col - 2, NOIR, NOIR, 176);
	ecran->afficherCaractere(ligne - 3, col - 1, NOIR, NOIR, 176);
	ecran->afficherCaractere(ligne - 3, col, BLANC, NOIR,
			ClavierHero::DESIGN_LIGNE);
	ecran->afficherCaractere(ligne - 3, col + 1, NOIR, NOIR, 176);
	ecran->afficherCaractere(ligne - 3, col + 2, NOIR, NOIR, 176);

	ecran->afficherCaractere(ligne - 2, col - 2, NOIR, NOIR, 176);
	ecran->afficherCaractere(ligne - 2, col - 1, BLANC, NOIR, 176);
	ecran->afficherCaractere(ligne - 2, col, BLANC, NOIR, 176);
	ecran->afficherCaractere(ligne - 2, col + 1, BLANC, NOIR, 176);
	ecran->afficherCaractere(ligne - 2, col + 2, NOIR, NOIR, 176);

	ecran->afficherCaractere(ligne - 1, col - 2, BLANC, NOIR, 176);
	ecran->afficherCaractere(ligne - 1, col - 1, BLANC, NOIR, 176);
	ecran->afficherCaractere(ligne - 1, col, BLANC, NOIR, 176);
	ecran->afficherCaractere(ligne - 1, col + 1, BLANC, NOIR, 176);
	ecran->afficherCaractere(ligne - 1, col + 2, BLANC, NOIR, 176);

	ecran->afficherCaractere(ligne, col - 2, NOIR, NOIR, 176);
	ecran->afficherCaractere(ligne, col - 1, BLANC, NOIR, 176);
	ecran->afficherCaractere(ligne, col, BLANC, NOIR, 176);
	ecran->afficherCaractere(ligne, col + 1, BLANC, NOIR, 176);
	ecran->afficherCaractere(ligne, col + 2, NOIR, NOIR, 176);

	ecran->afficherCaractere(ligne + 1, col - 2, NOIR, NOIR, 176);
	ecran->afficherCaractere(ligne + 1, col - 1, NOIR, NOIR, 176);
	ecran->afficherCaractere(ligne + 1, col, BLANC, NOIR,
			ClavierHero::DESIGN_LIGNE);
	ecran->afficherCaractere(ligne + 1, col + 1, NOIR, NOIR, 176);
	ecran->afficherCaractere(ligne + 1, col + 2, NOIR, NOIR, 176);
}

void Note::eraseIcon() {
	int col = getToucheCol();
	int ligne = ClavierHero::EMPLACEMENT_ZONE_JEU + 3;
	ecran->afficherCaractere(ligne - 3, col - 2, JAUNE, NOIR,
			ClavierHero::DESIGN_COLONNE);
	ecran->afficherCaractere(ligne - 3, col - 1, JAUNE, NOIR,
			ClavierHero::DESIGN_COLONNE);
	ecran->afficherCaractere(ligne - 3, col, JAUNE, NOIR,
			ClavierHero::DESIGN_COLONNE);
	ecran->afficherCaractere(ligne - 3, col + 1, JAUNE, NOIR,
			ClavierHero::DESIGN_COLONNE);
	ecran->afficherCaractere(ligne - 3, col + 2, JAUNE, NOIR,
			ClavierHero::DESIGN_COLONNE);

	ecran->afficherCaractere(ligne - 2, col - 2, NOIR, NOIR, 176);
	ecran->afficherCaractere(ligne - 2, col - 1, NOIR, NOIR, 176);
	ecran->afficherCaractere(ligne - 2, col, BLANC, NOIR,
			ClavierHero::DESIGN_LIGNE);
	ecran->afficherCaractere(ligne - 2, col + 1, NOIR, NOIR, 176);
	ecran->afficherCaractere(ligne - 2, col + 2, NOIR, NOIR, 176);

	ecran->afficherCaractere(ligne - 1, col - 2, NOIR, NOIR, 176);
	ecran->afficherCaractere(ligne - 1, col - 1, NOIR, NOIR, 176);
	ecran->afficherCaractere(ligne - 1, col, BLANC, NOIR,
			ClavierHero::DESIGN_LIGNE);
	ecran->afficherCaractere(ligne - 1, col + 1, NOIR, NOIR, 176);
	ecran->afficherCaractere(ligne - 1, col + 2, NOIR, NOIR, 176);

	ecran->afficherCaractere(ligne, col - 2, NOIR, NOIR, 176);
	ecran->afficherCaractere(ligne, col - 1, NOIR, NOIR, 176);
	ecran->afficherCaractere(ligne, col, BLANC, NOIR, ClavierHero::DESIGN_LIGNE);
	ecran->afficherCaractere(ligne, col + 1, NOIR, NOIR, 176);
	ecran->afficherCaractere(ligne, col + 2, NOIR, NOIR, 176);

	ecran->afficherCaractere(ligne + 1, col - 2, NOIR, NOIR, 176);
	ecran->afficherCaractere(ligne + 1, col - 1, NOIR, NOIR, 176);
	ecran->afficherMot(ClavierHero::LIGNE_AFFICHAGE_TOUCHE, col, "F?", JAUNE);
	ecran->afficherCaractere(ligne + 1, col + 1, NOIR, NOIR, 176);
	ecran->afficherCaractere(ligne + 1, col + 2, NOIR, NOIR, 176);
}

