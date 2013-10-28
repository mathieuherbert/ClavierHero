/*
 * Partition.cpp
 *
 *  Created on: 20 oct. 2013
 *      Author: julienderay
 */

#include "Partition.h"
#include "core/Conversion.h"
#include "ihm/FinDePartie.h"

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

	for (int i = 0; i < m_taillePartition; i++) {
		m_partition[i]->start("clavierHero");
		int ecartement = calculEcartement(m_partition[i]);
		m_partition[i]->duree=ecartement;
		int from = timer->getCsecondes();
		int to = from + ecartement;
		while (from < to) {
			from = timer->getCsecondes();
		}
		if (ClavierHero::SCORE_TROP_BAS) {
			break;
		}
	}
	FinDePartie fin = new FinDePartie(ClavierHero::SCORE_TROP_BAS);
	fin.afficherFin();
}

void Partition::applyDieses() {
	for (int j = 0; j < m_tailleDieses; j++) {
		for (int i = 0; i < m_taillePartition; i++) {
			if (m_partition[i]->getHauteur() == m_dieses[j])
				m_partition[i]->setDiese();
		}
	}
}

long Partition::calculEcartement(Note* note) {
	double temps = *note->getTempsNum();
	return (long) (m_tempo * (temps / (double) MULTIPLICATEUR) * 100);
}
