/*
 * Tour.cpp
 *
 *  Created on: 25 nov. 2011
 *      Author: Xan
 */

#include "Tour.h"


Tour::Tour(char caractere, int x, int y)
:x(x), y(y),niveau(1),caractere(caractere){
	switch(caractere){
	case 'd':
		vitesseAttaque = 3;
		portee = 4;
		cout = 50;
		logo = 8;
		break;
	case 's':
		vitesseAttaque = 3;
		portee = 3;
		cout = 75;
		logo = 42;
		break;
	case 'z':
		vitesseAttaque = 6;
		portee = 2;
		cout = 150;
		logo = 10;
		break;
	case 'p':
		vitesseAttaque = 6;
		portee = 3;
		cout = 100;
		logo = 15;
		break;
	}

}


//Return :true lorsque la tour a fini son cycle et est prete à tirer.
bool Tour::round() {
	if(horloge++>=vitesseAttaque){
		horloge-=vitesseAttaque;
		return true;
	}
	else return false;
}

int Tour::getX(){
	return this->x;
}

int Tour::getY(){
	return this->y;
}

int Tour::getVitesseAttaque(){
	return this->vitesseAttaque;
}

int Tour::getPortee(){
	return this->portee;
}

int Tour::getCout(){
	return this->cout;
}

//Return: l'attaque de la tour, cette méthode n'est appelée que si la tour a des ennemis à portée.
Attaque *Tour::attaquer(){

	int ralentissement=0;
	int paralysie=0;
	int zone=0;
	int degats=4*niveau;
	switch(caractere){
	case 's':
		ralentissement=niveau;
		degats=0;
		break;
	case 'z':
		zone=1;
		degats = 2*niveau;
		break;
	case 'p':
		paralysie=niveau;
		degats=0;
		break;
	}

	this->horloge = vitesseAttaque;
	Attaque *attaque = new Attaque(degats,ralentissement, paralysie, zone);
	return attaque;

}

