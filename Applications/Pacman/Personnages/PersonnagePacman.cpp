/*
 * PersonnagePacman.cpp
 *
 *  Created on: 21 oct. 2012
 *      Author: Administrateur
 */

#include "PersonnagePacman.h"

PersonnagePacman::PersonnagePacman() : old_x(0),old_y(0),x(0), y(0), name("default"), caractere('!'),color(NOIR),direction_current(NULLE),direction_next(NULLE){

}

PersonnagePacman::PersonnagePacman(const char * pname) : old_x(0),old_y(0),x(0), y(0), name(pname), caractere('!'),color(NOIR),direction_current(NULLE),direction_next(NULLE){

}

int PersonnagePacman::getX(){
	return this->x;
}

int PersonnagePacman::getY(){
	return this->y;
}

int PersonnagePacman::getOldX(){
	return this->old_x;
}

int PersonnagePacman::getOldY(){
	return this->old_y;
}

const char * PersonnagePacman::getName(){
	return this->name;
}

char  PersonnagePacman::getCaractere(){
	return this->caractere;
}

Couleur PersonnagePacman::getColor(){
	return this->color;
}

int PersonnagePacman::hasMoved(){
	if(this->old_x == this->x && this->old_y == this->y){
		//n'a pas bougé
		return 0;
	}else{
		//a bougé
		return 1;
	}
}


void PersonnagePacman::setX(int px){
	if(px){
		this->old_x = this->x;
		this->x = px;
	}
}
void PersonnagePacman::setY(int py){
	if(py){
		this->old_y = this->y;
		this->y = py;
	}
}


void PersonnagePacman::setOldX(int px){
	if(px){
		this->old_x = px;
	}
}
void PersonnagePacman::setOldY(int py){
	if(py){
		this->old_y = py;
	}
}
void PersonnagePacman::setOldToCurrent(){

		this->old_y = this->y;
		this->old_x = this->x;

}



void PersonnagePacman::setName(const char * pname){
	this->name = pname;
}

void PersonnagePacman::setCaractere(char pcar){
	this->caractere = pcar;
}

void PersonnagePacman::setColor(Couleur col){
	this->color = col;
}


void PersonnagePacman::monterPersonnage(){
	this->setX(x-1);
}
void PersonnagePacman::descendrePersonnage(){
	this->setX(x+1);
}
void PersonnagePacman::tournerDroitePersonnage(){
	this->setY(y+1);
}
void PersonnagePacman::tournerGauchePersonnage(){
	this->setY(y-1);
}

void PersonnagePacman::setDirectionCurrent(Direction dir){
	this->direction_current = dir;
}

void PersonnagePacman::setDirectionNext(Direction dir){
	this->direction_next = dir;
}

Direction PersonnagePacman::getDirectionCurrent(){
	return this->direction_current;
}

int PersonnagePacman::getFrequenceDijkstra()
{
	return frequenceDijkstra;
}

int PersonnagePacman::getDelaiDebut()
{
	return delaiDebut;
}

void PersonnagePacman::setFrequenceDijkstra(int frequenceDijkstra)
{
	this->frequenceDijkstra = frequenceDijkstra;
}

void PersonnagePacman::setDelaiDebut(int delaiDebut)
{
	this->delaiDebut = delaiDebut;
}

Direction PersonnagePacman::getDirectionNext(){
	return this->direction_next;
}
