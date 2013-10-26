/*
 * BlocAliens.h
 *
 *  Created on: 27 oct. 2008
 *      Author: Aurélien
 */

#ifndef BLOCALIENS_H_
#define BLOCALIENS_H_

#include "TimerSpaceInvaders.h"
#include <sextant/Activite/Threads.h>
#include "ConfigSpaceInvader.h"
#include "Entites/EntiteFactory.h"
#include "Random.h"

class Espace;

/*
 * Bloc d'aliens.
 * Si le sémaphore deplacementAliens du timer est dispo, le bloc se déplace.
 */
class BlocAliens: public Threads {

private:
	/*
	 * Le timer sert à gérer le mouvement suivant les tic d'horloges et interruption.
	 */
	TimerSpaceInvaders *timer;
	Espace *espace;

	/*
	 * Tableau d'aliens.
	 * Largeur et Hauteur sont les dimensions actuelles du tableau, pouvant varier
	 * suivant la destruction des aliens. EcartGauche et EcartHaut interviennent
	 * lorsque le bloc est diminué à gauche ou à droite.
	 */
	int hauteur, largeur, ecartGauche;
	Alien *blocAliens[LARGEUR_BLOC_ALIEN_MAX * HAUTEUR_BLOC_ALIEN_MAX]; //Linéarisation du tableau.

	/*
	 * Direction de déplacement du bloc, ainsi que sa vitesse.
	 * Position du bloc dans l'espace. Repéré par son entité en haut à gauche.
	 * Nombre d'aliens présents dans le bloc.
	 */
	int direction, vitesseBlocInitiale, positionLigne, positionColonne,
			nombreAliens, nombreAliensInitial;

	/*
	 * Générateur de nombres aléatoires.
	 */
	Random random;

public:

	BlocAliens(TimerSpaceInvaders *timer, Espace *espace, int vitesse,
			int positionLigne = 2, int positionColonne = 15);
	~BlocAliens();


	/*
	 * Accesseurs simples.
	 */
	int getPositionLigne();
	int getPositionColonne();
	int getEcartGauche();
	int getHauteur();
	int getLargeur();
	int getDirection();

	void run();

	/*
	 * Retourne l'entité depuis les coordonnées intra-bloc.
	 * Retourne le nombre d'aliens restants sauvegardé (rapide) ou le recalcule (lent).
	 */
	Alien *getAlien(int ligne, int colonne);
	int getNombreAliensRestants();
	int calculerNombreAliensRestants();
	/*
	 * Retourne les positions intrabloc de l'alien.
	 */
	int getPositionLigne(Alien *alien);
	int getPositionColonne(Alien *alien);

	void creerBloc1();
	void ajouterAlien(int ligne, int colonne, Alien *alien);
	void retirerAlien(Alien *alien);

	void deplacer();
	void effacer();
	void dessiner();

	void ajusterDimensionsBloc();
	void ajusterDimensionAGauche();
	void ajusterDimensionADroite();
	void ajusterDimensionEnBas();

	void ajusterVitesse();
	void tirerMissile();

};

#endif /* BLOCALIENS_H_ */
