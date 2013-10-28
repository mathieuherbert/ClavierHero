/*
 * Partition.h
 *
 *  Created on: 20 oct. 2013
 *      Author: Julien Deray, Mathieu Cartaud, Mathieu Herbert
 */

#ifndef PARTITION_H_
#define PARTITION_H_

#include "model/Hauteur.h"
#include "lib/String.h"
#include "Note.h"

class Note;

class Partition {
private:
	char* m_titre;
	double m_tempo;
	Note** m_partition;
	int m_taillePartition;
	Hauteur* m_dieses;
	int m_tailleDieses;
	Timer* timer;

	void applyDieses();


public:
	Partition(char* titre, int tempo,Note** partition, int taillePartition, Hauteur* dieses, int tailleDieses);
	long calculEcartement(Note* note);
	//	void setDieses(int dieses[]);
	void addNote(Note note);
	void lire();
};


#endif /* PARTITION_H_ */
