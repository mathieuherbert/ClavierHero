/*
 * BlocAliens.h
 *
 *  Created on: 27 oct. 2008
 *      Author: Aur�lien
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
 * Si le s�maphore deplacementAliens du timer est dispo, le bloc se d�place.
 */
class BlocAliens: public Threads {

private:
	/*
	 * Le timer sert � g�rer le mouvement suivant les tic d'horloges et interruption.
	 */
	TimerSpaceInvaders *timer;
	Espace *espace;

	/*
	 * Tableau d'aliens.
	 * Largeur et Hauteur sont les dimensions actuelles du tableau, pouvant varier
	 * suivant la destruction des aliens. EcartGauche et EcartHaut interviennent
	 * lorsque le bloc est diminu� � gauche ou � droite.
	 */
	int hauteur, largeur, ecartGauche;
	Alien *blocAliens[LARGEUR_BLOC_ALIEN_MAX * HAUTEUR_BLOC_ALIEN_MAX]; //Lin�arisation du tableau.

	/*
	 * Direction de d�placement du bloc, ainsi que sa vitesse.
	 * Position du bloc dans l'espace. Rep�r� par son entit� en haut � gauche.
	 * Nombre d'aliens pr�sents dans le bloc.
	 */
	int direction, vitesseBlocInitiale, positionLigne, positionColonne,
			nombreAliens, nombreAliensInitial;

	/*
	 * G�n�rateur de nombres al�atoires.
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
	 * Retourne l'entit� depuis les coordonn�es intra-bloc.
	 * Retourne le nombre d'aliens restants sauvegard� (rapide) ou le recalcule (lent).
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
