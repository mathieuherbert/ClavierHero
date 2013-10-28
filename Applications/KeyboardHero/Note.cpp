/*
 * Note.cpp
 *
 *  Created on: 20 oct. 2013
 *      Author: Julien Deray, Mathieu Cartaud, Mathieu Herbert
 */

#include "Note.h"
#include "model/Hauteur.h"
#include "model/Octave.h"
#include "core/SonClavierHero.h"
#include "ihm/AfficherReussiteNote.h"

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
	//gere le déplacement de la touche sur l ecran
	for (int i = 0; i < ClavierHero::EMPLACEMENT_ZONE_JEU + 3; i++) {
		int from = timer->getCsecondes();
		int to = from + 200 / (ClavierHero::EMPLACEMENT_ZONE_JEU - 2);
		//phase d attente avant de redescendre a novueau
		while (from < to) {
			from = timer->getCsecondes();
		}
		setIcon(i);
	}
	eraseIcon();
}

/*
 * En fonction de la place de de la note, on modifie les variables de placement de la note
 */
void Note::verificationDeValidationColUn(int & col, int & ligne) {
	if (col == ClavierHero::EMPLACEMENT_COLONNE1) {
		if (ligne == 0) {
			ClavierHero::c1PieceValider = false;
		}
		if (ligne == ClavierHero::EMPLACEMENT_ZONE_JEU) {
			ClavierHero::c1ok = true;
			ClavierHero::c1Dessus= false;
			ClavierHero::c1Dessous = false;
		} else if (ligne == ClavierHero::EMPLACEMENT_ZONE_JEU_DESSOUS) {
			ClavierHero::c1ok = false;
			ClavierHero::c1Dessous = true;
			ClavierHero::c1Dessus = false;
		} else if (ligne == ClavierHero::EMPLACEMENT_ZONE_JEU_DESSUS) {
			ClavierHero::c1ok = false;
			ClavierHero::c1Dessus = true;
			ClavierHero::c1Dessous = false;
		} else if (ligne == ClavierHero::EMPLACEMENT_ZONE_JEU_TROP_TARD) {
			AfficherReussiteNote* reussiteNote = new AfficherReussiteNote(ecran);
			if(!ClavierHero::c1PieceValider){
				ClavierHero::score-=2;
				ClavierHero::afficherChiffreCommente(ecran,10, 65, "Score:", ClavierHero::score, 6);
			}
			ClavierHero::c1ok = false;
			ClavierHero::c1Dessus = false;
			ClavierHero::c1Dessous = false;
			ClavierHero::c1PieceValider = false;
			//cas où le joueur n a pas appuyer sur une touche
			//ClavierHero* clavier = ClavierHero::getClavierHero();
			//clavier->afficherScore();
			reussiteNote->setReussite(0);
			reussiteNote->start("clavierHero");
		}

	}

}

void Note::verificationDeValidationColDeux(int & col, int & ligne) {
	if (col == ClavierHero::EMPLACEMENT_COLONNE2) {
		if (ligne == 0) {
			ClavierHero::c2PieceValider = false;
		}
		if (ligne == ClavierHero::EMPLACEMENT_ZONE_JEU) {
			ClavierHero::c2ok = true;
			ClavierHero::c2Dessus = false;
			ClavierHero::c2Dessous = false;
		} else if (ligne == ClavierHero::EMPLACEMENT_ZONE_JEU_DESSOUS) {
			ClavierHero::c2ok = false;
			ClavierHero::c2Dessous = true;
			ClavierHero::c2Dessus = false;
		} else if (ligne == ClavierHero::EMPLACEMENT_ZONE_JEU_DESSUS) {
			ClavierHero::c2ok = false;
			ClavierHero::c2Dessus = true;
			ClavierHero::c2Dessous = false;
		} else if (ligne == ClavierHero::EMPLACEMENT_ZONE_JEU_TROP_TARD) {
			if(!ClavierHero::c2PieceValider){
				ClavierHero::score-=2;
				ClavierHero::afficherChiffreCommente(ecran,10, 65, "Score:", ClavierHero::score, 6);
			}
			ClavierHero::c2ok = false;
			ClavierHero::c2Dessus = false;
			ClavierHero::c2Dessous = false;
			ClavierHero::c2PieceValider = false;

			AfficherReussiteNote* reussiteNote = new AfficherReussiteNote(ecran);
			reussiteNote->setReussite(0);
			reussiteNote->start("clavierHero");
		}

	}

}

void Note::verificationDeValidationColTrois(int & col, int & ligne) {
	if (col == ClavierHero::EMPLACEMENT_COLONNE3) {
		if (ligne == 0) {
			ClavierHero::c3PieceValider = false;
		}
		if (ligne == ClavierHero::EMPLACEMENT_ZONE_JEU) {
			ClavierHero::c3ok = true;
			ClavierHero::c3Dessus = false;
			ClavierHero::c3Dessous = false;
		} else if (ligne == ClavierHero::EMPLACEMENT_ZONE_JEU_DESSOUS) {
			ClavierHero::c3ok = false;
			ClavierHero::c3Dessous = true;
			ClavierHero::c3Dessus = false;
		} else if (ligne == ClavierHero::EMPLACEMENT_ZONE_JEU_DESSUS) {
			ClavierHero::c3ok = false;
			ClavierHero::c3Dessus = true;
			ClavierHero::c3Dessous = false;
		} else if (ligne == ClavierHero::EMPLACEMENT_ZONE_JEU_TROP_TARD) {
			if(!ClavierHero::c3PieceValider){
				ClavierHero::score-=2;
				ClavierHero::afficherChiffreCommente(ecran,10, 65, "Score:", ClavierHero::score, 6);
			}
			ClavierHero::c3ok = false;
			ClavierHero::c3Dessus = false;
			ClavierHero::c3Dessous = false;
			ClavierHero::c3PieceValider = false;

			AfficherReussiteNote* reussiteNote = new AfficherReussiteNote(ecran);
			reussiteNote->setReussite(0);
			reussiteNote->start("clavierHero");
		}

	}

}

void Note::verificationDeValidationColQuatre(int & col, int & ligne) {
	if (col == ClavierHero::EMPLACEMENT_COLONNE4) {
		if (ligne == 0) {
			ClavierHero::c4PieceValider = false;
		}
		if (ligne == ClavierHero::EMPLACEMENT_ZONE_JEU) {
			ClavierHero::c4ok = true;
			ClavierHero::c4Dessus = false;
			ClavierHero::c4Dessous = false;
		} else if (ligne == ClavierHero::EMPLACEMENT_ZONE_JEU_DESSOUS) {
			ClavierHero::c4ok = false;
			ClavierHero::c4Dessous = true;
			ClavierHero::c4Dessus = false;
		} else if (ligne == ClavierHero::EMPLACEMENT_ZONE_JEU_DESSUS) {
			ClavierHero::c4ok = false;
			ClavierHero::c4Dessus = true;
			ClavierHero::c4Dessous = false;
		} else if (ligne == ClavierHero::EMPLACEMENT_ZONE_JEU_TROP_TARD) {
			if(!ClavierHero::c4PieceValider){
				ClavierHero::score-=2;
				ClavierHero::afficherChiffreCommente(ecran,10, 65, "Score:", ClavierHero::score, 6);
			}
			ClavierHero::c4ok = false;
			ClavierHero::c4Dessus = false;
			ClavierHero::c4Dessous = false;
			ClavierHero::c4PieceValider = false;
			AfficherReussiteNote* reussiteNote = new AfficherReussiteNote(ecran);
			reussiteNote->setReussite(0);
			reussiteNote->start("clavierHero");
		}

	}

}
/*
 * CHange la note de place sur l ecran
 */
void Note::setIcon(int ligne) {

	int col = getToucheCol();
	Couleur couleur = getCouleur(col);
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
	ecran->afficherCaractere(ligne - 3, col, couleur, NOIR,
			ClavierHero::DESIGN_LIGNE);
	ecran->afficherCaractere(ligne - 3, col + 1, NOIR, NOIR, 176);
	ecran->afficherCaractere(ligne - 3, col + 2, NOIR, NOIR, 176);

	ecran->afficherCaractere(ligne - 2, col - 2, NOIR, NOIR, 176);
	ecran->afficherCaractere(ligne - 2, col - 1, couleur, NOIR, 176);
	ecran->afficherCaractere(ligne - 2, col, couleur, NOIR, 176);
	ecran->afficherCaractere(ligne - 2, col + 1, couleur, NOIR, 176);
	ecran->afficherCaractere(ligne - 2, col + 2, NOIR, NOIR, 176);

	ecran->afficherCaractere(ligne - 1, col - 2, couleur, NOIR, 176);
	ecran->afficherCaractere(ligne - 1, col - 1, couleur, NOIR, 176);
	ecran->afficherCaractere(ligne - 1, col, couleur, NOIR, 176);
	ecran->afficherCaractere(ligne - 1, col + 1, couleur, NOIR, 176);
	ecran->afficherCaractere(ligne - 1, col + 2, couleur, NOIR, 176);

	ecran->afficherCaractere(ligne, col - 2, NOIR, NOIR, 176);
	ecran->afficherCaractere(ligne, col - 1, couleur, NOIR, 176);
	ecran->afficherCaractere(ligne, col, couleur, NOIR, 176);
	ecran->afficherCaractere(ligne, col + 1, couleur, NOIR, 176);
	ecran->afficherCaractere(ligne, col + 2, NOIR, NOIR, 176);

	ecran->afficherCaractere(ligne + 1, col - 2, NOIR, NOIR, 176);
	ecran->afficherCaractere(ligne + 1, col - 1, NOIR, NOIR, 176);
	ecran->afficherCaractere(ligne + 1, col, couleur, NOIR,
			ClavierHero::DESIGN_LIGNE);
	ecran->afficherCaractere(ligne + 1, col + 1, NOIR, NOIR, 176);
	ecran->afficherCaractere(ligne + 1, col + 2, NOIR, NOIR, 176);
}

Couleur Note::getCouleur(int col){
	Couleur couleur;
	if (col == ClavierHero::EMPLACEMENT_COLONNE1) {
		couleur = VERT;
	} else if (col == ClavierHero::EMPLACEMENT_COLONNE2) {
		couleur = ROUGE;
	} else if (col == ClavierHero::EMPLACEMENT_COLONNE3) {
		couleur = JAUNE;
	} else if (col == ClavierHero::EMPLACEMENT_COLONNE4) {
		couleur = BLEU_LEGER;
	}
	return couleur;
}
/*
 * Supprime la note de l ecran
 */
void Note::eraseIcon() {
	int col = getToucheCol();
	int ligne = ClavierHero::EMPLACEMENT_ZONE_JEU + 3;
	ecran->afficherCaractere(ligne - 3, col - 2, BLANC, NOIR,
			ClavierHero::DESIGN_COLONNE);
	ecran->afficherCaractere(ligne - 3, col - 1, BLANC, NOIR,
			ClavierHero::DESIGN_COLONNE);
	ecran->afficherCaractere(ligne - 3, col, BLANC, NOIR,
			ClavierHero::DESIGN_COLONNE);
	ecran->afficherCaractere(ligne - 3, col + 1, BLANC, NOIR,
			ClavierHero::DESIGN_COLONNE);
	ecran->afficherCaractere(ligne - 3, col + 2, BLANC, NOIR,
			ClavierHero::DESIGN_COLONNE);

	Couleur couleur = getCouleur(col);

	ecran->afficherCaractere(ligne - 2, col - 2, NOIR, NOIR, 176);
	ecran->afficherCaractere(ligne - 2, col - 1, NOIR, NOIR, 176);
	ecran->afficherCaractere(ligne - 2, col, couleur, NOIR,
			ClavierHero::DESIGN_LIGNE);
	ecran->afficherCaractere(ligne - 2, col + 1, NOIR, NOIR, 176);
	ecran->afficherCaractere(ligne - 2, col + 2, NOIR, NOIR, 176);

	ecran->afficherCaractere(ligne - 1, col - 2, NOIR, NOIR, 176);
	ecran->afficherCaractere(ligne - 1, col - 1, NOIR, NOIR, 176);
	ecran->afficherCaractere(ligne - 1, col, couleur, NOIR,
			ClavierHero::DESIGN_LIGNE);
	ecran->afficherCaractere(ligne - 1, col + 1, NOIR, NOIR, 176);
	ecran->afficherCaractere(ligne - 1, col + 2, NOIR, NOIR, 176);

	ecran->afficherCaractere(ligne, col - 2, NOIR, NOIR, 176);
	ecran->afficherCaractere(ligne, col - 1, NOIR, NOIR, 176);
	ecran->afficherCaractere(ligne, col, couleur, NOIR, ClavierHero::DESIGN_LIGNE);
	ecran->afficherCaractere(ligne, col + 1, NOIR, NOIR, 176);
	ecran->afficherCaractere(ligne, col + 2, NOIR, NOIR, 176);

	ecran->afficherCaractere(ligne + 1, col - 2, NOIR, NOIR, 176);
	ecran->afficherCaractere(ligne + 1, col - 1, NOIR, NOIR, 176);
	ecran->afficherMot(ClavierHero::LIGNE_AFFICHAGE_TOUCHE, col, "F?", couleur);
	ecran->afficherCaractere(ligne + 1, col + 1, NOIR, NOIR, 176);
	ecran->afficherCaractere(ligne + 1, col + 2, NOIR, NOIR, 176);
}

