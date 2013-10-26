#ifndef EcranVMF_H
#define EcranVMF_H

/**
 * @file Ecran.h
 * @class Ecran
 * @brief Affichage e l'ecran en couleur. Le caractere '\\n' est pris en charge.
 * Si l'ecran est plein, un defilement vers le bas est provoque lors de la cretion
 * d'une nouvelle ligne.
 */

#define LIGNES 		25 // 25 lignes maximun pour un ecran
#define COLONNES	80 // 80 colonnes maximun pour un ecran
#define MAXECRAN	8
#define CURSEUR		'>' // caractere pour le curseur
#define CLIGN_OUI		1 // Clignotement
#define CLIGN_NON		0 // Clignotement
#include <sextant/types.h>
#include <hal/fonctionsES.h>
#include <drivers/EcranP.h>

/**
 * @struct caseEcran
 * @brief Une case memoire de la memoire video en mode texte.
 */
//struct caseEcran {
//	unsigned char caractere;
//	unsigned char couleurs;
//} __attribute__ ((packed));
////__attribute__ ((packed)) : compile la structure en memoire telle qu'elle est definie.


/**
 * Affiche le curseur Ã  la position ('ligne','colonne').
 */
class EcranVMF {
public:
	/**
	 * Couleur de l'arriere-plan.
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
	 * Tailles courantes
	 */

	int taille_x;
	int taille_y;
	int origine;
	int numeroReel;

	/**
	 * Adresse de la premiere case de la memoire video.
	 *
	 * volatile : signifie que l'ecriture et la lecture se font toujours
	 * en memoire (certaines optimisations du compilateur permettent
	 * d'eviter la lecture ou l'ecriture en memoire en plaçant
	 * des variables dans des registres).
	 */
public:
	caseEcran tab[LIGNES * COLONNES];

	EcranVMF();

	int getLigne();

	int getColonne();

	void setLigne(int);

	void setColonne(int);

	int positionCourrante();

	void avancerPositionCourrante();

	/***
	 * Modifie la position courante de la sortie sur l'ecran
	 ***/
	void modifierPosition(int, int);
	/*
	 * Fonction de traduction : couleur -> code
	 */
	unsigned char coderCouleur(Couleur);

	/*
	 * Fonction de traduction : clignotement + couleurs -> attribut
	 */
	unsigned char coderAttribut(Couleur, Couleur);

	unsigned char coderAttribut(Couleur, Couleur, int);

	/**
	 * Affiche le curseur e la position ('ligne','colonne').
	 */
	void afficherCurseur();
	/**
	 * Gere le defilement.
	 * Lorsque le curseur sort de l'ecran, le texte est decale d'une ligne vers le haut,
	 * liberant la derniere ligne.
	 * Le curseur se positionne en bas e gauche.
	 */
	void defilement(int nline);
	bool curseurDedans(int x, int y);
	bool surCoinInfDroit(int x, int y);
	bool surBarreDefilement(int x, int y);
	void deplacement(int x, int y);
	void redimensionner(int x, int y);

public:

	void getCase(caseEcran *C, int l, int c);

	void sautDeLigne();

	/**
	 * Efface l'ecran en le coloriant avec la couleur indiquee.
	 */
	void effacerEcranV(Couleur arrierePlan);

	void ecrireBord();
	void effacerBord();

	/**
	 * Ecrit un caractere sur l'ecran (caractere) e la position donnee (l,c)
	 * avec la couleur (prPlan) et l'attribut donne (arPlan).
	 */
	void afficherCaractereSeul(int l, int c, Couleur prPlan, Couleur arPlan,
			const char caractere);

	void
			afficherCaractere(Couleur prPlan, Couleur arPlan,
					const char caractere);

	/**
	 * Ecrit sur l'ecran le caractere e la position donnee  avec l'attribut donne.
	 * Ne gere ni le caractere de passage e la ligne ('\n')
	 * ni le defilement.
	 * Corrige les erreurs de position.
	 */
	void afficherCaractere(int ligne, int colonne, Couleur premierPlan,
			Couleur arrierePlan, const char caractere);

	/**
	 * Affiche la chaene de  caracteres sur l'ecran e la position courante
	 * avec la couleur donnee.
	 */
	void afficherMot(const char *mot, Couleur premierPlan = BLANC);
	void
			afficherMot(int l, int c, const char *mot, Couleur premierPlan =
					BLANC);

	/**
	 * Affiche un entier e la position courante de couleur prPlan (blanc par defaut)
	 * Dans la base choisie (maximum 16). Par defaut, l'entier est affiche dans la base decimale en blanc.
	 */
	void afficherBase(unsigned int entier, int base = 10, Couleur prPlan =
			BLANC);

	void afficherChiffre(const int valeur);
	void afficherChiffre(int l, int c, const int valeur);

	void miniprintf(char *fmt, ...);
};
#endif
