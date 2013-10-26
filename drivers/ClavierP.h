#ifndef CLAVIERP_H
#define CLAVIERP_H

#include "../drivers/EcranV.h"
#include "../hal/fonctionsES.h"
#include <sextant/Synchronisation/Semaphore/Semaphore.h>
#include <sextant/interruptions/handler/handler_clavier.h>
#include <sextant/Activite/Threads.h>

/**
 * @file Clavier.h
 * @class Clavier
 * @brief Permet la récupération des caractères saisis au clavier.
 */

#define MAXCONSOLE 10


class ClavierP : public Threads {
	EcranV *ecran;
	int positioncourante;

public :
	ClavierP(EcranV*);
	/***
	 * Recupere le premier caractere tape.
	 ***/
	void run();
	char getChar();
	/***
	 * Recupere tous les caracteres tapes.
	 ***/


};

#endif
