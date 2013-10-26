/*
 * Espace.h
 *
 *  Created on: 17 oct. 2008
 *      Author: Aur�lien
 */

#ifndef ESPACE_H_
#define ESPACE_H_

#include "TimerSpaceInvaders.h"
#include "drivers/ClavierV.h"
#include "FondEspace.h"
#include "BlocAliens.h"

/*
 * Classe Espace.
 * Permet de r�ferencer les entit�s pr�sentes dans ce niveau.
 * Tout r�ferencement ou demande de r�ferencement d'entit� doit s'effectuer
 * dans la zone allouable de l'espace, c'est � dire :
 * 			Ligne : [1; 25]
 * 			Colonne : [0; 80]
 */
class Espace {

private:
	/*
	 * Espace dans lequel �voluent les entit�s du jeu.
	 * C'est un tableau lin�aris�. (ligne, colonne) est plac� � l'adresse
	 * [ligne*LARGEUR + colonne).
	 */
	EntiteBase *espace[LARGEUR * HAUTEUR]; //Lin�arisation du tableau.
	EcranV *ecran;
	TimerSpaceInvaders *timer;
	ClavierV *clavier;

	/*
	 * Entit�s mouvantes.
	 */
	Canon *canon;
	BlocAliens *blocAliens;

	/*
	 * Tronche de l'espace, couleur d'arri�re, de premier plan, et image de fond.
	 */
	FondEspace *fondEspace;

	/*
	 * Niveau de l'espace.
	 */
	int niveau;
	/*
	 * Bool�en permettant la pause en fin de niveau.
	 */
	bool niveauAcheve;

public:

	Espace(EcranV *ecran, TimerSpaceInvaders *timer, ClavierV *clavier,
			const int niveau);
	~Espace();

	/*
	 * Retourne la couleur d'arri�re plan et d'avantplan de l'espace.
	 */
	Couleur getCouleurArPlanAt(int ligne, int colonne);
	Couleur getCouleurPrPlanAt(int ligne, int colonne);

	/*
	 * Retourne l'entit� occupant la zone sp�cifi�e par (ligne, colonne).
	 * Fixe l'entit� pr�sente dans la zone sp�cifi�e par (ligne, colonne).
	 */
	EntiteBase *getEntite(int ligne, int colonne);
	void setEntite(EntiteBase *entite, int ligne, int colonne);
	/*
	 * Lie l'entit� � l'espace.
	 * Effectue la liaison pour chacune des cases de l'espace concern�e.
	 * Supprime tous les liens de l'entit� dans l'espace.
	 */
	void ajouterEntite(EntiteBase *entite);
	void supprimerEntite(EntiteBase *entite);

	/*
	 * Place une entit� vide dans la zone sp�cifi�e par (ligne, colonne).
	 */
	void setEntiteVide(int ligne, int colonne);

	/*
	 * Remplit la totalit� de l'espace par des entit�s vides.
	 * Redessine les entit�s pr�sentes dans chacune des cases de l'espace.
	 * Cr�er les bunkers dans l'espace.
	 */
	void remplirEspaceVide();
	void redessinerEspace();
	void creerBunkers(int niveau, Couleur couleur, int resistance);

	/*
	 * D�marre les threads du canon et du bloc aliens, ou les bloque.
	 */
	void demarrerEspace();
	void stopperEspace();

	BlocAliens *getBlocAliens();
	Canon *getCanon();
	const int getNiveau();

	bool niveauTermine();
};

#endif /* ESPACE_H_ */
