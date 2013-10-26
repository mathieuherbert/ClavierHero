/*
 * Attaque.h
 *
 *  Created on: 12 déc. 2011
 *      Author: Fabien
 */

#ifndef ATTAQUE_H_
#define ATTAQUE_H_

class Attaque{


public :
	int ralentissement;
	int degats;
	int paralysie;
	int zone;


	//constructeur
	Attaque( int degats,int ralentissement, int paralysie, int zone);

	//Retourne le ralentissement (int)
	int getRalentissement();
	 //Retourne les degats de la tour (int)
	int getDegats();

	int getParalysie();

	int getZone();


};


#endif /* ATTAQUE_H_ */
