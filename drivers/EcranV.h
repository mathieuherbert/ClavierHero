#ifndef ECRANV_H
#define ECRANV_H

/**
 * @file Ecran.h
 * @class Ecran
 * @brief Affichage à l'écran en couleur. Le caractère '\\n' est pris en charge. Si l'écran est plein, un défilement
 * vers le bas est provoqué lors de la crétion d'une nouvelle ligne.
 */

#define LIGNES 		25 // 25 lignes maximun pour un écran
#define COLONNES	80 // 80 colonnes maximun pour un écran
#define CURSEUR		'>' // caractère pour le curseur
#define CLIGN_OUI		1 // Clignotement
#define CLIGN_NON		0 // Clignotement

#include <sextant/types.h>
#include <hal/fonctionsES.h>
//#include <drivers/Ecran.h>


/**
 * @struct caseEcran
 * @brief Une case mémoire de la mémoire vidÃ©o en mode texte.
 */
struct caseEcran {
	unsigned char caractere;
	unsigned char couleurs;
} __attribute__ ((packed));
//__attribute__ ((packed)) : compile la structure en mémoire telle qu'elle est définie.


/**
 * Affiche le curseur Ã  la position ('ligne','colonne').
 */
class EcranV {

	/**
	 * Couleur de l'arrière-plan.
	 */
	Couleur arrierePlan;
	/**
	 * Ligne courante.
	 */
	int ligne;
	/**
	 * Colonne courante.
	 */
	int colonne;
	/**
	 * Adresse de la première case de la mémoire vidéo.
	 *
	 * volatile : signifie que l'écriture et la lecture se font toujours
	 * en mémoire (certaines optimisations du compilateur permettent
	 * d'éviter la lecture ou l'écriture en mémoire en plaçant
	 * des variables dans des registres).
	 */
	public :
	caseEcran tab[LIGNES*COLONNES];

	EcranV();

	int getLigne();

	int getColonne();


	void setLigne(int);

	void setColonne(int);

	int positionCourrante();

	void avancerPositionCourrante();

	void reculerPositionCourante();

	/***
	 * Modifie la position courante de la sortie sur l'écran
	 ***/
	void modifierPosition(int l,int c);
	/*
	 * Fonction de traduction : couleur -> code
	 */
	unsigned char coderCouleur(Couleur);

	/*
	 * Fonction de traduction : clignotement + couleurs -> attribut
	 */
	unsigned char coderAttribut(Couleur, Couleur);

	unsigned char coderAttribut(Couleur , Couleur ,int);

	/**
	 * Affiche le curseur à  la position ('ligne','colonne').
	 */
	void afficherCurseur();
	/**
	 * Gère le défilement.
	 * Lorsque le curseur sort de l'écran, le texte est décalé d'une ligne vers le haut,
	 * libérant la dernière ligne.
	 * Le curseur se positionne en bas à  gauche.
	 */
	void defilement(int nline);

public :

	void getCase(caseEcran *C,int l,int c);

	void sautDeLigne();


	/**
	 * Efface l'écran en le coloriant avec la couleur indiquée.
	 */
	void effacerEcranV(Couleur arrierePlan);

	/**
	 * Ecrit un caractère sur l'écran (caractère) à  la position donnée (l,c)
	 * avec la couleur (prPlan) et l'attribut donné (arPlan).
	 */
	void afficherCaractereSeul(int l,int c,Couleur prPlan,Couleur arPlan,const char caractere);

	void afficherCaractere(Couleur prPlan,Couleur arPlan,const char caractere);
	void effacerCaractere();

	/**
	 * Ecrit sur l'écran le caractère à  la position donnée  avec l'attribut donné.
	 * Ne gère ni le caractère de passage à la ligne ('\n')
	 * ni le défilement.
	 * Corrige les erreurs de position.
	 */
	void afficherCaractere(int ligne, int colonne,Couleur premierPlan, Couleur arrierePlan,const char caractere);

	/**
	 * Affiche la chaîne de  caractères sur l'écran à  la position courante
	 * avec la couleur donnée.
	 */
	void afficherMot(const char *mot,Couleur premierPlan=BLANC);
	void afficherMot(int l,int c,const char *mot,Couleur premierPlan=BLANC);

	/**
	 * Affiche un entier à  la position courante de couleur prPlan (blanc par defaut)
	 * Dans la base choisie (maximum 16). Par défaut, l'entier est affiché dans la base décimale en blanc.
	 */
	void afficherBase(unsigned int entier,int base=10,Couleur prPlan=BLANC);

	void afficherChiffre( const int valeur);
	void afficherChiffre(int l,int c, const int valeur);

	void miniprintf(char *fmt, ...);
};
#endif
