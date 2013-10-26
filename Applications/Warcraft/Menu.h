#ifndef MENU_H_
#define MENU_H_


#include <drivers/EcranV.h>
#include <drivers/ClavierV.h>
#include <drivers/Souris.h>
#include <sextant/types.h>

class Menu {
private:
	EcranV *ecr;
	ClavierV *clavier;
	int tab[25][10];
public:
	Menu(EcranV *ecr, ClavierV *clavier);
	EcranV *getEcranV();
	void afficher();
	void changerValeur(int grandeur,int valeur);
	void initialiserSalementLeMenu();

	static const int BOIS = 0;
	static const int OR = 1;
	static const int POPULATION = 2;
	static const int PAYSAN = 3;
	static const int GUERRIER = 4;

};


#endif /* MENU_H_ */
