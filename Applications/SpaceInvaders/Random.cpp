#include "Random.h"

#define RAND_MAX 4294967291

unsigned long int Random::random(void) {

	static unsigned long int random_seed = 93186752;
	static unsigned int a = 1588635695, q = 2, r = 1117695901;

	random_seed = a * (random_seed % q) - r * (random_seed / q);
	return random_seed;
}
;

int Random::nextInt(int max) {

	long double base;
	long double i;
	int resultat;

	base = (long double) random();
	i = (base / RAND_MAX);
	i = i * max;
	resultat = 0;

	while ((resultat < i) && (resultat < max)) {
		resultat++;
	}

	return resultat;
}
;

bool Random::nextBool() {

	unsigned long int base;
	float i;

	base = random();
	i = base / RAND_MAX;
	if (i < (0.5))
		return 1;
	else
		return 0;
}
;
