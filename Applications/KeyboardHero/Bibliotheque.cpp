/*
 * Bibliotheque.cpp
 *
 *  Created on: 27 oct. 2013
 *      Author: Julien Deray, Mathieu Cartaud, Mathieu Herbert
 */

#include "Bibliotheque.h"
#include "core/SonClavierHero.h"
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
	ClavierHero::valScoreInf =-10;
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

	SonClavierHero* son = new SonClavierHero(ecran,tabNotes[0],1 );
	son->stop();

}
/*
 * Partition Super Mario
 */
void Bibliotheque::superMario() {
	ClavierHero::valScoreInf =-30;
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

	tabNotes[0] = new Note(new Puls(DCROCHE), SOLD, FDEUX, O3, ecran, timer);
	tabNotes[1] = new Note(new Puls(CROCHE), SOLD, FDEUX, O3, ecran, timer);
	tabNotes[2] = new Note(new Puls(DCROCHE), SOLD, FDEUX, O3, ecran, timer);
	tabNotes[4] = new Note(new Puls(DCROCHE), SOUPIRE, FDEUX, O3, ecran, timer);
	tabNotes[5] = new Note(new Puls(DCROCHE), MI, FUN, O3, ecran, timer);
	tabNotes[6] = new Note(new Puls(CROCHE), SOL, FDEUX, O3, ecran, timer);
	tabNotes[7] = new Note(new Puls(NOIRE), MI, FQUATRE, O4, ecran, timer);
	tabNotes[8] = new Note(new Puls(NOIRE), LA, FUN, O3, ecran, timer);

	tabNotes[9] = new Note(new Puls(CROCHE), RED, FTROIS, O4, ecran, timer);
	tabNotes[10] = new Note(new Puls(DCROCHE), LA, FDEUX, O3, ecran, timer);
	tabNotes[11] = new Note(new Puls(CROCHE), FA, FUN, O3, ecran, timer);
	tabNotes[12] = new Note(new Puls(DCROCHE), SOUPIRE, FDEUX, O3, ecran, timer);
	tabNotes[13] = new Note(new Puls(CROCHE), SI, FDEUX, O3, ecran, timer);
	tabNotes[14] = new Note(new Puls(DCROCHE), DOD, FQUATRE, O3, ecran, timer);
	tabNotes[15] = new Note(new Puls(DCROCHE), DO, FTROIS, O3, ecran, timer);
	tabNotes[16] = new Note(new Puls(CROCHE), SI, FDEUX, O3, ecran, timer);

	tabNotes[17] = new Note(new Puls(DCROCHE), LA, FUN, O3, ecran, timer);
	tabNotes[18] = new Note(new Puls(CROCHE), FA, FDEUX, O4, ecran, timer);
	tabNotes[19] = new Note(new Puls(DCROCHE), LA, FTROIS, O4, ecran, timer);
	tabNotes[20] = new Note(new Puls(CROCHE), SI, FQUATRE, O4, ecran, timer);
	tabNotes[21] = new Note(new Puls(DCROCHE), SOL, FUN, O4, ecran, timer);
	tabNotes[22] = new Note(new Puls(DCROCHE), LA, FQUATRE, O4, ecran, timer);
	tabNotes[23] = new Note(new Puls(DCROCHE), SOUPIRE, FDEUX, O3, ecran, timer);
	tabNotes[24] = new Note(new Puls(CROCHE), FA, FTROIS, O4, ecran, timer);
	tabNotes[25] = new Note(new Puls(DCROCHE), RE, FUN, O4, ecran, timer);
	tabNotes[26] = new Note(new Puls(DCROCHE), MI, FDEUX, O4, ecran, timer);
	tabNotes[27] = new Note(new Puls(CROCHE), DO, FUN, O4, ecran, timer);

	tabNotes[28] = new Note(new Puls(CROCHE), RED, FTROIS, O4, ecran, timer);
	tabNotes[29] = new Note(new Puls(DCROCHE), LA, FDEUX, O3, ecran, timer);
	tabNotes[30] = new Note(new Puls(CROCHE), FA, FUN, O3, ecran, timer);
	tabNotes[31] = new Note(new Puls(DCROCHE), SOUPIRE, FDEUX, O3, ecran, timer);
	tabNotes[32] = new Note(new Puls(CROCHE), SI, FDEUX, O3, ecran, timer);
	tabNotes[33] = new Note(new Puls(DCROCHE), DOD, FQUATRE, O3, ecran, timer);
	tabNotes[34] = new Note(new Puls(DCROCHE), DO, FTROIS, O3, ecran, timer);
	tabNotes[35] = new Note(new Puls(CROCHE), SI, FDEUX, O3, ecran, timer);

	tabNotes[36] = new Note(new Puls(DCROCHE), LA, FUN, O3, ecran, timer);
	tabNotes[37] = new Note(new Puls(CROCHE), FA, FDEUX, O4, ecran, timer);
	tabNotes[38] = new Note(new Puls(DCROCHE), LA, FTROIS, O4, ecran, timer);
	tabNotes[39] = new Note(new Puls(CROCHE), SI, FQUATRE, O4, ecran, timer);
	tabNotes[40] = new Note(new Puls(DCROCHE), SOL, FUN, O4, ecran, timer);
	tabNotes[41] = new Note(new Puls(DCROCHE), LA, FQUATRE, O4, ecran, timer);
	tabNotes[42] = new Note(new Puls(DCROCHE), SOUPIRE, FDEUX, O3, ecran, timer);
	tabNotes[43] = new Note(new Puls(CROCHE), FA, FTROIS, O4, ecran, timer);
	tabNotes[44] = new Note(new Puls(DCROCHE), RE, FUN, O4, ecran, timer);
	tabNotes[45] = new Note(new Puls(DCROCHE), MI, FDEUX, O4, ecran, timer);
	tabNotes[46] = new Note(new Puls(CROCHE), DO, FUN, O4, ecran, timer);

	tabNotes[47] = new Note(new Puls(CROCHE), SOUPIRE, FDEUX, O3, ecran, timer);
	tabNotes[48] = new Note(new Puls(DCROCHE), LA, FUN, O4, ecran, timer);
	tabNotes[49] = new Note(new Puls(DCROCHE), SOLD, FUN, O4, ecran, timer);
	tabNotes[50] = new Note(new Puls(DCROCHE), SOL, FUN, O4, ecran, timer);
	tabNotes[51] = new Note(new Puls(CROCHE), FA, FUN, O4, ecran, timer);
	tabNotes[52] = new Note(new Puls(DCROCHE), FA, FUN, O4, ecran, timer);
	tabNotes[53] = new Note(new Puls(DCROCHE), SOUPIRE, FDEUX, O3, ecran, timer);
	tabNotes[54] = new Note(new Puls(DCROCHE), LAD, FUN, O3, ecran, timer);
	tabNotes[55] = new Note(new Puls(DCROCHE), SI, FUN, O3, ecran, timer);
	tabNotes[56] = new Note(new Puls(DCROCHE), RE, FUN, O3, ecran, timer);
	tabNotes[57] = new Note(new Puls(DCROCHE), SOUPIRE, FDEUX, O3, ecran, timer);
	tabNotes[58] = new Note(new Puls(DCROCHE), SI, FUN, O3, ecran, timer);
	tabNotes[59] = new Note(new Puls(DCROCHE), RE, FUN, O3, ecran, timer);
	tabNotes[60] = new Note(new Puls(DCROCHE), RED, FUN, O3, ecran, timer);

	tabNotes[61] = new Note(new Puls(DCROCHE), LA, FUN, O4, ecran, timer);
	tabNotes[62] = new Note(new Puls(DCROCHE), SOLD, FUN, O4, ecran, timer);
	tabNotes[63] = new Note(new Puls(DCROCHE), SOUPIRE, FDEUX, O3, ecran, timer);
	tabNotes[64] = new Note(new Puls(DCROCHE), SOL, FUN, O4, ecran, timer);
	tabNotes[65] = new Note(new Puls(CROCHE), FA, FUN, O4, ecran, timer);
	tabNotes[67] = new Note(new Puls(DCROCHE), FA, FUN, O4, ecran, timer);
	tabNotes[68] = new Note(new Puls(DCROCHE), SOUPIRE, FDEUX, O3, ecran, timer);
	tabNotes[69] = new Note(new Puls(CROCHE), RE, FUN, O5, ecran, timer);
	tabNotes[70] = new Note(new Puls(DCROCHE), RE, FUN, O5, ecran, timer);
	tabNotes[71] = new Note(new Puls(NOIRE), RE, FUN, O5, ecran, timer);

	tabNotes[72] = new Note(new Puls(CROCHE), SOUPIRE, FDEUX, O3, ecran, timer);
	tabNotes[73] = new Note(new Puls(DCROCHE), LA, FUN, O5, ecran, timer);
	tabNotes[74] = new Note(new Puls(DCROCHE), SOLD, FUN, O5, ecran, timer);
	tabNotes[75] = new Note(new Puls(DCROCHE), SOL, FUN, O5, ecran, timer);
	tabNotes[76] = new Note(new Puls(CROCHE), FA, FUN, O5, ecran, timer);
	tabNotes[77] = new Note(new Puls(DCROCHE), FA, FUN, O5, ecran, timer);
	tabNotes[78] = new Note(new Puls(DCROCHE), SOUPIRE, FDEUX, O3, ecran, timer);
	tabNotes[79] = new Note(new Puls(DCROCHE), LAD, FUN, O4, ecran, timer);
	tabNotes[80] = new Note(new Puls(DCROCHE), SI, FUN, O4, ecran, timer);
	tabNotes[81] = new Note(new Puls(DCROCHE), RE, FUN, O4, ecran, timer);
	tabNotes[82] = new Note(new Puls(DCROCHE), SOUPIRE, FDEUX, O3, ecran, timer);
	tabNotes[83] = new Note(new Puls(DCROCHE), SI, FUN, O4, ecran, timer);
	tabNotes[84] = new Note(new Puls(DCROCHE), RE, FUN, O4, ecran, timer);
	tabNotes[85] = new Note(new Puls(DCROCHE), RED, FUN, O4, ecran, timer);
	tabNotes[86] = new Note(new Puls(CROCHE), SOUPIRE, FDEUX, O3, ecran, timer);
	tabNotes[89] = new Note(new Puls(CROCHE), LAD, FUN, O4, ecran, timer);
	tabNotes[90] = new Note(new Puls(DCROCHE), SOUPIRE, FDEUX, O3, ecran, timer);
	tabNotes[91] = new Note(new Puls(CROCHE), SI, FUN, O4, ecran, timer);
	tabNotes[92] = new Note(new Puls(BLANCHE), RE, FUN, O4, ecran, timer);

	tabNotes[93] = new Note(new Puls(DCROCHE), FA, FUN, O4, ecran, timer);
	tabNotes[94] = new Note(new Puls(CROCHE), RE, FUN, O4, ecran, timer);
	tabNotes[95] = new Note(new Puls(DCROCHE), LA, FUN, O4, ecran, timer);
	tabNotes[96] = new Note(new Puls(CROCHE), LAD, FUN, O4, ecran, timer);
	tabNotes[97] = new Note(new Puls(CROCHE), SOL, FUN, O4, ecran, timer);
	tabNotes[98] = new Note(new Puls(DCROCHE), SI, FUN, O4, ecran, timer);
	tabNotes[99] = new Note(new Puls(CROCHE), DO, FUN, O4, ecran, timer);
	tabNotes[100] = new Note(new Puls(DCROCHE), SI, FUN, O4, ecran, timer);
	tabNotes[101] = new Note(new Puls(NOIRE), SI, FUN, O4, ecran, timer);

	tabNotes[102] = new Note(new Puls(DCROCHE), SI, FUN, O4, ecran, timer);
	tabNotes[103] = new Note(new Puls(CROCHE), LA, FUN, O4, ecran, timer);
	tabNotes[104] = new Note(new Puls(DCROCHE), SOL, FUN, O3, ecran, timer);
	tabNotes[105] = new Note(new Puls(DCROCHE), FA, FUN, O3, ecran, timer);
	tabNotes[106] = new Note(new Puls(CROCHE), RE, FUN, O3, ecran, timer);
	tabNotes[107] = new Note(new Puls(DCROCHE), SI, FUN, O3, ecran, timer);
	tabNotes[108] = new Note(new Puls(DCROCHE), LA, FUN, O2, ecran, timer);
	tabNotes[109] = new Note(new Puls(CROCHE), FA, FUN, O3, ecran, timer);
	tabNotes[110] = new Note(new Puls(DCROCHE), RE, FUN, O3, ecran, timer);
	tabNotes[111] = new Note(new Puls(NOIRE), LA, FUN, O2, ecran, timer);

	tabNotes[112] = new Note(new Puls(DCROCHE), LAD, FUN, O2, ecran, timer);
	tabNotes[113] = new Note(new Puls(CROCHE), SI, FUN, O2, ecran, timer);
	tabNotes[114] = new Note(new Puls(DCROCHE), SOL, FUN, O3, ecran, timer);
	tabNotes[115] = new Note(new Puls(CROCHE), SOL, FUN, O3, ecran, timer);
	tabNotes[116] = new Note(new Puls(CROCHE), SI, FUN, O3, ecran, timer);

	tabNotes[117] = new Note(new Puls(DCROCHE), DO, FUN, O3, ecran, timer);
	tabNotes[118] = new Note(new Puls(CROCHE), SOL, FUN, O4, ecran, timer);
	tabNotes[119] = new Note(new Puls(DCROCHE), SOL, FUN, O4, ecran, timer);
	tabNotes[120] = new Note(new Puls(NOIRE), SOL, FUN, O4, ecran, timer);
	tabNotes[121] = new Note(new Puls(DCROCHE), FA, FUN, O4, ecran, timer);
	tabNotes[122] = new Note(new Puls(CROCHE), MI, FUN, O4, ecran, timer);
	tabNotes[123] = new Note(new Puls(DCROCHE), RE, FUN, O4, ecran, timer);

	tabNotes[124] = new Note(new Puls(DCROCHE), DO, FUN, O4, ecran, timer);
	tabNotes[125] = new Note(new Puls(CROCHE), SOL, FUN, O5, ecran, timer);
	tabNotes[126] = new Note(new Puls(DCROCHE), SOL, FUN, O5, ecran, timer);
	tabNotes[127] = new Note(new Puls(DCROCHE), SOL, FUN, O5, ecran, timer);
	tabNotes[128] = new Note(new Puls(CROCHE), FA, FUN, O5, ecran, timer);
	tabNotes[129] = new Note(new Puls(DCROCHE), MI, FUN, O5, ecran, timer);
	tabNotes[130] = new Note(new Puls(BLANCHE), RE, FUN, O5, ecran, timer);

	Partition* part = new Partition(titre, 60, tabNotes, 47, tabDieses, 2);
	part->lire();

	SonClavierHero* son = new SonClavierHero(ecran,tabNotes[0],1 );
	son->stop();
}

