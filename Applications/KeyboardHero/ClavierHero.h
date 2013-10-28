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
	static bool C1DESSUS ;
	static bool C1OK ;
	static bool C1DESSOUS ;

	static bool C2DESSUS ;
	static bool C2OK ;
	static bool C2DESSOUS ;

	static bool C3DESSUS ;
	static bool C3OK ;
	static bool C3DESSOUS ;

	static bool C4DESSUS ;
	static bool C4OK ;
	static bool C4DESSOUS ;

	static bool C1PIECEVALIDER ;
	static bool C2PIECEVALIDER ;
	static bool C3PIECEVALIDER ;
	static bool C4PIECEVALIDER ;

	static bool SCORE_TROP_BAS;
	static int VAL_SCORE_INF;

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
