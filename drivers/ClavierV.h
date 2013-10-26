#ifndef CLAVIERV_H
#define CLAVIERV_H

#include "../drivers/EcranV.h"
#include "../hal/fonctionsES.h"
#include <sextant/Synchronisation/Semaphore/Semaphore.h>
#include <sextant/interruptions/handler/handler_clavier.h>

/**
 * @file Clavier.h
 * @class Clavier
 * @brief Permet la récupération des caractères saisis au clavier.
 */

class ClavierV {
	Semaphore *semaphoreClavierV;
	char *tab;
	char *buf;
	int positioncourante;
public :
	ClavierV(Semaphore *,char*);
	/***
	 * Recupere le premier caractere tape.
	 ***/
	char getChar();
	char getChar(EcranV* ecran);
	/***
	 * Recupere tous les caracteres tapes.
	 ***/
	char* getString();

	void set_leds(void);

};

#endif
