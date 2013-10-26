#ifndef RANDOMSP_H
#define RANDOMSP_H

/**
 * @file Random.h
 * @class Random
 * @brief Classe permettant de choisir un entier aléatoirement. 
*/

class RandomSP {
	unsigned long int random(void);

public :
	int nextInt(int);
	bool nextBool(void);
};
#endif


