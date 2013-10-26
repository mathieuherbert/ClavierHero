/*
 * PlateauPacmanPacman.h
 *
 *  Created on: 5 oct. 2012
 *      Author: killerider
 */

#ifndef PlateauPacmanPACMAN_H_
#define PlateauPacmanPACMAN_H_

#include "CasePacman.h"
#include "Personnages/Blinky.h"
#include "Personnages/Pacman.h"
#include "Personnages/Clyde.h"
#include "Personnages/Inky.h"
#include "Personnages/Pinky.h"
#include "Personnages/PersonnagePacman.h"
#include "config.h"
#include "Algorithme/Dijkstra.h"

class PlateauPacman {

public :
	CasePacman tab[HAUTEUR][LARGEUR]; //Tableau des cases du jeu.
	bool partieGagnee; //Booleen qui permet de savoir si le niveau est termine
	EcranV *ecran;
	bool jouer;

	Pacman pacman;

    Blinky blinky;

    Clyde clyde;

    Inky inky;

    Pinky pinky;
    bool touche;
    int score;
    int vie;

	Dijkstra D;



	/**
	 * Construit la grille avec les murs, les zones privées, le personnage, les caisses et les rangements en fonction du niveau passe en parametre
	 */
	PlateauPacman(EcranV *);

	void initPlateau();

	void updatePositionPersonnages();
	void updatePositionPersonnage(PersonnagePacman * perso);

	/*
	 * permet d'acceder a la case de position (x,y) du PlateauPacman
	 */
	CasePacman* getCase(int x,int y);

	void initPersonnages();


	void afficherPersoEcran(PersonnagePacman * perso);

	void paint(EcranV *e, int x, int y);

	Pacman * getPacman();

	void bougerPersonnages(int sec);

	void bougerPersonnage(PersonnagePacman * perso, int sec);

	bool aPerdu();

};


#endif /* PlateauPacman_H_ */
