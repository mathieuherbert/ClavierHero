/*
 * Missile.h
 *
 *  Created on: 7 nov. 2008
 *      Author: Aurélien
 */

#ifndef MISSILE_H_
#define MISSILE_H_

#include "../TimerSpaceInvaders.h"
#include <sextant/Activite/Threads.h>
#include <Applications/SpaceInvaders/Entites/EntiteBase.h>


class Missile: public EntiteBase, public Threads {

protected:
	Semaphore *semaphore;

	int direction;
	int degats;

	static TimerSpaceInvaders *timer;

	Missile(int direction, int degats, int positionLigne, int positionColonne,
			char *affichage, int hauteur, int largeur, Couleur couleur);

	void setSemaphore(Semaphore *semaphore);
	virtual void stop(){}

public:
	void run();

	virtual bool estMissile(){
		return true;
	}

	void chercherCollision();

	static void setTimer(TimerSpaceInvaders *timer);
	static void reinitialiser();
};

#endif /* MISSILE_H_ */
