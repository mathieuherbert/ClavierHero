/*
 * Joueur.h
 *
 *  Created on: 12 déc. 2011
 *      Author: Math
 */

#ifndef JOUEURTD_H_
#define JOUEURTD_H_

#include "MapTD.h"
#include "MenuTD.h"
extern Souris mouse;

class JoueurTD:public Threads{
public:
	int static const lifeinit=30;
	int static const goldinit=200;
	EcranV *ecr;
	MenuTD *menuTD;
	char action;
	ClavierV *clavier;
	MapTD *mapTD;
	bool fini,bfglaive;
	int gold;
	int life;
	int xCurseur, yCurseur;
	char caractere;

	JoueurTD(EcranV *ecr,ClavierV *clavier);
	void round();
	void majCurseur(int xCurseur, int yCurseur,char caractere);
	void run();
};

#endif /* JOUEUR_H_ */
