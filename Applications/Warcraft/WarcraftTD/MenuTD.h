#ifndef MENUTD_H_
#define MENUTD_H_


#include <drivers/EcranV.h>
#include <drivers/ClavierV.h>
#include <drivers/Souris.h>
#include <sextant/types.h>
#include "Tour.h"

class MenuTD {
private:
	EcranV *ecr;
	int tab[25][10];
public:
	MenuTD(EcranV *ecr);
	EcranV *getEcranV();
	void afficher(Tour *t, int gold, int pv, int round);
	void initialiserSalementLeMenu();
	void modeConstruction();
	void modeUpgrade(Tour *t);
};


#endif /* MENUTD_H_ */
