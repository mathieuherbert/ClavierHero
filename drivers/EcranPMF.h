#ifndef ECRANPMF_H
#define ECRANPMF_H

/**
 * @file Ecran.h
 * @class Ecran
 * @brief Affichage à l'écran en couleur. Le caractère '\\n' est pris en charge. Si l'écran est plein, un défilement
 * vers le bas est provoqué lors de la crétion d'une nouvelle ligne.
 */

#define CRT_REG_INDEX 0x3d4
#define CRT_REG_DATA  0x3d5
#define VIDEO   	0xb8000

#include <sextant/types.h>
#include <hal/fonctionsES.h>
#include <drivers/EcranVMF.h>
#include <drivers/ClavierP.h>

class EcranPMF  {

	static volatile caseEcran *origine;
	caseEcran vide[LIGNES*COLONNES];
	EcranVMF *ecranActif;
//	EcranVMF *ecran;
	ClavierP *clavierP;
	EcranVMF *tabEcran[MAXECRAN+1];
	int numeroEcranActif;
	int nombreFenetres;

	public:
		EcranPMF(EcranV *lecran); //initialiser l'écran actif

	//EcranV getEcran();

	//Le set sert aussi de rafraichissement
	//Penser à associer le clavier à l'écran actif

	EcranVMF* getEcransV();

	void setEcran(int index);

	void setFenetre(int index);

	void vider();

	void deplacerGauche();

	void deplacerDroite();

	void deplacerHaut();

	void deplacerBas();

	void ecrire(char c);

	void ouvrirFenetre();

	void fermerFenetre();

public :
	void start();

};

#endif
