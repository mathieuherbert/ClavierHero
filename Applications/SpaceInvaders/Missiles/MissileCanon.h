/*
 * Missile.h
 *
 *  Created on: 5 nov. 2008
 *      Author: MATTHIEU
 */

#ifndef MISSILE_CANON_H_
#define MISSILE_CANON_H_

#include "Missile.h"

class MissileCanon : public Missile{

private:
	static MissileCanon *singleton;

protected:

	MissileCanon(TimerSpaceInvaders *timer, int vie, int positionLigne,
			int positionColonne, char *affichage, int hauteur, int largeur,
			Couleur couleur);

	virtual void stop();

public:

	static bool missileDisponible();
	static int getNombre();
	static void reinitialiser();

	/*
	 * Retourne le singleton du missileCanon ou en créer un nouveau si l'ancien
	 * est détruit.
	 */
	static MissileCanon *getMissileCanon();
	static MissileCanon *lancerNouveauMissile(int positionColonne);

};
#endif /* MISSILE_CANON_H_ */
