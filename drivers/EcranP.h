#ifndef ECRAN_H
#define ECRAN_H

/**
 * @file Ecran.h
 * @class Ecran
 * @brief Affichage � l'�cran en couleur. Le caract�re '\\n' est pris en charge. Si l'�cran est plein, un d�filement
 * vers le bas est provoqu� lors de la cr�tion d'une nouvelle ligne.
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
		EcranP(EcranV *ecr); //initialiser l'�cran actif � l'�cran 1

	//EcranV getEcran();

	//Le set sert aussi de rafraichissement
	//Penser � associer le clavier � l'�cran actif

	void setEcran(int index);
	void raffraichir();
	EcranV *getEcranActif();


public :
	volatile caseEcran *getOrigine(){return origine;}

};

#endif
