
#ifndef MAP_H_
#define MAP_H_

#include <drivers/EcranV.h>
#include <Applications/Warcraft/Unite.h>
#include <Applications/Warcraft/Batiment.h>
#include <Applications/Warcraft/Joueur.h>
#include <drivers/ClavierV.h>
#include <sextant/Activite/Threads.h>

class Map : public Threads{
public:
	EcranV *ecr;
	int tab[26][70];
	Joueur *joueurHumain;
	Joueur *joueurIA;
	ClavierV *clavier;
	char action;

	Map(EcranV *ecr,Joueur *joueurHumain,Joueur *joueurIA, ClavierV *clavier);

	void run();

	bool recupererOuAttaquer();
	void deplacer();
	void creerUnites();
	void afficher();
	void afficherMessage(const char *aAfficher);

	Position *scanner(Position *p,int nombreDeCaseMaxAutour,int typeRecherche);
	bool estDansLeTableau(int x,int y);
	int valeurAbsolue(int i);
	void effacerPosition(Position *p);
	void initialiserLesJoueurs();
	void initialiserSalementLaMap();
	void creation();

	static const int UNITE_IA = 0;
	static const int BATIMENT_IA = 1;
	static const int UNITE_HUMAIN = 2;
	static const int BATIMENT_HUMAIN = 3;
	static const int OR = 4;
	static const int BOIS = 5;
	static const int CASEVIDE = 5;
};

#endif /* MAP_H_ */
