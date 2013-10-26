/*
 * EntiteFactory.cpp
 *
 *  Created on: 22 oct. 2008
 *      Author: Aurélien
 */

#include "EntiteFactory.h"

Canon* EntiteFactory::canon=0;

Alien* EntiteFactory::creerAlienRobot(int niveau) {
	return new Alien(3 * Config::getPVAliens(niveau) - 1, "{@@}\057\42\42\134", 2, 4, Config::getCouleurAlienRobot(niveau));
}
Alien* EntiteFactory::creerAlienDoob(int niveau) {
	return new Alien(2 * Config::getPVAliens(niveau) - 1, "dOOb^\057\134^", 2, 4, Config::getCouleurAlienRobot(niveau));
}
Alien* EntiteFactory::creerAlienBat(int niveau) {
	return new Alien(Config::getPVAliens(niveau), "\057MM\134\134~~\057", 2, 4, Config::getCouleurAlienBat(niveau));
}
Alien* EntiteFactory::creerBoss(int niveau) {
	return new Alien(Config::getPVAliens(niveau), " _\057^\134_ |#####|", 2, 7, Config::getCouleurAlienRobot(niveau));
}

Alien* EntiteFactory::creerAlienPinguin(int positionLigne, int positionColonne) {
	return new Alien(1, "(*>() ^^ ", 3, 3, BLEU);
}
Alien* EntiteFactory::creerAlienFish(int positionLigne, int positionColonne) {
	return new Alien(1, "<*))><", 1, 7, BLEU);
}

Canon* EntiteFactory::creerCanon(TimerSpaceInvaders *timer, ClavierV *clavier,
		int positionLigne, int positionColonne) {
	if(EntiteFactory::canon==0)
		EntiteFactory::canon = new Canon(timer, clavier, 3, positionLigne, positionColonne, " mAm MAZAM", 2, 5, VERT);

		return EntiteFactory::canon;

}

Bunker* EntiteFactory::creerBunker(int positionLigne, int positionColonne,
		Couleur couleur, int resistance) {
	return new Bunker(resistance, positionLigne, positionColonne, "M", couleur);
}
