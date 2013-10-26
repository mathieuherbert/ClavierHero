#include "Warcraft.h"
#include "Menu.h"
#include "Map.h"
#include "Joueur.h"

Warcraft:: Warcraft(EcranV *ecran, ClavierV *clavierV,Souris *mouse):ecr(ecran),clavier(clavierV),jeux(false),horloge(0),mymouse(mouse){
}



//lance un td
void Warcraft::warTD(){
	ecr->effacerEcranV(NOIR);
	classic=false;
	jeux=true;
	TD=new JoueurTD(ecr,clavier);
	TD->start("TD");
}

//lance une partie classique
void Warcraft::warClassic(){
	classic=true;
	jeux=true;
	fini = false;
	joueurHumain = new Joueur(true);
	joueurIA = new Joueur(false);
	map = new Map(ecr,joueurHumain,joueurIA,clavier);
	menu = new Menu(ecr, clavier);
	map->start("War map");
}

//fait fonctionner une partie classique
void Warcraft::jouerClassic(){
//	if(true){
    if(!fini){
		fini = map->recupererOuAttaquer();
		map->deplacer();
		map->creerUnites();
		map->creation();
		map->afficher();
		actualiserLeMenu();
		menu->afficher();
	}
}


void Warcraft::jouerTD(){
	TD->round();
}
void Warcraft::jouer(){
	if(jeux){
		if(classic) jouerClassic();
		else jouerTD();
	}
}




void Warcraft::actualiserLeMenu(){
	menu->changerValeur(Menu::BOIS,joueurHumain->bois);
	menu->changerValeur(Menu::OR,joueurHumain->gold);
	menu->changerValeur(Menu::POPULATION,joueurHumain->nombreGuerriers()+joueurHumain->nombrePaysanBois()+joueurHumain->nombrePaysanOr());
	menu->changerValeur(Menu::PAYSAN,joueurHumain->nombrePaysanBois()+joueurHumain->nombrePaysanOr());
	menu->changerValeur(Menu::GUERRIER,joueurHumain->nombreGuerriers());
}

void Warcraft::wartic(){
	horloge++;
	if(!classic){
		if(!fini)
			TD->majCurseur(mymouse->x,mymouse->y,TD->action);
		else
			TD->majCurseur(mymouse->x,mymouse->y,' ');
		TD->action=' ';
	}
}
void Warcraft::run(){
	//demande à l'utilisateur de choisir le mode, si celui demande un mode non-disponible elle se réitère

	ecr->effacerEcranV(NOIR);
	ecr->afficherMot("Bienvenue dans Warcraft\n Deux modes de jeu sont disponible \n");
	ecr->afficherMot("a:Classique\nb:Tour de defense\n");
	ecr->afficherMot("Pour lancer le mode de votre choix taper la numero correspondant");

	char i=clavier->getChar();
	if(i=='a'){
		warClassic();
	}
	else if(i=='b'){
		warTD();
	}
	else{
		warClassic();
	}
	horloge=0;
	int previous=0;
	while(1){

		if (gettime()>(previous+frequence)) {
			previous=gettime();
			horloge=0;
			jouer();
		}

	}
}









