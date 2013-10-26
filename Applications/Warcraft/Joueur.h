
#ifndef JOUEUR_H_
#define JOUEUR_H_
#include <Applications/Warcraft/Unite.h>
#include <Applications/Warcraft/Batiment.h>
#include "Position.h"

class Joueur {
public:
	int population,
	nbBatiment,
	bois,
	gold;
	Unite *unites[30];
	Batiment *batiments[15];

	Joueur(bool humain);

	bool unitePerdDesPV(Position *positionDeLUnite,int pvPerdus);
	bool batimentPerdDesPV(int pvPerdus);
	void attaquer();
	void attaquerHumain();
	int nombrePaysanBois();
	int nombrePaysanOr();
	int nombreGuerriers();
	void creerPaysan(int materiauRecherche,Position *position,Position *objectif);
	void creerGuerrier(Position *position);
};



#endif /* JOUEUR_H_ */
