/*
 * Bibliotheque.cpp
 *
 *  Created on: 27 oct. 2013
 *      Author: julienderay
 */

#include "Bibliotheque.h"

Bibliotheque::Bibliotheque(EcranV* e, Timer* t) {
	ecran = e;
	timer = t;
}

Partition* Bibliotheque::auClairDeLaLune() {
	char titre[20];
	titre[0] = 'A';
	titre[1] = 'u';
	titre[2] = ' ';
	titre[3] = 'c';
	titre[4] = 'l';
	titre[5] = 'a';
	titre[6] = 'i';
	titre[7] = 'r';
	titre[8] = 'e';
	titre[9] = ' ';
	titre[10] = 'd';
	titre[11] = 'e';
	titre[12] = ' ';
	titre[13] = 'l';
	titre[14] = 'a';
	titre[15] = ' ';
	titre[16] = 'l';
	titre[17] = 'u';
	titre[18] = 'n';
	titre[19] = 'e';

	Note* tabDieses[0];
	Note* tabNotes[12];

	tabNotes[1] = new Note(new Puls(NOIRE), DO, FUN, O3, ecran, timer);
	tabNotes[2] = new Note(new Puls(NOIRE), DO, FUN, O3, ecran, timer);
	tabNotes[3] = new Note(new Puls(NOIRE), DO, FUN, O3, ecran, timer);
	tabNotes[4] = new Note(new Puls(NOIRE), RE, FDEUX, O3, ecran, timer);

	tabNotes[5] = new Note(new Puls(BLANCHE), MI, FTROIS, O3, ecran, timer);
	tabNotes[6] = new Note(new Puls(BLANCHE), RE, FDEUX, O3, ecran, timer);

	tabNotes[7] = new Note(new Puls(NOIRE), DO, FUN , O3, ecran, timer);
	tabNotes[8] = new Note(new Puls(NOIRE), MI, FTROIS , O3, ecran, timer);
	tabNotes[9] = new Note(new Puls(NOIRE), RE, FDEUX , O3, ecran, timer);
	tabNotes[10] = new Note(new Puls(NOIRE), RE, FDEUX , O3, ecran, timer);

	tabNotes[11] = new Note(new Puls(NOIRE), DO, FUN , O3, ecran, timer);

	return new Partition(titre, 100, tabNotes, 12, tabDieses, 0);
}


