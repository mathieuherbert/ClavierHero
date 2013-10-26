/*
 * Trame.h
 *
 *  Created on: 30 nov. 2009
 *      Author: menaud
 */

#ifndef TRAME_H_
#define TRAME_H_

#include "PortSerie.h"
#include <sextant/types.h>


typedef struct uneTrame {
	char deb_fan;
	message monMessage;
	char fin_fan;
//	uneTrame() : deb_fan('x'), fin_fan('x') {}
};

class Trame {

	uneTrame maTrame;
	PortSerie monportserie;

public :

	Trame();
	void emettreTrame(const char*message); // envois un message
	message *recevoirTrame();  // retourne un message

};
#endif /* TRAME_H_ */
