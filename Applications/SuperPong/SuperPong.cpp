#include "SuperPong.h"

SuperPong::SuperPong(EcranV* e, ClavierV* c){
	ecran=e;
	clavier=c;
}

void SuperPong::init() {
	//ecran->effacerEcran(NOIR);
	laGrille.init(ecran);
	laGrille.affiche();
}

void SuperPong::init(EcranV* e,ClavierV* c) {
	ecran=e;
	clavier=c;
//	e->effacerEcran(NOIR);
	laGrille.init(e);
	laGrille.affiche();
}


void SuperPong::start() {
	char buffer[256];
	int  i;
	bool jouer=true;
	char *src;
	Balle balle(&laGrille);
	//Modification de la routine d'interruption du keyboard
//	irq_set_routine(IRQ_KEYBOARD, keyboard_handler_jeu);

	//Initialisation de la grille
	init();
	balle.start();
	while (jouer){
		char c=clavier->getChar();

//		if(clavier->testChar()) {

//			src=clavier->getString();

//			for(i=0;i<256-1 && src[i]!='\0';i++)
//				buffer[i]=src[i];
//			buffer[i]='\0';
//
//			for(i=0;buffer[i]!='\0';i++)
				switch(c){
				case 's' :
					laGrille.monterRaquette(GAUCHE);
					break;
				case 'x' :
					laGrille.descendreRaquette(GAUCHE);
					break;
				case 'j' :
					laGrille.monterRaquette(DROITE);
					break;
				case 'n' :
					laGrille.descendreRaquette(DROITE);
					break;
				case 'q' :
					jouer=false;
				}
//		}
	}
//	ecran->effacerEcran(NOIR);
}
