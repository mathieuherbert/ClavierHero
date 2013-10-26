/*
 * PlateauPacman.cpp
 *
 *  Created on: 5 oct. 2012
 *      Author: killerider
 */

#include "PlateauPacman.h"
#include "niveauPacman.h"

PlateauPacman::PlateauPacman(EcranV *e) {
	//initialisation du plateau
	this->ecran=e;
	score = 0;
	vie = 3;
	NiveauPacman::generer(this);
	this->partieGagnee=false;
	initPlateau();
	initPersonnages();
	this->updatePositionPersonnages();
}




CasePacman* PlateauPacman::getCase(int x,int y) {
	return &tab[x][y];
}

void PlateauPacman::initPlateau(){

	for (int x=0 ; x<HAUTEUR ; x++) {
		for (int y=0 ; y<LARGEUR ; y++) {
			tab[x][y].paint();
		}
	}

	//Panel
	ecran->afficherMot(2,2,"Touches :",GRIS_SOMBRE);
	ecran->afficherMot(3,9,"q : Gauche",GRIS_SOMBRE);
	ecran->afficherMot(4,9,"d : Droite",GRIS_SOMBRE);
	ecran->afficherMot(5,9,"s : Bas",GRIS_SOMBRE);
	ecran->afficherMot(6,9,"z : Haut",GRIS_SOMBRE);
	//LIGNE DU HAUT
		ecran->afficherCaractere(0,0, BLANC, NOIR, '#');
		ecran->afficherCaractere(0,1, BLANC, NOIR, '#');
		ecran->afficherCaractere(0,2, BLANC, NOIR, '#');
		ecran->afficherCaractere(0,3, BLANC, NOIR, '#');
		ecran->afficherCaractere(0,4, BLANC, NOIR, '#');
		ecran->afficherCaractere(0,5, BLANC, NOIR, '#');
		ecran->afficherCaractere(0,6, BLANC, NOIR, '#');
		ecran->afficherCaractere(0,7, BLANC, NOIR, '#');
		ecran->afficherCaractere(0,8, BLANC, NOIR, '#');
		ecran->afficherCaractere(0,9, BLANC, NOIR, '#');
		ecran->afficherCaractere(0,10, BLANC, NOIR, '#');
		ecran->afficherCaractere(0,11, BLANC, NOIR, '#');
		ecran->afficherCaractere(0,12, BLANC, NOIR, '#');
		ecran->afficherCaractere(0,13, BLANC, NOIR, '#');
		ecran->afficherCaractere(0,14, BLANC, NOIR, '#');
		ecran->afficherCaractere(0,15, BLANC, NOIR, '#');
		ecran->afficherCaractere(0,16, BLANC, NOIR, '#');
		ecran->afficherCaractere(0,17, BLANC, NOIR, '#');
		ecran->afficherCaractere(0,18, BLANC, NOIR, '#');
		ecran->afficherCaractere(0,19, BLANC, NOIR, '#');
		ecran->afficherCaractere(0,20, BLANC, NOIR, '#');
		ecran->afficherCaractere(0,21, BLANC, NOIR, '#');
		ecran->afficherCaractere(0,22, BLANC, NOIR, '#');
		ecran->afficherCaractere(0,23, BLANC, NOIR, '#');
		ecran->afficherCaractere(0,24, BLANC, NOIR, '#');
		ecran->afficherCaractere(0,25, BLANC, NOIR, '#');
		ecran->afficherCaractere(0,26, BLANC, NOIR, '#');
		ecran->afficherCaractere(0,27, BLANC, NOIR, '#');
		ecran->afficherCaractere(0,28, BLANC, NOIR, '#');
		ecran->afficherCaractere(0,29, BLANC, NOIR, '#');
		ecran->afficherCaractere(0,30, BLANC, NOIR, '#');
		ecran->afficherCaractere(0,31, BLANC, NOIR, '#');
		ecran->afficherCaractere(0,32, BLANC, NOIR, '#');
		ecran->afficherCaractere(0,33, BLANC, NOIR, '#');
		ecran->afficherCaractere(0,34, BLANC, NOIR, '#');
		ecran->afficherCaractere(0,35, BLANC, NOIR, '#');
		ecran->afficherCaractere(0,36, BLANC, NOIR, '#');
		ecran->afficherCaractere(0,37, BLANC, NOIR, '#');
		ecran->afficherCaractere(0,38, BLANC, NOIR, '#');
		ecran->afficherCaractere(0,39, BLANC, NOIR, '#');
		ecran->afficherCaractere(0,40, BLANC, NOIR, '#');
		ecran->afficherCaractere(0,41, BLANC, NOIR, '#');
		ecran->afficherCaractere(0,42, BLANC, NOIR, '#');
		ecran->afficherCaractere(0,43, BLANC, NOIR, '#');
		ecran->afficherCaractere(0,44, BLANC, NOIR, '#');
		ecran->afficherCaractere(0,45, BLANC, NOIR, '#');
		ecran->afficherCaractere(0,46, BLANC, NOIR, '#');
		ecran->afficherCaractere(0,47, BLANC, NOIR, '#');
		ecran->afficherCaractere(0,48, BLANC, NOIR, '#');
		ecran->afficherCaractere(0,49, BLANC, NOIR, '#');
		ecran->afficherCaractere(0,50, BLANC, NOIR, '#');
		ecran->afficherCaractere(0,51, BLANC, NOIR, '#');
		ecran->afficherCaractere(0,52, BLANC, NOIR, '#');
		ecran->afficherCaractere(0,53, BLANC, NOIR, '#');
		ecran->afficherCaractere(0,54, BLANC, NOIR, '#');
		ecran->afficherCaractere(0,55, BLANC, NOIR, '#');
		ecran->afficherCaractere(0,56, BLANC, NOIR, '#');
		ecran->afficherCaractere(0,57, BLANC, NOIR, '#');
		ecran->afficherCaractere(0,58, BLANC, NOIR, '#');
		ecran->afficherCaractere(0,59, BLANC, NOIR, '#');
		ecran->afficherCaractere(0,60, BLANC, NOIR, '#');
		ecran->afficherCaractere(0,61, BLANC, NOIR, '#');
		ecran->afficherCaractere(0,62, BLANC, NOIR, '#');
		ecran->afficherCaractere(0,63, BLANC, NOIR, '#');
		ecran->afficherCaractere(0,64, BLANC, NOIR, '#');
		ecran->afficherCaractere(0,65, BLANC, NOIR, '#');
		ecran->afficherCaractere(0,66, BLANC, NOIR, '#');
		ecran->afficherCaractere(0,67, BLANC, NOIR, '#');
		ecran->afficherCaractere(0,68, BLANC, NOIR, '#');
		ecran->afficherCaractere(0,69, BLANC, NOIR, '#');
		ecran->afficherCaractere(0,70, BLANC, NOIR, '#');
		ecran->afficherCaractere(0,71, BLANC, NOIR, '#');
		ecran->afficherCaractere(0,72, BLANC, NOIR, '#');
		ecran->afficherCaractere(0,73, BLANC, NOIR, '#');
		ecran->afficherCaractere(0,74, BLANC, NOIR, '#');
		ecran->afficherCaractere(0,75, BLANC, NOIR, '#');
		ecran->afficherCaractere(0,76, BLANC, NOIR, '#');
		ecran->afficherCaractere(0,77, BLANC, NOIR, '#');
		ecran->afficherCaractere(0,78, BLANC, NOIR, '#');
		ecran->afficherCaractere(0,79, BLANC, NOIR, '#');

		//GAUCHE
		ecran->afficherCaractere(1,0, BLANC, NOIR, '|');
		ecran->afficherCaractere(2,0, BLANC, NOIR, '|');
		ecran->afficherCaractere(3,0, BLANC, NOIR, '|');
		ecran->afficherCaractere(4,0, BLANC, NOIR, '|');
		ecran->afficherCaractere(5,0, BLANC, NOIR, '|');
		ecran->afficherCaractere(6,0, BLANC, NOIR, '|');
		ecran->afficherCaractere(7,0, BLANC, NOIR, '|');
		ecran->afficherCaractere(8,0, BLANC, NOIR, '|');
		ecran->afficherCaractere(9,0, BLANC, NOIR, '|');
		ecran->afficherCaractere(10,0, BLANC, NOIR, '|');
		ecran->afficherCaractere(11,0, BLANC, NOIR, '|');
		ecran->afficherCaractere(12,0, BLANC, NOIR, '|');
		ecran->afficherCaractere(13,0, BLANC, NOIR, '|');
		ecran->afficherCaractere(14,0, BLANC, NOIR, '|');
		ecran->afficherCaractere(15,0, BLANC, NOIR, '|');
		ecran->afficherCaractere(16,0, BLANC, NOIR, '|');
		ecran->afficherCaractere(17,0, BLANC, NOIR, '|');
		ecran->afficherCaractere(18,0, BLANC, NOIR, '|');
		ecran->afficherCaractere(19,0, BLANC, NOIR, '|');
		ecran->afficherCaractere(20,0, BLANC, NOIR, '|');
		ecran->afficherCaractere(21,0, BLANC, NOIR, '|');
		ecran->afficherCaractere(22,0, BLANC, NOIR, '|');
		ecran->afficherCaractere(23,0, BLANC, NOIR, '|');

		//BAS
		ecran->afficherCaractere(24,0, BLANC, NOIR, '#');
		ecran->afficherCaractere(24,1, BLANC, NOIR, '#');
		ecran->afficherCaractere(24,2, BLANC, NOIR, '#');
		ecran->afficherCaractere(24,3, BLANC, NOIR, '#');
		ecran->afficherCaractere(24,4, BLANC, NOIR, '#');
		ecran->afficherCaractere(24,5, BLANC, NOIR, '#');
		ecran->afficherCaractere(24,6, BLANC, NOIR, '#');
		ecran->afficherCaractere(24,7, BLANC, NOIR, '#');
		ecran->afficherCaractere(24,8, BLANC, NOIR, '#');
		ecran->afficherCaractere(24,9, BLANC, NOIR, '#');
		ecran->afficherCaractere(24,10, BLANC, NOIR, '#');
		ecran->afficherCaractere(24,11, BLANC, NOIR, '#');
		ecran->afficherCaractere(24,12, BLANC, NOIR, '#');
		ecran->afficherCaractere(24,13, BLANC, NOIR, '#');
		ecran->afficherCaractere(24,14, BLANC, NOIR, '#');
		ecran->afficherCaractere(24,15, BLANC, NOIR, '#');
		ecran->afficherCaractere(24,16, BLANC, NOIR, '#');
		ecran->afficherCaractere(24,17, BLANC, NOIR, '#');
		ecran->afficherCaractere(24,18, BLANC, NOIR, '#');
		ecran->afficherCaractere(24,19, BLANC, NOIR, '#');
		ecran->afficherCaractere(24,20, BLANC, NOIR, '#');
		ecran->afficherCaractere(24,21, BLANC, NOIR, '#');
		ecran->afficherCaractere(24,22, BLANC, NOIR, '#');
		ecran->afficherCaractere(24,23, BLANC, NOIR, '#');
		ecran->afficherCaractere(24,24, BLANC, NOIR, '#');
		ecran->afficherCaractere(24,25, BLANC, NOIR, '#');
		ecran->afficherCaractere(24,26, BLANC, NOIR, '#');
		ecran->afficherCaractere(24,27, BLANC, NOIR, '#');
		ecran->afficherCaractere(24,28, BLANC, NOIR, '#');
		ecran->afficherCaractere(24,29, BLANC, NOIR, '#');
		ecran->afficherCaractere(24,30, BLANC, NOIR, '#');
		ecran->afficherCaractere(24,31, BLANC, NOIR, '#');
		ecran->afficherCaractere(24,32, BLANC, NOIR, '#');
		ecran->afficherCaractere(24,33, BLANC, NOIR, '#');
		ecran->afficherCaractere(24,34, BLANC, NOIR, '#');
		ecran->afficherCaractere(24,35, BLANC, NOIR, '#');
		ecran->afficherCaractere(24,36, BLANC, NOIR, '#');
		ecran->afficherCaractere(24,37, BLANC, NOIR, '#');
		ecran->afficherCaractere(24,38, BLANC, NOIR, '#');
		ecran->afficherCaractere(24,39, BLANC, NOIR, '#');
		ecran->afficherCaractere(24,40, BLANC, NOIR, '#');
		ecran->afficherCaractere(24,41, BLANC, NOIR, '#');
		ecran->afficherCaractere(24,42, BLANC, NOIR, '#');
		ecran->afficherCaractere(24,43, BLANC, NOIR, '#');
		ecran->afficherCaractere(24,44, BLANC, NOIR, '#');
		ecran->afficherCaractere(24,45, BLANC, NOIR, '#');
		ecran->afficherCaractere(24,46, BLANC, NOIR, '#');
		ecran->afficherCaractere(24,47, BLANC, NOIR, '#');
		ecran->afficherCaractere(24,48, BLANC, NOIR, '#');
		ecran->afficherCaractere(24,49, BLANC, NOIR, '#');
		ecran->afficherCaractere(24,50, BLANC, NOIR, '#');
		ecran->afficherCaractere(24,51, BLANC, NOIR, '#');
		ecran->afficherCaractere(24,52, BLANC, NOIR, '#');
		ecran->afficherCaractere(24,53, BLANC, NOIR, '#');
		ecran->afficherCaractere(24,54, BLANC, NOIR, '#');
		ecran->afficherCaractere(24,55, BLANC, NOIR, '#');
		ecran->afficherCaractere(24,56, BLANC, NOIR, '#');
		ecran->afficherCaractere(24,57, BLANC, NOIR, '#');
		ecran->afficherCaractere(24,58, BLANC, NOIR, '#');
		ecran->afficherCaractere(24,59, BLANC, NOIR, '#');
		ecran->afficherCaractere(24,60, BLANC, NOIR, '#');
		ecran->afficherCaractere(24,61, BLANC, NOIR, '#');
		ecran->afficherCaractere(24,62, BLANC, NOIR, '#');
		ecran->afficherCaractere(24,63, BLANC, NOIR, '#');
		ecran->afficherCaractere(24,64, BLANC, NOIR, '#');
		ecran->afficherCaractere(24,65, BLANC, NOIR, '#');
		ecran->afficherCaractere(24,66, BLANC, NOIR, '#');
		ecran->afficherCaractere(24,67, BLANC, NOIR, '#');
		ecran->afficherCaractere(24,68, BLANC, NOIR, '#');
		ecran->afficherCaractere(24,69, BLANC, NOIR, '#');
		ecran->afficherCaractere(24,70, BLANC, NOIR, '#');
		ecran->afficherCaractere(24,71, BLANC, NOIR, '#');
		ecran->afficherCaractere(24,72, BLANC, NOIR, '#');
		ecran->afficherCaractere(24,73, BLANC, NOIR, '#');
		ecran->afficherCaractere(24,74, BLANC, NOIR, '#');
		ecran->afficherCaractere(24,75, BLANC, NOIR, '#');
		ecran->afficherCaractere(24,76, BLANC, NOIR, '#');
		ecran->afficherCaractere(24,77, BLANC, NOIR, '#');
		ecran->afficherCaractere(24,78, BLANC, NOIR, '#');
		ecran->afficherCaractere(24,79, BLANC, NOIR, '#');

		//DROITE
		ecran->afficherCaractere(1,79, BLANC, NOIR, '|');
		ecran->afficherCaractere(2,79, BLANC, NOIR, '|');
		ecran->afficherCaractere(3,79, BLANC, NOIR, '|');
		ecran->afficherCaractere(4,79, BLANC, NOIR, '|');
		ecran->afficherCaractere(5,79, BLANC, NOIR, '|');
		ecran->afficherCaractere(6,79, BLANC, NOIR, '|');
		ecran->afficherCaractere(7,79, BLANC, NOIR, '|');
		ecran->afficherCaractere(8,79, BLANC, NOIR, '|');
		ecran->afficherCaractere(9,79, BLANC, NOIR, '|');
		ecran->afficherCaractere(10,79, BLANC, NOIR, '|');
		ecran->afficherCaractere(11,79, BLANC, NOIR, '|');
		ecran->afficherCaractere(12,79, BLANC, NOIR, '|');
		ecran->afficherCaractere(13,79, BLANC, NOIR, '|');
		ecran->afficherCaractere(14,79, BLANC, NOIR, '|');
		ecran->afficherCaractere(15,79, BLANC, NOIR, '|');
		ecran->afficherCaractere(16,79, BLANC, NOIR, '|');
		ecran->afficherCaractere(17,79, BLANC, NOIR, '|');
		ecran->afficherCaractere(18,79, BLANC, NOIR, '|');
		ecran->afficherCaractere(19,79, BLANC, NOIR, '|');
		ecran->afficherCaractere(20,79, BLANC, NOIR, '|');
		ecran->afficherCaractere(21,79, BLANC, NOIR, '|');
		ecran->afficherCaractere(22,79, BLANC, NOIR, '|');
		ecran->afficherCaractere(23,79, BLANC, NOIR, '|');

		ecran->afficherMot(0,32,"==> Pacman <===",JAUNE);
}

void PlateauPacman::updatePositionPersonnages(){

	PortSerie *p;
	//for (int x=0 ; x<HAUTEUR ; x++) {
	//	for (int y=0 ; y<LARGEUR ; y++) {
		//	tab[pacman.getOldX()][pacman.getOldY()].paint();
	//	}
	//}

			if(pacman.hasMoved()) {
				updatePositionPersonnage(&pacman);
				pacman.setOldToCurrent();
				p->ecrireMot("Affichage de Pacman");
				p->afficherChiffre(pacman.getX());
				p->ecrireMot("|");
				p->afficherChiffre(pacman.getY());
			}

			if(blinky.hasMoved()) {
				updatePositionPersonnage(&blinky);
				blinky.setOldToCurrent();
				p->ecrireMot("Affichage de Blinky");
				p->afficherChiffre(blinky.getX());
				p->ecrireMot("|");
				p->afficherChiffre(blinky.getY());
			}

			if(clyde.hasMoved()) {
				updatePositionPersonnage(&clyde);
				clyde.setOldToCurrent();
				p->ecrireMot("Affichage de Clyde");
				p->afficherChiffre(clyde.getX());
				p->ecrireMot("|");
				p->afficherChiffre(clyde.getY());
			}
			if(pinky.hasMoved()) {
				updatePositionPersonnage(&pinky);
				pinky.setOldToCurrent();
				p->ecrireMot("Affichage de Pinky");
				p->afficherChiffre(pinky.getX());
				p->ecrireMot("|");
				p->afficherChiffre(pinky.getY());
			}
			if(inky.hasMoved()) {
				updatePositionPersonnage(&inky);
				inky.setOldToCurrent();
				p->ecrireMot("Affichage de Inky");
				p->afficherChiffre(inky.getX());
				p->ecrireMot("|");
				p->afficherChiffre(inky.getY());
			}
		//}
	//}
}

void PlateauPacman::initPersonnages() {

	blinky.setX(11);
	blinky.setY(39);
	blinky.setCaractere('B');
	blinky.setColor(ROUGE);
	blinky.setDelaiDebut(100);
	blinky.setFrequenceDijkstra(5);

	clyde.setX(12);
	clyde.setY(39);
	clyde.setCaractere('C');
	clyde.setColor(MARRON);
	clyde.setDelaiDebut(100);
	clyde.setFrequenceDijkstra(2);

	inky.setX(12);
	inky.setY(40);
	inky.setCaractere('I');
	inky.setColor(BLEU);
	inky.setDelaiDebut(80);
	inky.setFrequenceDijkstra(4);

	pinky.setX(12);
	pinky.setY(40);
	pinky.setCaractere('P');
	pinky.setColor(VERT);
	pinky.setDelaiDebut(50);
	pinky.setFrequenceDijkstra(10);

	pacman.setX(9);
	pacman.setY(39);
	pacman.setCaractere('@');
	pacman.setColor(JAUNE);

	afficherPersoEcran(&pacman);
	afficherPersoEcran(&blinky);
	afficherPersoEcran(&clyde);
	afficherPersoEcran(&pinky);
	afficherPersoEcran(&inky);

}

void PlateauPacman::afficherPersoEcran(PersonnagePacman * perso){
	ecran->afficherCaractere(perso->getX(), perso->getY(), perso->getColor(), NOIR, perso->getCaractere());
}

void PlateauPacman::updatePositionPersonnage(PersonnagePacman * perso){
	if (perso->getCaractere() == '@'){
		if(tab[perso->getX()][perso->getY()].getEtat()==TELEPORTG){
			perso->setX(11);
			perso->setY(51);
			perso->setOldX(11);
			perso->setOldY(50);
			perso->setDirectionCurrent(GAUCHE);
			perso->setDirectionNext(GAUCHE);
			tab[11][29].setCaseVide();
			tab[11][29].paint();
		}
		else if(tab[perso->getX()][perso->getY()].getEtat()==TELEPORTD){
			perso->setX(11);
			perso->setY(28);
			perso->setOldX(11);
			perso->setOldY(29);
			perso->setDirectionCurrent(DROITE);
			perso->setDirectionNext(DROITE);
			tab[11][50].setCaseVide();
			tab[11][50].paint();
		}
		else if(tab[perso->getX()][perso->getY()].getEtat()==FRUIT){
			tab[perso->getX()][perso->getY()].setCaseVide();
			score++;
		}
	}
	tab[perso->getOldX()][perso->getOldY()].paint();
	afficherPersoEcran(perso);

}

Pacman  * PlateauPacman::getPacman(){
	return &pacman;
}

void PlateauPacman::bougerPersonnages(int sec) {
	//blinky.bouger(&pacman);

	this->bougerPersonnage(&blinky, sec);
	this->bougerPersonnage(&pinky, sec);
	this->bougerPersonnage(&clyde, sec);
	this->bougerPersonnage(&inky, sec);
}

void PlateauPacman::bougerPersonnage(PersonnagePacman * perso, int sec) {

	if(perso->getX() == pacman.getX() && perso->getY() == pacman.getY())
		return;

	// Le perso peut commencer à bouger
	if(sec > perso->getDelaiDebut()) {
		if(sec%perso->getFrequenceDijkstra() == 0) {

			D.initialize(perso->getX()-1, perso->getY()-28, pacman.getX()-1, pacman.getY()-28);
			D.calculateDistance();

			int next = D.nextPosition(pacman.getX()-1, pacman.getY()-28);

			if(next == -1)
				return;

			int nextX = (int)(next/1000)+1;
			int nextY = next%1000+28;


			if(nextX < perso->getX()) {
				perso->monterPersonnage();
			}
			else if(nextX > perso->getX()) {
				perso->descendrePersonnage();
			}
			else if(nextY > perso->getY()) {
				perso->tournerDroitePersonnage();
			}
			else if(nextY < perso->getY()) {
				perso->tournerGauchePersonnage();
			}
		}
	}


}

bool PlateauPacman::aPerdu()
{

	if(pacman.getX() == blinky.getX() && pacman.getY() == blinky.getY()) {
		return true;
	}
	if(pacman.getX() == inky.getX() && pacman.getY() == inky.getY()) {
		return true;
	}
	if(pacman.getX() == clyde.getX() && pacman.getY() == clyde.getY()) {
		return true;
	}
	if(pacman.getX() == pinky.getX() && pacman.getY() == pinky.getY()) {
		return true;
	}

	return false;

}


