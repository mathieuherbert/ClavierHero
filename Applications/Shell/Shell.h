/*
 * Shell.h
 *
 *  Created on: 24 nov. 2010
 *      Author: pouda
 */


#ifndef SHELL_H_
#define SHELL_H_

#include <Applications/Shell/ListeDouble.h>
#include <Applications/Shell/IntApp.h>
#include <drivers/ClavierV.h>
#include <drivers/EcranV.h>


class Shell{
private:
	ListeDouble<IntApp> *Encours;
	ListeDouble<String> *Disponible;
public:
	Shell(EcranV listeEcran[], ClavierV *listeClavier[], int nbEcrans);
	ListeDouble<IntApp> *getEncours();
	ListeDouble<String> *getDisponible();
};

#endif /* SHELL_H_ */

