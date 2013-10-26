#ifndef BALLE_H
#define BALLE_H

#include "RandomSP.h"
#include "Grille.h"
#include <sextant/Activite/Threads.h>
/**
 * @file Balle.h
 * @class Balle
 * @brief Une balle du casse brique.
 */
class Balle : public Threads {

	/**
	 * Grille dans laquelle se trouve la balle.
	 */
	Grille* grille;
	/**
	 * Vitesse de déplacement de la balle.
	 */
	int vitesse;
	/**
	 * Position de la balle dans la grille. y, position verticale.
	 * x, position horizontale.
	 */
	int x, y ;
	/**
	 * Direction de la balle donnée par le déplacement vertical et horizontal.
	 */
	int dx, dy ;
	/**
	 * Fait avancer la balle du déplacement dy,dx.
	 */
	void bouger();//Avance dans la direction dx,dy

public :
	/**
	 * Constructeur. Ajoute une balle dans la grille et affecte une sémaphore à la balle.
	 * @param la grille du jeu.
	 * @param Sémaphore permettant d'obtenir les ressources pour traverser les zones
	 *  spéciales.
	 */
	Balle(Grille*);
	/**
	 * Permet de savoir si la balle est toujours en jeu.
	 * @return vrai si la balle est toujours en jeu.
	 */
	bool avance();
	void start();
};
#endif
