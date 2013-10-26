/*
 * Canon.cpp
 *
 *  Created on: 22 oct. 2008
 *      Author: Aurélien
 */

#include "Canon.h"
#include "Applications/SpaceInvaders/Espace.h"

Canon::Canon(TimerSpaceInvaders *t, ClavierV *cla, int v, int ligne,
		int colonne, char *a, int h, int l, Couleur c) :
			EntiteBase(v, ligne, colonne, a, h, l, c) {
	timer = t;
	clavier = cla;
}

void Canon::run() {
	dessiner();
	while (true) {
/*JMM		while(!clavier->testChar() && !espace->niveauTermine()) {
			//
		}*/
		//if(espace->niveauTermine())
			//Exit();

		char c = clavier->getChar();

		// Le canon est en fait le joueur.
		// On a modifie les 2 touches qui n'etaient pas logique, on met donc q et d comme dans les applications standard
		// On a mis des limites au déplacement du canon afin qu'il reste sur sa ligne et ne puisse plus en sortir
		//et ainsi eviter les bugs graphiques que le groupe precedent n'avait pas prevu
		switch (c) {
		case 'd':
			if(positionColonne<COLONNES-TAILLE_CANON){
			deplacer(DEPL_DROITE);
			}
			break;
		case 'q':
			if(positionColonne>0){
			deplacer(DEPL_GAUCHE);
			}
			break;
		case ' ':
			MissileCanon::lancerNouveauMissile(getColonneCentre());
			break;
		}

	}
}

void Canon::infligerDegats(int degats){
	vie -= degats;
}
