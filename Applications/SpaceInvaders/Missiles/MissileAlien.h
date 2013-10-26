/*
 * Missile.h
 *
 *  Created on: 5 nov. 2008
 *      Author: MATTHIEU
 */

#ifndef MISSILE_ALIEN_H_
#define MISSILE_ALIEN_H_

#include "Missile.h"

class MissileAlien : public Missile {
	friend class EntiteFactory;

private:
	int numeroMissile;
	static int nombreMaxMissiles;

protected:
	MissileAlien(TimerSpaceInvaders *timer, int degats, int numero, int positionLigne, int positionColonne,
			char *affichage, int hauteur, int largeur, Couleur couleur);

	virtual void stop();

public:

	static bool missileDisponible();
	static int getNombre();
	static void reinitialiser();

	static void setNombreMaxMissiles(int nombreMaxMissiles);
	static MissileAlien *getMissileAlien(int numero);
	static MissileAlien *lancerNouveauMissile(int positionLigne, int positionColonne);

};
#endif /* MISSILE_ALIEN_H_ */
