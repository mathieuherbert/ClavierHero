#ifndef CASSEBRIQUE_H
#define CASSEBRIQUE_H

#include <drivers/ClavierV.h>
#include <drivers/EcranV.h>

#include "config.h"
#include "Grille.h"
#include "Balle.h"

/**
 * @file SuperPong.h
 * @class SuperPong
 * @brief Le jeu Pong avec deux raquettes, plusieurs balles et de jolies couleurs.
 */


#include <sextant/Activite/Threads.h>

class SuperPong : public Threads{
	Grille laGrille;
	ClavierV *clavier;
	EcranV *ecran;
public:
	SuperPong(EcranV *e, ClavierV *c);
	void start();
	void init();
	void init(EcranV*,ClavierV*);
};
#endif
