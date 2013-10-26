/*
 * JeuPacman.cpp
 *
 *  Created on: 5 oct. 2012
 *      Author: killerider
 */

#include "JeuPacman.h"
#include "PlateauPacman.h"
#include "LecteurClavier.h"
#include "LecteurTouche.h"
#include "Affichage/Animation.h"
#include "Affichage/Accueil.h"

//

#include <sextant/interruptions/idt.h>
#include <sextant/interruptions/irq.h>
#include <sextant/interruptions/handler/handler_tic.h>
#include <sextant/interruptions/handler/handler_clavier.h>
#include <drivers/timer.h>
#include <sextant/Activite/Threads.h>

JeuPacman::JeuPacman(EcranV *e, ClavierV *c, PlateauPacman *plateau){
	ecran=e;
	clavier=c;
	lePlateau = plateau;
}

void JeuPacman::run(){
	//le jeu!

	ecran->effacerEcranV(NOIR);
	//Selection du niveau
	//ecran->afficherMot(HAUTEUR/2,LARGEUR/2-20,"Bienvenue sur Pacman, appuyez sur une touche pour commencer",BLANC);

	Animation::intro(ecran);

	Accueil::initAccueil(ecran);

	this->initLevel();
	//HELLO
	//Lancement du jeu
	this->launch();
	// a la fin du jeu, on propose au joueur de recommencer
	//ecran->afficherMot(23,LARGEUR/2-21,"Appuyez sur n pour relancer un nouveau jeu",BLANC);
	ecran->afficherMot(24,LARGEUR/2-21,"Appuyez sur q pour quitter le jeu",BLANC);


	PortSerie * p;
	char src;
	//tant que le joueur n'a pas entre la commande n, on ne fait rien.
	do{
		src=this->clavier->getChar();
		p->ecrireMot("CHAR ENTRE : |");
		p->ecrireCaractere(src);
	}while(src!='q');
	// on relance le jeu
	//this->start("Pacman");
}



void JeuPacman::launch(){
	// initialisation du booleen permettant de savoir si le joueur souhaite quitter la partie
	lePlateau->jouer=true;
	// declaration du caractere recueillant les touches saisies successivement par le joueur
	// c'est l'unique variable de communication avec le joueur
	char src;

	//on affiche le niveau du plateau
	this->ecran->effacerEcranV(NOIR);
	this->lePlateau= new PlateauPacman(this->ecran);
	this->lePlateau->updatePositionPersonnages();
	this->initPanel(&lePlateau->score,&lePlateau->vie);


	//this->ecran->afficherMot(0,0,"Pour acceder a l'aide appuyez sur a",BLANC);
	LecteurClavier *lecteurClavier = new LecteurClavier(clavier,lePlateau);

	//

	Timer timer;

	//idt_setup();
	//irq_setup();
	//Initialisation de la frequence de l'horloge
	timer.i8254_set_frequency(1000);

	//asm volatile("sti\n");//Autorise les interruptions
	//

	PortSerie *p;
	lecteurClavier->start("lecteurClavier");
	// la boucle du jeu en lui meme
	int sec = -1;
	int dsec = -1;

	while (lePlateau->jouer){
		//p->afficherChiffre(timer.getSecondes());
		switch(lePlateau->getPacman()->getDirectionNext()){
			case HAUT:
				if(!lePlateau->tab[lePlateau->getPacman()->getX()-1][lePlateau->getPacman()->getY()].estMur()){
					lePlateau->getPacman()->setDirectionNext(NULLE);
					lePlateau->getPacman()->setDirectionCurrent(HAUT);

				}
				break;
			case BAS:
				if(!lePlateau->tab[lePlateau->getPacman()->getX()+1][lePlateau->getPacman()->getY()].estMur()){
					lePlateau->getPacman()->setDirectionNext(NULLE);
					lePlateau->getPacman()->setDirectionCurrent(BAS);
				}
				break;
			case DROITE:
				if(!lePlateau->tab[lePlateau->getPacman()->getX()][lePlateau->getPacman()->getY()+1].estMur()){
					lePlateau->getPacman()->setDirectionNext(NULLE);
					lePlateau->getPacman()->setDirectionCurrent(DROITE);
				}
				break;
			case GAUCHE:
				if(!lePlateau->tab[lePlateau->getPacman()->getX()][lePlateau->getPacman()->getY()-1].estMur()){
					lePlateau->getPacman()->setDirectionNext(NULLE);
					lePlateau->getPacman()->setDirectionCurrent(GAUCHE);
				}
				break;
			case NULLE:
				//p->ecrireMot("NEXT A NULLE");
				break;
		}
		dsec = timer.getDsecondes();
		sec = timer.getSecondes();
		ecran->afficherMot(12,2,"Temps : ",ROUGE);
		ecran->afficherChiffre(12,((sec)/60 < 10 ? 10:9),(sec)/60);
		ecran->afficherCaractere(12,11,BLANC,NOIR,':');
		ecran->afficherChiffre(12,12,(sec%60));
		//p->afficherChiffre(dsec);
		while(timer.getDsecondes() <= dsec){

		}

		lePlateau->bougerPersonnages(dsec);

		switch(lePlateau->getPacman()->getDirectionCurrent()){
					case HAUT:
						if(!lePlateau->tab[lePlateau->getPacman()->getX()-1][lePlateau->getPacman()->getY()].estMur()){
							lePlateau->getPacman()->monterPersonnage();
							//p->ecrireMot("MOVE HAUT");
						}
						break;
					case BAS:
						if(!lePlateau->tab[lePlateau->getPacman()->getX()+1][lePlateau->getPacman()->getY()].estMur()){
							lePlateau->getPacman()->descendrePersonnage();
							//p->ecrireMot("MOVE BAS");
						}
						break;
					case DROITE:
						if(!lePlateau->tab[lePlateau->getPacman()->getX()][lePlateau->getPacman()->getY()+1].estMur()){
							lePlateau->getPacman()->tournerDroitePersonnage();
							//p->ecrireMot("MOVE DROITE");
						}
						break;
					case GAUCHE:
						if(!lePlateau->tab[lePlateau->getPacman()->getX()][lePlateau->getPacman()->getY()-1].estMur()){
							lePlateau->getPacman()->tournerGauchePersonnage();
							//p->ecrireMot("MOVE GAUCHE");
						}
						break;
					case NULLE:
						//p->ecrireMot("MOVE NULLE");
						break;
				}


		//irq_set_routine(IRQ_TIMER, ticTac);
		//irq_set_routine(IRQ_TIMER,ticTac);
			this->lePlateau->updatePositionPersonnages();
			this->updatePanel(&lePlateau->score,&lePlateau->vie);

			if(lePlateau->score == 228){
				Animation::victoire(ecran);
				this->lePlateau->partieGagnee = true;
				break;
			}

			if(this->lePlateau->aPerdu()) {


				ecran->effacerEcranV(NOIR);
				//Animation::victoire(ecran);
				Animation::Perdu(ecran);
				lePlateau->jouer = false;
				break;


			}



	}
	/*if(!lePlateau->jouer){
		ecran->effacerEcranV(NOIR);
		//afficher "vous avez quitté la partie"
		ecran->afficherMot(HAUTEUR/2,LARGEUR/2-13,"Vous avez quitte la partie!",BLANC);
	}*/
	// Le joueur a gagne la partie
	/*if(this->lePlateau->partieGagnee){
		ecran->effacerEcranV(NOIR);

	}*/
}

int JeuPacman::initLevel(){

	//le niveau a retourner qui sera compris entre 1 et 3
	int niveau;
	LecteurTouche * lecteur = new LecteurTouche(clavier,lePlateau);
	lePlateau->touche = false;
	lecteur->start("TOUCHE DEBUT");
	//saisie du joueur
	Timer timer;
	timer.i8254_set_frequency(1000);

	int sec = -1;
	PortSerie *p;
	p->afficherChiffre(sec);
	ecran->afficherMot(5,20,"Appuyez sur une touche pour commencer",BLANC);
	while(!lePlateau->touche){
		sec = timer.getDsecondes();
		ecran->afficherMot(5,20,"Appuyez sur une touche pour commencer",BLANC);
		while(timer.getDsecondes() <= sec){
		}
		for(int i = 20; i < LARGEUR-5;i++){
			ecran->afficherCaractere(5,i, NOIR, NOIR,' ');
		}
		sec = timer.getDsecondes();
		while(timer.getDsecondes() <= sec){
		}
	}
	//lecteur->Exit();
	//delete_thread(lecteur);

	return niveau;
}

void JeuPacman::updatePanel(int * score, int * vie){
	this->ecran->afficherMot(10,2,"Score : ",BLANC);
	this->ecran->afficherChiffre(10,13,*score);
	this->ecran->afficherMot(11,2,"Vies restantes : ",BLANC);
	this->ecran->afficherChiffre(11,24,*vie);
}


void JeuPacman::initPanel(int * score, int * vie){
		for(int i = 1; i < 28;i++){
			ecran->afficherCaractere(9,i, ROUGE, NOIR, '-');
			ecran->afficherCaractere(13,i, ROUGE, NOIR, '-');
		}
		this->ecran->afficherMot(10,2,"Score : ",BLANC);
		this->ecran->afficherChiffre(10,13,*score);
		this->ecran->afficherMot(11,2,"Vies restantes : ",BLANC);
		this->ecran->afficherChiffre(11,24,*vie);

		ecran->afficherCaractere(20,3, ROUGE, ROUGE, ' ');
		ecran->afficherCaractere(20,5, ROUGE, ROUGE, ' ');
		ecran->afficherCaractere(20,9, ROUGE, ROUGE, ' ');
		ecran->afficherCaractere(20,11, ROUGE, ROUGE, ' ');
		ecran->afficherCaractere(20,15, ROUGE, ROUGE, ' ');
		ecran->afficherCaractere(20,17, ROUGE, ROUGE, ' ');
		ecran->afficherCaractere(21,2, ROUGE, ROUGE, ' ');
		ecran->afficherCaractere(21,3, ROUGE, ROUGE, ' ');
		ecran->afficherCaractere(21,4, ROUGE, ROUGE, ' ');
		ecran->afficherCaractere(21,5, ROUGE, ROUGE, ' ');
		ecran->afficherCaractere(21,6, ROUGE, ROUGE, ' ');
		ecran->afficherCaractere(21,8, ROUGE, ROUGE, ' ');
		ecran->afficherCaractere(21,9, ROUGE, ROUGE, ' ');
		ecran->afficherCaractere(21,10, ROUGE, ROUGE, ' ');
		ecran->afficherCaractere(21,11, ROUGE, ROUGE, ' ');
		ecran->afficherCaractere(21,12, ROUGE, ROUGE, ' ');
		ecran->afficherCaractere(21,14, ROUGE, ROUGE, ' ');
		ecran->afficherCaractere(21,15, ROUGE, ROUGE, ' ');
		ecran->afficherCaractere(21,16, ROUGE, ROUGE, ' ');
		ecran->afficherCaractere(21,17, ROUGE, ROUGE, ' ');
		ecran->afficherCaractere(21,18, ROUGE, ROUGE, ' ');
		ecran->afficherCaractere(22,3, ROUGE, ROUGE, ' ');
		ecran->afficherCaractere(22,4, ROUGE, ROUGE, ' ');
		ecran->afficherCaractere(22,5, ROUGE, ROUGE, ' ');
		ecran->afficherCaractere(22,9, ROUGE, ROUGE, ' ');
		ecran->afficherCaractere(22,10, ROUGE, ROUGE, ' ');
		ecran->afficherCaractere(22,11, ROUGE, ROUGE, ' ');
		ecran->afficherCaractere(22,15, ROUGE, ROUGE, ' ');
		ecran->afficherCaractere(22,16, ROUGE, ROUGE, ' ');
		ecran->afficherCaractere(22,17, ROUGE, ROUGE, ' ');
		ecran->afficherCaractere(23,4, ROUGE, ROUGE, ' ');
		ecran->afficherCaractere(23,10, ROUGE, ROUGE, ' ');
		ecran->afficherCaractere(23,16, ROUGE, ROUGE, ' ');



		//ecran->afficherCaractere(8,8, JAUNE, JAUNE, ' ');
//		ecran->afficherCaractere(8,9, JAUNE, JAUNE, ' ');
//		ecran->afficherCaractere(8,10, JAUNE, JAUNE, ' ');
//		ecran->afficherCaractere(8,11, JAUNE, JAUNE, ' ');
//		ecran->afficherCaractere(8,12, JAUNE, JAUNE, ' ');
//		ecran->afficherCaractere(8,13, JAUNE, JAUNE, ' ');
//		ecran->afficherCaractere(8,14, JAUNE, JAUNE, ' ');
//		ecran->afficherCaractere(8,15, JAUNE, JAUNE, ' ');
//		ecran->afficherCaractere(8,16, JAUNE, JAUNE, ' ');
//		ecran->afficherCaractere(8,17, JAUNE, JAUNE, ' ');
//		ecran->afficherCaractere(8,18, JAUNE, JAUNE, ' ');
//		ecran->afficherCaractere(8,19, JAUNE, JAUNE, ' ');
//		ecran->afficherCaractere(8,20, JAUNE, JAUNE, ' ');
//		ecran->afficherCaractere(8,21, JAUNE, JAUNE, ' ');
//		ecran->afficherCaractere(8,22, JAUNE, JAUNE, ' ');


		//ecran->afficherCaractere(1,13+i, JAUNE, JAUNE, ' ');
		//ecran->afficherCaractere(1,13+i, JAUNE, JAUNE, ' ');
//		ecran->afficherCaractere(14,13, JAUNE, JAUNE, ' ');
//		ecran->afficherCaractere(14,9, JAUNE, JAUNE, ' ');
//		ecran->afficherCaractere(14,10, JAUNE, JAUNE, ' ');
//		ecran->afficherCaractere(14,11, JAUNE, JAUNE, ' ');
//		ecran->afficherCaractere(14,12, JAUNE, JAUNE, ' ');
//		ecran->afficherCaractere(14,13, JAUNE, JAUNE, ' ');
//		ecran->afficherCaractere(14,14, JAUNE, JAUNE, ' ');
//		ecran->afficherCaractere(14,15, JAUNE, JAUNE, ' ');
//		ecran->afficherCaractere(14,16, JAUNE, JAUNE, ' ');
//		ecran->afficherCaractere(14,17, JAUNE, JAUNE, ' ');
//		ecran->afficherCaractere(14,18, JAUNE, JAUNE, ' ');
//		ecran->afficherCaractere(14,19, JAUNE, JAUNE, ' ');
//		ecran->afficherCaractere(14,20, JAUNE, JAUNE, ' ');
//		ecran->afficherCaractere(14,21, JAUNE, JAUNE, ' ');
//		ecran->afficherCaractere(14,22, JAUNE, JAUNE, ' ');
}


