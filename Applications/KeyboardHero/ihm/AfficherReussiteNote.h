/*
 * AfficherReussiteNote.h
 *
 *  Created on: 27 oct. 2013
 *      Author: mathieu
 */

#ifndef AFFICHERREUSSITENOTE_H_
#define AFFICHERREUSSITENOTE_H_

#include <drivers/EcranV.h>
#include <sextant/Activite/Threads.h>

class AfficherReussiteNote : public Threads{
private:
	EcranV* ecran;
	int reussite;

	void afficherReussite();
	void effacerReussite();
	char* selectionnerMot();

public:
	AfficherReussiteNote(EcranV* e);
	void run();
	void setReussite(int i);
};


#endif /* AFFICHERREUSSITENOTE_H_ */
