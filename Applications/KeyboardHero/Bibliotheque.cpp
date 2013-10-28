/*
 * Bibliotheque.cpp
 *
 *  Created on: 27 oct. 2013
 *      Author: Julien Deray, Mathieu Cartaud, Mathieu Herbert
 */

#include "Bibliotheque.h"

Bibliotheque::Bibliotheque(EcranV* e, Timer* t) {
	ecran = e;
	timer = t;
}
//On affiche le nom de la partition
void Bibliotheque::afficherNomPartition(char* part)
{
    ecran->afficherMot(7,60,"Partition : ",BLANC);
    ecran->afficherMot(8,60,part,BLANC);
}
/*
 * Partition de la chanson Au Claire de la Lune
 */
void Bibliotheque::auClairDeLaLune() {
	ClavierHero::VAL_SCORE_INF =-10;
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

	Hauteur tabDieses[0];
	Note* tabNotes[11];
	afficherNomPartition("Au claire de la lune");
	tabNotes[0] = new Note(new Puls(NOIRE), DO, FUN, O3, ecran, new Timer());
	tabNotes[1] = new Note(new Puls(NOIRE), DO, FUN, O3, ecran, new Timer());
	tabNotes[2] = new Note(new Puls(NOIRE), DO, FUN, O3, ecran, new Timer());
	tabNotes[3] = new Note(new Puls(NOIRE), RE, FDEUX, O3, ecran, new Timer());

	tabNotes[4] = new Note(new Puls(BLANCHE), MI, FTROIS, O3, ecran, new Timer());
	tabNotes[5] = new Note(new Puls(BLANCHE), RE, FDEUX, O3, ecran, new Timer());

	tabNotes[6] = new Note(new Puls(NOIRE), DO, FUN , O3, ecran, new Timer());
	tabNotes[7] = new Note(new Puls(NOIRE), MI, FTROIS , O3, ecran, new Timer());
	tabNotes[8] = new Note(new Puls(NOIRE), RE, FDEUX , O3, ecran, new Timer());
	tabNotes[9] = new Note(new Puls(NOIRE), RE, FDEUX , O3, ecran, new Timer());

	tabNotes[10] = new Note(new Puls(NOIRE), DO, FUN , O3, ecran, new Timer());

	Partition* part = new Partition(titre, 100, tabNotes, 11, tabDieses, 0);
	part->lire();

}
/*
 * Partition Super Mario
 */
void Bibliotheque::superMario() {
	ClavierHero::VAL_SCORE_INF =-30;
	char titre[11];

	Hauteur tabDieses[2];
	Note* tabNotes[47];

	titre[0] = 'S';
	titre[1] = 'u';
	titre[2] = 'p';
	titre[3] = 'e';
	titre[4] = 'r';
	titre[5] = ' ';
	titre[6] = 'M';
	titre[7] = 'a';
	titre[8] = 'r';
	titre[9] = 'i';
	titre[10] = 'o';
	afficherNomPartition("Super Mario");
	tabDieses[0] = DO;
	tabDieses[1] = FA;

	tabNotes[0] = new Note(new Puls(CROCHE), SOLD, FDEUX, O3, ecran, timer);
	tabNotes[1] = new Note(new Puls(CROCHE), SOLD, FDEUX, O3, ecran, timer);
	tabNotes[2] = new Note(new Puls(CROCHE), SOLD, FDEUX, O3, ecran, timer);
	tabNotes[3] = new Note(new Puls(CROCHE), SOLD, FDEUX, O3, ecran, timer);
	tabNotes[4] = new Note(new Puls(CROCHE), SOUPIRE, FDEUX, O3, ecran, timer);
	tabNotes[5] = new Note(new Puls(CROCHE), MI, FUN, O3, ecran, timer);
	tabNotes[6] = new Note(new Puls(CROCHE), SOL, FDEUX, O3, ecran, timer);
	tabNotes[7] = new Note(new Puls(NOIRE), MI, FQUATRE, O4, ecran, timer);
	tabNotes[8] = new Note(new Puls(NOIRE), LA, FUN, O3, ecran, timer);

	tabNotes[9] = new Note(new Puls(CROCHE), RED, FTROIS, O4, ecran, timer);
	tabNotes[10] = new Note(new Puls(CROCHE), LA, FDEUX, O3, ecran, timer);
	tabNotes[11] = new Note(new Puls(CROCHE), FA, FUN, O3, ecran, timer);
	tabNotes[12] = new Note(new Puls(CROCHE), SOUPIRE, FDEUX, O3, ecran, timer);
	tabNotes[13] = new Note(new Puls(CROCHE), SI, FDEUX, O3, ecran, timer);
	tabNotes[14] = new Note(new Puls(CROCHE), DOD, FQUATRE, O3, ecran, timer);
	tabNotes[15] = new Note(new Puls(CROCHE), DO, FTROIS, O3, ecran, timer);
	tabNotes[16] = new Note(new Puls(CROCHE), SI, FDEUX, O3, ecran, timer);

	tabNotes[17] = new Note(new Puls(CROCHE), LA, FUN, O3, ecran, timer);
	tabNotes[18] = new Note(new Puls(CROCHE), FA, FDEUX, O4, ecran, timer);
	tabNotes[19] = new Note(new Puls(CROCHE), LA, FTROIS, O4, ecran, timer);
	tabNotes[20] = new Note(new Puls(CROCHE), SI, FQUATRE, O4, ecran, timer);
	tabNotes[21] = new Note(new Puls(CROCHE), SOL, FUN, O4, ecran, timer);
	tabNotes[22] = new Note(new Puls(CROCHE), LA, FQUATRE, O4, ecran, timer);
	tabNotes[23] = new Note(new Puls(CROCHE), SOUPIRE, FDEUX, O3, ecran, timer);
	tabNotes[24] = new Note(new Puls(CROCHE), FA, FTROIS, O4, ecran, timer);
	tabNotes[25] = new Note(new Puls(CROCHE), RE, FUN, O4, ecran, timer);
	tabNotes[26] = new Note(new Puls(CROCHE), MI, FDEUX, O4, ecran, timer);
	tabNotes[27] = new Note(new Puls(CROCHE), DO, FUN, O4, ecran, timer);

	tabNotes[28] = new Note(new Puls(CROCHE), RED, FTROIS, O4, ecran, timer);
	tabNotes[29] = new Note(new Puls(CROCHE), LA, FDEUX, O3, ecran, timer);
	tabNotes[30] = new Note(new Puls(CROCHE), FA, FUN, O3, ecran, timer);
	tabNotes[31] = new Note(new Puls(CROCHE), SOUPIRE, FDEUX, O3, ecran, timer);
	tabNotes[32] = new Note(new Puls(CROCHE), SI, FDEUX, O3, ecran, timer);
	tabNotes[33] = new Note(new Puls(CROCHE), DOD, FQUATRE, O3, ecran, timer);
	tabNotes[34] = new Note(new Puls(CROCHE), DO, FTROIS, O3, ecran, timer);
	tabNotes[35] = new Note(new Puls(CROCHE), SI, FDEUX, O3, ecran, timer);

	tabNotes[36] = new Note(new Puls(CROCHE), LA, FUN, O3, ecran, timer);
	tabNotes[37] = new Note(new Puls(CROCHE), FA, FDEUX, O4, ecran, timer);
	tabNotes[38] = new Note(new Puls(CROCHE), LA, FTROIS, O4, ecran, timer);
	tabNotes[39] = new Note(new Puls(CROCHE), SI, FQUATRE, O4, ecran, timer);
	tabNotes[40] = new Note(new Puls(CROCHE), SOL, FUN, O4, ecran, timer);
	tabNotes[41] = new Note(new Puls(CROCHE), LA, FQUATRE, O4, ecran, timer);
	tabNotes[42] = new Note(new Puls(CROCHE), SOUPIRE, FDEUX, O3, ecran, timer);
	tabNotes[43] = new Note(new Puls(CROCHE), FA, FTROIS, O4, ecran, timer);
	tabNotes[44] = new Note(new Puls(CROCHE), RE, FUN, O4, ecran, timer);
	tabNotes[45] = new Note(new Puls(CROCHE), MI, FDEUX, O4, ecran, timer);
	tabNotes[46] = new Note(new Puls(CROCHE), DO, FUN, O4, ecran, timer);

	Partition* part = new Partition(titre, 60, tabNotes, 47, tabDieses, 2);
	part->lire();
}

