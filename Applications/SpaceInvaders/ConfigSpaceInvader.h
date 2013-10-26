#ifndef CONFIG_SPACE_INVADER_H
#define CONFIG_SPACE_INVADER_H

/***
 * @file config.h
 * @brief Fichier de configuration du jeu.
 * N.B. : Les zones doivent Ãªtre entourÃ©es par un espace vide.
 * Les zones doivent Ãªtre inclues les unes dans les autres
 ***/

/*** Taille du jeu ***/
#define LARGEUR 	80
#define HAUTEUR 	25
/*** Direction de déplacement ***/
#define DEPL_GAUCHE 	1
#define DEPL_DROITE 	2
#define DEPL_HAUT 		3
#define DEPL_BAS 		4
/*** Vitesses de déplacement du missile canon ***/
#define VITESSE_MISSILE_CANON	15
/*** Taille du bloc d'aliens ***/
#define LARGEUR_BLOC_ALIEN_MAX 	10
#define HAUTEUR_BLOC_ALIEN_MAX 	6
/*** Nombre missiles aliens simultanés par niveau ***/
#define MISSILES_ALIENS_MAX	10
/*** Nombre missiles aliens simultanés par niveau ***/
#define TAILLE_CANON 5

// Gestion des niveaux :

/*** Taille du bloc d'aliens ***/
#define LARGEUR_BLOC_ALIEN_NIV_1 	6
#define LARGEUR_BLOC_ALIEN_NIV_2 	8
#define LARGEUR_BLOC_ALIEN_NIV_3 	8
#define LARGEUR_BLOC_ALIEN_NIV_4 	10
#define LARGEUR_BLOC_ALIEN_NIV_5 	10
#define HAUTEUR_BLOC_ALIEN_NIV_1 	3
#define HAUTEUR_BLOC_ALIEN_NIV_2 	4
#define HAUTEUR_BLOC_ALIEN_NIV_3 	5
#define HAUTEUR_BLOC_ALIEN_NIV_4 	5
#define HAUTEUR_BLOC_ALIEN_NIV_5 	6
/*** Vitesses de déplacement des missiles aliens ***/
#define VIT_MISSILE_ALIEN_NIV_1		300
#define VIT_MISSILE_ALIEN_NIV_2		300
#define VIT_MISSILE_ALIEN_NIV_3		250
#define VIT_MISSILE_ALIEN_NIV_4		250
#define VIT_MISSILE_ALIEN_NIV_5		200
#define VIT_MISSILE_BOSS_NIV_1		200
#define VIT_MISSILE_BOSS_NIV_2		200
#define VIT_MISSILE_BOSS_NIV_3		150
#define VIT_MISSILE_BOSS_NIV_4		150
#define VIT_MISSILE_BOSS_NIV_5		100
/*** Vitesses de déplacement du bloc alien ***/
#define VIT_DEPL_BLOC_ALIEN_NIV_1	500
#define VIT_DEPL_BLOC_ALIEN_NIV_2	500
#define VIT_DEPL_BLOC_ALIEN_NIV_3	400
#define VIT_DEPL_BLOC_ALIEN_NIV_4	350
#define VIT_DEPL_BLOC_ALIEN_NIV_5	250
#define VIT_DEPL_BLOC_BOSS_NIV_1	150
#define VIT_DEPL_BLOC_BOSS_NIV_2	100
#define VIT_DEPL_BLOC_BOSS_NIV_3	80
#define VIT_DEPL_BLOC_BOSS_NIV_4	50
#define VIT_DEPL_BLOC_BOSS_NIV_5	30
/*** Nombre missiles aliens simultanés par niveau ***/
#define MISSILES_ALIENS_MAX_NIV_1	4
#define MISSILES_ALIENS_MAX_NIV_2	5
#define MISSILES_ALIENS_MAX_NIV_3	6
#define MISSILES_ALIENS_MAX_NIV_4	7
#define MISSILES_ALIENS_MAX_NIV_5	8
#define MISSILES_BOSS_MAX_NIV_1		3
#define MISSILES_BOSS_MAX_NIV_2		3
#define MISSILES_BOSS_MAX_NIV_3		5
#define MISSILES_BOSS_MAX_NIV_4		6
#define MISSILES_BOSS_MAX_NIV_5		8
/*** Nombre de points de vie des aliens ***/
#define PV_ALIENS_NIV_1		1
#define PV_ALIENS_NIV_2		1
#define PV_ALIENS_NIV_3		2
#define PV_ALIENS_NIV_4		4
#define PV_ALIENS_NIV_5		8
#define PV_BOSS_NIV_1		5
#define PV_BOSS_NIV_2		10
#define PV_BOSS_NIV_3		25
#define PV_BOSS_NIV_4		50
#define PV_BOSS_NIV_5		150
/*** Nombre de bunkers ***/
#define NB_BUNKER_NIV_1		8
#define NB_BUNKER_NIV_2		6
#define NB_BUNKER_NIV_3		3
#define NB_BUNKER_NIV_4		1
#define NB_BUNKER_NIV_5		0


/*** Alignement Aliens dans le bloc ***/
#define ALIGN_HORI	 	6
#define ALIGN_VERT 		3

#include <sextant/types.h>

class Config {
public:

	static int getLargeurBlocAlien(int niveau){
		switch(niveau){
		case 1 : return LARGEUR_BLOC_ALIEN_NIV_1; break;
		case 3 : return LARGEUR_BLOC_ALIEN_NIV_2; break;
		case 5 : return LARGEUR_BLOC_ALIEN_NIV_3; break;
		case 7 : return LARGEUR_BLOC_ALIEN_NIV_4; break;
		case 9 : return LARGEUR_BLOC_ALIEN_NIV_5; break;
		}
		return 1;
	}
	static int getHauteurBlocAlien(int niveau){
		switch(niveau){
		case 1 : return HAUTEUR_BLOC_ALIEN_NIV_1; break;
		case 3 : return HAUTEUR_BLOC_ALIEN_NIV_2; break;
		case 5 : return HAUTEUR_BLOC_ALIEN_NIV_3; break;
		case 7 : return HAUTEUR_BLOC_ALIEN_NIV_4; break;
		case 9 : return HAUTEUR_BLOC_ALIEN_NIV_5; break;
		}
		return 1;
	}
	static int getVitesseMissileAlien(int niveau){
		switch(niveau){
		case 1 : return VIT_MISSILE_ALIEN_NIV_1; break;
		case 3 : return VIT_MISSILE_ALIEN_NIV_2; break;
		case 5 : return VIT_MISSILE_ALIEN_NIV_3; break;
		case 7 : return VIT_MISSILE_ALIEN_NIV_4; break;
		case 9 : return VIT_MISSILE_ALIEN_NIV_5; break;
		case 2 : return VIT_MISSILE_BOSS_NIV_1; break;
		case 4 : return VIT_MISSILE_BOSS_NIV_2; break;
		case 6 : return VIT_MISSILE_BOSS_NIV_3; break;
		case 8 : return VIT_MISSILE_BOSS_NIV_4; break;
		case 10: return VIT_MISSILE_BOSS_NIV_5; break;
		}
		return 0;
	}
	static int getVitesseDeplacementBlocAlien(int niveau){
		switch(niveau){
		case 1 : return VIT_DEPL_BLOC_ALIEN_NIV_1; break;
		case 3 : return VIT_DEPL_BLOC_ALIEN_NIV_2; break;
		case 5 : return VIT_DEPL_BLOC_ALIEN_NIV_3; break;
		case 7 : return VIT_DEPL_BLOC_ALIEN_NIV_4; break;
		case 9 : return VIT_DEPL_BLOC_ALIEN_NIV_5; break;
		case 2 : return VIT_DEPL_BLOC_BOSS_NIV_1; break;
		case 4 : return VIT_DEPL_BLOC_BOSS_NIV_2; break;
		case 6 : return VIT_DEPL_BLOC_BOSS_NIV_3; break;
		case 8 : return VIT_DEPL_BLOC_BOSS_NIV_4; break;
		case 10: return VIT_DEPL_BLOC_BOSS_NIV_5; break;
		}
		return 0;
	}
	static int getNombreMissilesAliensMax(int niveau){
		switch(niveau){
		case 1 : return MISSILES_ALIENS_MAX_NIV_1; break;
		case 3 : return MISSILES_ALIENS_MAX_NIV_2; break;
		case 5 : return MISSILES_ALIENS_MAX_NIV_3; break;
		case 7 : return MISSILES_ALIENS_MAX_NIV_4; break;
		case 9 : return MISSILES_ALIENS_MAX_NIV_5; break;
		case 2 : return MISSILES_BOSS_MAX_NIV_1; break;
		case 4 : return MISSILES_BOSS_MAX_NIV_2; break;
		case 6 : return MISSILES_BOSS_MAX_NIV_3; break;
		case 8 : return MISSILES_BOSS_MAX_NIV_4; break;
		case 10: return MISSILES_BOSS_MAX_NIV_5; break;
		}
		return 0;
	}
	static int getPVAliens(int niveau){
		switch(niveau){
		case 1 : return PV_ALIENS_NIV_1; break;
		case 3 : return PV_ALIENS_NIV_2; break;
		case 5 : return PV_ALIENS_NIV_3; break;
		case 7 : return PV_ALIENS_NIV_4; break;
		case 9 : return PV_ALIENS_NIV_5; break;
		case 2 : return PV_BOSS_NIV_1; break;
		case 4 : return PV_BOSS_NIV_2; break;
		case 6 : return PV_BOSS_NIV_3; break;
		case 8 : return PV_BOSS_NIV_4; break;
		case 10: return PV_BOSS_NIV_5; break;
		}
		return 0;
	}
	static int getNbBunkers(int niveau){
		switch(niveau){
		case 1 : case 2 : return NB_BUNKER_NIV_1; break;
		case 3 : case 4 : return NB_BUNKER_NIV_2; break;
		case 5 : case 6 : return NB_BUNKER_NIV_3; break;
		case 7 : case 8 : return NB_BUNKER_NIV_4; break;
		case 9 : case 10: return NB_BUNKER_NIV_5; break;
		}
		return 0;
	}
	static Couleur getCouleurAlienRobot(int niveau){
		switch(niveau){
		case 1 : case 2 : return CYAN; break;
		case 3 : case 4 : return BLEU; break;
		case 5 : case 6 : return MARRON; break;
		case 7 : case 8 : return MAGENTA; break;
		case 9 : case 10: return ROUGE; break;
		}
		return NOIR;
	}
	static Couleur getCouleurAlienBat(int niveau){
		switch(niveau){
		case 1 : case 2 : return CYAN_LEGER; break;
		case 3 : case 4 : return BLEU_LEGER; break;
		case 5 : case 6 : return JAUNE; break;
		case 7 : case 8 : return MAGENTA_LEGER; break;
		case 9 : case 10: return ROUGE_LEGER; break;
		}
		return NOIR;
	}
	static Couleur getCouleurFondEspace(int niveau){
		return GRIS_SOMBRE;
		switch(niveau){
		case 1 : case 2 : return CYAN_LEGER; break;
		case 3 : case 4 : return BLEU_LEGER; break;
		case 5 : case 6 : return JAUNE; break;
		case 7 : case 8 : return MAGENTA_LEGER; break;
		case 9 : case 10: return ROUGE_LEGER; break;
		}
		return NOIR;
	}
};

#endif
