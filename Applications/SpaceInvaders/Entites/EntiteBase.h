/*
 * Entite.h
 *
 *  Created on: 17 oct. 2008
 *      Author: Aur�lien
 */

#ifndef ENTITE_BASE_H_
#define ENTITE_BASE_H_

#include <drivers/EcranV.h>
#include <sextant/types.h>
#include <sextant/memoire/Memoire.h>	//Gestion de la m�moire
#include "Applications/SpaceInvaders/ConfigSpaceInvader.h"
#include <sextant/Synchronisation/Semaphore/Semaphore.h>

class Espace;

/*
 * Classe entite : superclasse de toutes les entit�s de Space Invaders.
 * Si une entit� se d�place alors qu'une autre lui est contigu�, des
 * erreurs peuvent survenir. (pas de s�curit� sur l'ecrasement)
 */
class EntiteBase {

protected:
	/*
	 * Points de vie de l'entit�. Lorsqu'ils sont mis � z�ro, l'entit� est effac�e.
	 */
	int vie;
	int vieInitiale;

	/*
	 * Repr�sentation de l'affichage. (Sprite)
	 * Hauteur, largeur et couleur de premier plan du sprite.
	 */
	char *affichage;
	int hauteur;
	int largeur;
	Couleur couleur;

	/*
	 * Position verticale et horizontale de l'entit�.
	 */
	int positionLigne;
	int positionColonne;

	/*
	 * Espace li� aux entit�s. Permet de suivre l'�volution des entit�s.
	 * Semaphore permettant de g�rer le multithread sur cette entit�.
	 */
	static Espace* espace;
	static EcranV* ecran;
	Semaphore semaphore;

	/*
	 * Constructeur d'une entit�. Passage par factory.
	 */
	EntiteBase(int vie, int positionLigne, int positionColonne,
			char *affichage, int hauteur, int largeur, Couleur couleur);

	~EntiteBase();

public:

	/*
	 * Accesseurs simples.
	 * Retourne la position de l'entit� dans l'espace, et ses dimensions.
	 * getColonneCentre retourne la colonne situ�e au centre de l'entit�.
	 */
	int getPositionLigne();
	int getPositionColonne();
	Couleur getCouleur();
	int getHauteur();
	int getLargeur();
	int getColonneCentre();

	Semaphore *getSemaphore();

	/*
	 * Retourne le nombre de points de vie restant � l'entit�.
	 */
	int getPointsDeVie();
	/*
	 * Retourne le nombre de points de vie initial restant � l'entit�.
	 */
	int getPointsDeVieInitiaux();
	/*
	 * Inflige des d�gats � l'entit�.
	 */
	virtual void infligerDegats(int degat) {};
	/*
	 * Teste si l'entit� est une entit� vide.
	 * Retourne false par d�faut. Cette m�thode n'est r��crite que pour la classe
	 * EntiteVide.
	 */
	virtual bool estEntiteVide(){
		return false;
	}
	/*
	 * Teste si l'entit� est un missile.
	 * Retourne false par d�faut. Cette m�thode n'est r��crite que pour la classe
	 * Missile.
	 */
	virtual bool estMissile(){
		return false;
	}
	/*
	 * Teste si l'entit� est un alien.
	 * Retourne false par d�faut. Cette m�thode n'est r��crite que pour la classe
	 * Alien.
	 */
	virtual bool estAlien(){
		return false;
	}


	/*
	 * D�place l'entit� dans une des directions. (Voir ConfigSpaceInvader)
	 * Met � jour l'affichage en m�me temps.
	 */
	void deplacer(int direction);
	/*
	 * D�place l'entit� dans une des directions. (Voir ConfigSpaceInvader)
	 * Ne met pas � jour l'affichage, penser � effacer l'entit� avant.
	 */
	void deplacerPosition(int direction);

	/*
	 * Force le dessin de l'entit� et la lie � l'espace. Op�ration
	 * effectu�e automatiquement lors du d�placement de l'entit�.
	 */
	void dessiner();
	/*
	 * Force l'effacement du dessin de l'entit� et la lie � l'espace.
	 * Op�ration effectu�e automatiquement lors du d�placement de l'entit�
	 * ou de sa suppression.
	 */
	void effacer();

	/*
	 * Fixe le param�tre statique ecran de toutes les entit�s.
	 * M�thode appel�e une seule fois au chargement du jeu.
	 */
	static void setEcran(EcranV *ecran);
	/*
	 * Fixe le param�tre statique espace de toutes les entit�s.
	 * M�thode appel�e � chaque nouveau niveau du jeu.
	 */
	static void setEspace(Espace *espace);
};

#endif /* ENTITE_BASE_H_ */
