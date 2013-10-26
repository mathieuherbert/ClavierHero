/*
 * Blinky.cpp
 *
 *  Created on: 21 oct. 2012
 *      Author: Administrateur
 */

#include "Blinky.h"

Blinky::Blinky() : PersonnagePacman("Blinky") {

}

/*
void Blinky::bouger(Pacman *pacman) {

	PortSerie p;


	if(this->getX() == pacman->getX() && this->getY() == pacman->getY())
		return;

	D.initialize(this->getX()-1, this->getY()-28);
	D.calculateDistance();

	p.ecrireMot("---------@");
	p.afficherChiffre(this->getX()-1);
	p.ecrireMot("|");
	p.afficherChiffre(this->getY()-28);
	p.ecrireMot("@---------");

	//D.printPath(pacman->getX()-1, pacman->getY()-23);

	int next = D.nextPosition(pacman->getX()-1, pacman->getY()-28);

	if(next == -1)
		return;


	int nextX = (int)(next/1000)+1;
	int nextY = next%1000+28;


	p.ecrireMot("---------");
	p.afficherChiffre(next+1028);
	p.ecrireMot("|");
	p.afficherChiffre(this->getX());
	p.ecrireMot("|");
	p.afficherChiffre(this->getY());
	p.ecrireMot("---------");

	if(nextX < this->getX()) {
		this->monterPersonnage();
	}
	else if(nextX > this->getX()) {
		this->descendrePersonnage();
	}
	else if(nextY > this->getY()) {
		this->tournerDroitePersonnage();
	}
	else if(nextY < this->getY()) {
		this->tournerGauchePersonnage();
	}

}*/
