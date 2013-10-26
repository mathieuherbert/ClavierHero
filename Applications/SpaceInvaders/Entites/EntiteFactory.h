/*
 * EntiteFactory.h
 *
 *  Created on: 22 oct. 2008
 *      Author: Aurélien
 */

#ifndef ENTITEFACTORY_H_
#define ENTITEFACTORY_H_

#include "Alien.h"
#include "Canon.h"
#include "Bunker.h"
#include <Applications/SpaceInvaders/Missiles/MissileAlien.h>
#include <Applications/SpaceInvaders/Missiles/MissileCanon.h>

/*
 * Classe permettant la création des entités.
 */


class EntiteFactory {

public:
	static Canon* canon;
	static Alien* creerAlienRobot(int niveau);
	static Alien* creerAlienBat(int niveau);
	static Alien* creerAlienDoob(int niveau);
	static Alien* creerBoss(int niveau);

	static Alien* creerAlienPinguin(int positionLigne, int positionColonne);
	static Alien* creerAlienFish(int positionLigne, int positionColonne);

	static Canon* creerCanon(TimerSpaceInvaders *timer, ClavierV *clavier, int positionLigne, int positionColonne);

	static Bunker* creerBunker(int positionLigne, int positionColonne,
			Couleur couleur, int resistance);

};

#endif /* ENTITEFACTORY_H_ */
