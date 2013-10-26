#ifndef CASEPACMAN_H
#define CASEPACMAN_H

#include <drivers/EcranV.h>
#include <drivers/PortSerie.h>
#include "config.h"

class CasePacman {
	/**
	 * Ecran pour l'affichage de la case
	 */
	EcranV *ecran;
	/**
	 * coordonnees de la case dans la grille.
	 */
    int x, y ;
    /**
     * Etat de la case. Permet de savoir si la case est un rangement, un mur, un carton ou le bonhomme.
     */
    int etat;

public:
	//Modifieurs
	void setEcran(EcranV *e);
	void setCaseMur();
    void setCaseVide();
    void setCaseFruit();
    void setCaseTeleportG();
    void setCaseTeleportD();

    //Accesseurs
    EcranV *getEcran();
    int getx();
    int gety();
    //methodes
    /**
     * permet de renvoyer l'etat de la case
     */
    int getEtat();
    /**
     * definit la case x,y comme une case vide.
     */
    void init(int x, int y, EcranV *e);

    /**
     * Affiche la case.
     */
    void paint();

    bool estMur();
    bool estFruit();
    bool estTeleportG();
    bool estTeleportD();


};
#endif
