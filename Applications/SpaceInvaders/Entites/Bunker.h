/*
 * Bunker.h
 *
 *  Created on: 22 oct. 2008
 *      Author: Aurélien
 */

#ifndef BUNKER_H_
#define BUNKER_H_

#include "EntiteBase.h"

class Bunker: public EntiteBase {
	friend class EntiteFactory;

protected:
	Bunker(int vie, int positionLigne, int positionColonne,
			char *affichage, Couleur couleur);

public:
	virtual void infligerDegats(int degats);
};

#endif /* BUNKER_H_ */
