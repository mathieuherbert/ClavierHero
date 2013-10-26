/*
 * SpaceInvader.h
 *
 *  Created on: 17 oct. 2008
 *      Author: Aur�lien
 */

#ifndef SPACEINVADERS_H_
#define SPACEINVADERS_H_

#include <drivers/EcranV.h>
#include <drivers/ClavierV.h>
#include "Espace.h"
#include "BlocAliens.h"
#include "Entites/EntiteFactory.h"

class SpaceInvaders : public Threads {
private:
	EcranV *ecran;
	ClavierV *clavier;
	Espace *espace;

	TimerSpaceInvaders *timer;

public:
	SpaceInvaders(EcranV *ec, ClavierV *c);

	~SpaceInvaders();

	void run();

	static int score;
};

#endif /* SPACEINVADERS_H_ */
