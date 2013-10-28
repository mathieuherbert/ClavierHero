/*
 * Partition.cpp
 *
 *  Created on: 20 oct. 2013
 *      Author: Julien Deray, Mathieu Cartaud, Mathieu Herbert
 */

#include "Partition.h"
#include "core/Conversion.h"

Partition::Partition(char* titre, int tempo, Note** partition,
		int taillePartition, Hauteur* dieses, int tailledieses) :
	m_titre(titre), m_tempo(Conversion::fromBPMtoSec(tempo)), m_partition(
			partition), m_taillePartition(taillePartition), m_dieses(dieses),
			m_tailleDieses(tailledieses), timer(new Timer()) {
}

//void Partition::setDieses(int diesestmp[]) {
//	dieses = diesestmp;
//}

//void Partition::addNote(Note note) {
//	partition.add( note );
//}

void Partition::lire() {
	applyDieses();
	//boucle sur toutes les notes de la partition
	for (int i = 0; i < m_taillePartition; i++) {
		//on joue la note sur l ecran
		m_partition[i]->start("clavierHero");
		int ecartement = calculEcartement(m_partition[i]);
		m_partition[i]->duree = ecartement;
		int from = timer->getCsecondes();
		int to = from + ecartement;
		//attente de la prochaine note
		while (from < to) {
			from = timer->getCsecondes();
		}
		//si le score est inferieur a un score voulu on arrete
		if (ClavierHero::score < ClavierHero::valScoreInf) {
			break;
		}
	}
	//attente de fin de partie
	int from = timer->getSecondes();
	int to = from + 3;
	while (from < to) {
		from = timer->getSecondes();
	}

}

void Partition::applyDieses() {
	for (int j = 0; j < m_tailleDieses; j++) {
		for (int i = 0; i < m_taillePartition; i++) {
			if (m_partition[i]->getHauteur() == m_dieses[j])
				m_partition[i]->setDiese();
		}
	}
}
/*
 * Calcule l ecartement entre cette note et la suivante
 */
long Partition::calculEcartement(Note* note) {
	double temps = *note->getTempsNum();
	return (long) (m_tempo * (temps / (double) MULTIPLICATEUR) * 100);
}
