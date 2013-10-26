#ifndef ECRAN_H
#define ECRAN_H

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
#include <drivers/EcranV.h>
#include <drivers/ClavierV.h>

class EcranP {

	static volatile caseEcran *origine;

	EcranV *ecranActif;
	EcranV *ecran;
	ClavierV *clavier;

	public:
		EcranP(EcranV *ecr); //initialiser l'écran actif à l'écran 1

	//EcranV getEcran();

	//Le set sert aussi de rafraichissement
	//Penser à associer le clavier à l'écran actif

	void setEcran(int index);
	void raffraichir();
	EcranV *getEcranActif();


public :
	volatile caseEcran *getOrigine(){return origine;}

};

#endif
