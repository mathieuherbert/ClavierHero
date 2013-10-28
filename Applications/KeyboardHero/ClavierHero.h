/*
 * ClavierHero.h
 *
 *  Created on: 23 oct. 2013
 *      Author: Julien Deray, Mathieu Cartaud, Mathieu Herbert
 */

#ifndef CLAVIERHERO_H_
#define CLAVIERHERO_H_

#include <drivers/EcranV.h>
#include <drivers/ClavierV.h>
#include <sextant/Activite/Threads.h>
#include <sextant/Synchronisation/Semaphore/Semaphore.h>
#include "Bibliotheque.h"

class ClavierHero : public Threads{
private:
	EcranV *ecran;
	ClavierV *clavier;
	Timer *timer;

public:
	//Pour toutes les colonnes : C1Dessus => valider quelques lignes au dessus de la ligne validation
	//C1OK => valider sur la ligne de validation
	//C1Dessous =>valider quelques lignes en dessous de la ligne validation
	static bool c1Dessus;
	static bool c1ok ;
	static bool c1Dessous ;

	static bool c2Dessus;
	static bool c2ok ;
	static bool c2Dessous ;

	static bool c3Dessus;
	static bool c3ok ;
	static bool c3Dessous ;

	static bool c4Dessus;
	static bool c4ok ;
	static bool c4Dessous ;

	//True si la piece de la colonne est valider
	static bool c1PieceValider;
	static bool c2PieceValider;
	static bool c3PieceValider;
	static bool c4PieceValider;
	//si partie est perdue ou pas
	static bool scoreTropBas;
	//Score pour lequel la partie est arrete
	static int valScoreInf;

	static const char DESIGN_LIGNE='|';
	static const int DESIGN_COLONNE=170;
	static const int EMPLACEMENT_COLONNE1=8;
	static const int EMPLACEMENT_COLONNE2=23;
	static const int EMPLACEMENT_COLONNE3=38;
	static const int EMPLACEMENT_COLONNE4=53;
	static const int EMPLACEMENT_ZONE_JEU_DESSUS=19;
	static const int EMPLACEMENT_ZONE_JEU=20;
	static const int EMPLACEMENT_ZONE_JEU_DESSOUS=21;
	static const int EMPLACEMENT_ZONE_JEU_TROP_TARD=22;
	static const int LIGNE_AFFICHAGE_TOUCHE=24;
	static const int FUN = 1;
	static const int FDEUX = 2;
	static const int FTROIS = 3;
	static const int FQUATRE = 4;
	static const int NOTEOK = 2;
	static const int NOTEPRESQUEOK = 4;
	static int score;
    void afficherScore();

	ClavierHero(EcranV *e, ClavierV *c);
	~ClavierHero();
	void init();
	void run();
	static void afficherChiffreCommente(EcranV* l_ecran,int l, int c, const char* label,
			const int valeur, const int nbChiffres);
	void afficherLignes(int ligne1, int ligne2, int ligne3, int ligne4);
	void afficherTouches(int ligne1, int ligne2, int ligne3, int ligne4);
	void afficherLigneDeJeu(int colonne);
	void setToucheJouee(int touche);
	void mario();
	void lune();
};


#endif /* CLAVIERHERO_H_ */
