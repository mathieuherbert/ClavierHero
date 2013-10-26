/*
 * EntiteVide.h
 *
 *  Created on: 20 oct. 2008
 *      Author: Aurélien
 */

#ifndef ENTITE_VIDE_H_
#define ENTITE_VIDE_H_

#include "EntiteBase.h"


class EntiteVide :public EntiteBase {

public:
	EntiteVide(int positionLigne, int positionColonne, char *caractere, Couleur couleur);

	/*
	 * Retourne true dans le cas d'une entité vide.
	 */
	virtual bool estEntiteVide();

};

#endif /* ENTITE_VIDE_H_ */
