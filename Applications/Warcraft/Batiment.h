
#ifndef BATIMENT_H_
#define BATIMENT_H_

#include "Position.h"

class Batiment{
public:
	int
	type,
	pv;
	Position *position;

	Batiment(int type,Position *position);

	bool perdDesPV(int pvPerdus);

	static const int QUARTIER_GENERAL = 0;
	static const int CASERNE = 1;
	static const int FERME = 2;
};

#endif /* BATIMENT_H_ */
