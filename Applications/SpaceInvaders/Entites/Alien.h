/*
 * Alien.h
 *
 *  Created on: 22 oct. 2008
 *      Author: Aurélien
 */

#ifndef ALIEN_H_
#define ALIEN_H_

#include "EntiteBase.h"

class Alien: public EntiteBase {
	friend class EntiteFactory;

protected:
	Alien(int vie, char *affichage, int hauteur, int largeur, Couleur couleur);


public:
	virtual ~Alien();
	void setPositionLigne(int positionLigne);
	void setPositionColonne(int positionColonne);

	virtual void infligerDegats(int degats);
	virtual bool estAlien(){
		return true;
	}
};

#endif /* ALIEN_H_ */
