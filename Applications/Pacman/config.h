#ifndef CONFIG_H
#define CONFIG_H

/***
 * @file config.h
 * @brief Fichier de configuration du jeu. 
 * N.B. : Les zones doivent etre entourees par un espace vide.
 * Les zones doivent etre inclues les unes dans les autres
 ***/

/*** Type des cases ***/
#define VIDE 				0
#define MUR					10
#define PACGOMME			20
#define FRUIT	 			30
#define PACGOMMEBONUS 		40
#define PACMAN		 		50
#define BLINKY		 		60
#define CLYDE		 		70
#define INKY		 		80
#define PINKY		 		90
#define TELEPORTG			100
#define TELEPORTD			110
/*** Taille du jeu ***/
#define LARGEUR 	80
#define HAUTEUR 	25


enum Direction{
	HAUT,BAS,DROITE,GAUCHE,NULLE
};
#endif
