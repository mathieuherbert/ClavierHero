#ifndef SOURIS_H
#define SOURIS_H

#include "../drivers/EcranV.h"
#include "../hal/fonctionsES.h"
/**
 * @file Souris.h
 * @class Souris
 * @brief Permet la rÃ©cupÃ©ration des données souris sur le port série
 */

class Souris {
public :

	int x0;
	int y0;
	int x;
	int y;
	int before_mouse_x;
	int before_mouse_y;

	bool clicG;
	bool clicD;
	bool clicM;

	void initialiser(EcranV *ecran);
	void actualiser(EcranV *ecran);
	void bouger(EcranV *ecran);


};

#endif
