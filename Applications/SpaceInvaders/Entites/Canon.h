/*
 * Canon.h
 *
 *  Created on: 22 oct. 2008
 *      Author: Aurélien
 */

#ifndef CANON_H_
#define CANON_H_

#include "../TimerSpaceInvaders.h"
#include <drivers/ClavierV.h>
#include <sextant/Activite/Threads.h>
#include "EntiteBase.h"

class Canon: public EntiteBase, public Threads {
	friend class EntiteFactory;

protected:
	TimerSpaceInvaders *timer;
	ClavierV *clavier;

	Canon(TimerSpaceInvaders *timer, int vie, int positionLigne,
			int positionColonne, char *affichage, int hauteur, int largeur,
			Couleur couleur);
	Canon(TimerSpaceInvaders *timer, ClavierV *clavier, int vie,
			int positionLigne, int positionColonne, char *affichage,
			int hauteur, int largeur, Couleur couleur);

public:
	void run();

	void lancerMissile();

	virtual void infligerDegats(int degats);
};

#endif /* CANON_H_ */
