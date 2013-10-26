#ifndef WARCRAFT_H_
#define WARCRAFT_H_
#include <drivers/EcranV.h>
#include <drivers/ClavierV.h>
#include <drivers/Souris.h>
#include <Applications/Warcraft/Map.h>
#include <Applications/Warcraft/Menu.h>
#include <Applications/Warcraft/Joueur.h>
#include <Applications/Warcraft/WarcraftTD/JoueurTD.h>
#include <sextant/Activite/Threads.h>
#include <drivers/Souris.h>
#include <sextant/interruptions/handler/handler_tic.h>



class Warcraft :public Threads{
private:
private:
	//true quand une partie est  lancé
	bool jeux;

	//true quand la partie lancé est une classique et false quand c'est un td
	bool classic;
public:
	EcranV *ecr;
	ClavierV *clavier;
	Map *map;
	Menu *menu;
	Souris *mymouse;
	Joueur *joueurHumain;
	Joueur *joueurIA;
	JoueurTD *TD;
	int const static frequence=500;
	int horloge;
	bool fini;
	void jouer();
	void actualiserLeMenu();
	Warcraft(EcranV *ecran, ClavierV *clavierV,Souris *mouse);
	void warClassic();
	void warTD();
	void jouerTD();
	void jouerClassic();
	void wartic();
	void run();


};

#endif /* WARCRAFT_H_ */
