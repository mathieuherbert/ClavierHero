/*
 * Joueur.cpp
 *
 *  Created on: 12 déc. 2011
 *      Author: Math
 */

#include<Applications/Warcraft/warcraftTD/JoueurTD.h>
#include<Applications/Warcraft/warcraftTD/MapTD.h>
#include<Applications/Warcraft/warcraftTD/MenuTD.h>
#include<Applications/Warcraft/warcraftTD/Tour.h>

JoueurTD::JoueurTD(EcranV *ecr,ClavierV *clavier):ecr(ecr),clavier(clavier),action(' '){
	gold=goldinit;
	life=lifeinit;
	fini=false;
	bfglaive = false;
	mapTD=new MapTD(ecr);
	menuTD = new MenuTD(ecr);
	caractere=' ';
}

//this->menuTD->getEcranV()->afficherCaractere(10, 10,JAUNE,NOIR,(char)caractere);

void JoueurTD::round(){
	this->caractere = action;
	action=' ';
	this->xCurseur=mouse.x;
	this->yCurseur=mouse.y;

	if(!bfglaive){
		if(caractere=='d'||caractere=='s'||caractere=='z'||caractere=='p'){
			gold-=mapTD->construireTour(caractere, xCurseur, yCurseur, gold);
		}
		else if(caractere=='u'&&mapTD->getInfo(xCurseur, yCurseur)&&mapTD->getInfo(xCurseur, yCurseur)->cout<=gold&&mapTD->getInfo(xCurseur, yCurseur)->niveau<6){
			gold-=mapTD->getInfo(xCurseur, yCurseur)->cout;
			mapTD->getInfo(xCurseur, yCurseur)->niveau++;
		}
		caractere = ' ';
		fini = false;
		life-=mapTD->gererLesEnnemi();
		gold+=mapTD->gererLesTours();
		menuTD->afficher(mapTD->getInfo(xCurseur, yCurseur), gold, life, mapTD->fabrique->getlvl());
		if(life<=0)
			bfglaive=true;
	}else{
		ecr->effacerEcranV(NOIR);
		ecr->afficherMot("\n\n\n\n\n\n\n\n                                    You lose !");
	}
}

void JoueurTD::majCurseur(int xCurseur, int yCurseur, char caractere){
	this->xCurseur=xCurseur;
	this->yCurseur=yCurseur;
	if(caractere!=' '){
		this->caractere = caractere;
		fini = true;
	}
}

void JoueurTD::run(){
	while(true){
		action = clavier->getChar();
	}
}
