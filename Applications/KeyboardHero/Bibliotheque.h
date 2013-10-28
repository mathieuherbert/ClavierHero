/*
 * Bibliotheque.h
 *
 *  Created on: 27 oct. 2013
 *      Author: julienderay
 */

#ifndef BIBLIOTHEQUE_H_
#define BIBLIOTHEQUE_H_

#include "Note.h"
#include "model/Hauteur.h"
#include "model/Octave.h"
#include "model/Puls.h"
#include "model/Touche.h"
#include "Partition.h"

class Partition;

class Bibliotheque {
private:
	EcranV* ecran;
	Timer* timer;

public:
	Bibliotheque(EcranV* e, Timer* t);
	void afficherNomPartition(char* part);
	void auClairDeLaLune();
	void superMario();
};


#endif /* BIBLIOTHEQUE_H_ */
