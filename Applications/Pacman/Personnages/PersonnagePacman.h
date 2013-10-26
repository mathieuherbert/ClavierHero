/*
 * PersonnagePacman.h
 *
 *  Created on: 21 oct. 2012
 *      Author: Administrateur
 */

#ifndef PersonnagePacman_H_
#define PersonnagePacman_H_


#include <sextant/types.h>
#include <Applications/Pacman/config.h>
class PersonnagePacman {
public:
	PersonnagePacman();
	PersonnagePacman(const char * pname);
	int getX();
	int getY();
	int getOldX();
	int getOldY();
	const char * getName();
	char getCaractere();
	Couleur getColor();
	int hasMoved();
	void setX(int px);
	void setY(int py);
	void setOldX(int px);
	void setOldY(int py);
	void setOldToCurrent();
	void setName(const char * pname);
	void setColor(Couleur pcolor);
	void setCaractere(const char pcar);
	void monterPersonnage();
	void descendrePersonnage();
	void tournerDroitePersonnage();
	void tournerGauchePersonnage();
	void setDirectionCurrent(Direction dir);
	void setDirectionNext(Direction dir);
	int getFrequenceDijkstra();
	int getDelaiDebut();
	void setFrequenceDijkstra(int frequenceDijkstra);
	void setDelaiDebut(int delaiDebut);
	Direction getDirectionCurrent();
	Direction getDirectionNext();
	Direction direction_current;
	Direction direction_next;
protected:
	int old_x;
	int old_y;
	int x;
	int y;
	const char * name;
	char caractere;
	Couleur color;

	// Frequence de calcul de dijkstra (tous les X coups)
	int frequenceDijkstra;

	// Delai avant de commencer ˆ bouger
	int delaiDebut;

};

#endif /* PersonnagePacman_H_ */
