/*
 * SonClavierHero.h
 *
 *  Created on: 24 oct. 2013
 *      Author: mathieu herbert
 */

#ifndef SONCLAVIERHERO_H_
#define SONCLAVIERHERO_H_
#include "hal/fonctionsES.h"
#include "../Note.h"
#include <sextant/Activite/Threads.h>
class SonClavierHero: public Threads {
private:
	EcranV *ecran;
	Note*  m_note;
	int duree;
public:
	SonClavierHero(EcranV *anEcran, Note* const t_note, int t_duree);
	virtual ~SonClavierHero();
	void jouer(int nFrequence);
	void note(Note* note, int time);
	int puissance(int value, int oct);
	void compterJusquA(int seconds);
	void stop();
	void run();
};

#endif /* SONCLAVIERHERO_H_ */
