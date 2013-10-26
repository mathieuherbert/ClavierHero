
#ifndef UNITE_H_
#define UNITE_H_

#include "Position.h"

class Unite {
public:
	int
	pv,
	objetRecherche,
	objetPorte;
	bool paysan;
	Position *position;
	Position *objectif;
	Unite(Position *position,Position *objectif, bool paysan,int objetRecherche);
	bool perdDesPV(int pvPerdus);
};

#endif /* UNITE_H_ */
