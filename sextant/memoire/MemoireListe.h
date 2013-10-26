/*
 * MemoireListe.h
 *
 *  Created on: 24 oct. 2008
 *      Author: menaud
 */

#ifndef MEMOIRELISTE_H_
#define MEMOIRELISTE_H_

#include "Memoire.h"

class MemoireListe : public Memoire {
private:
	void *debut;
	int taille;
	EcranV *ec;
public:
	 void mem_setup(void *begin, int size,EcranV *ec);
	 vaddr_t malloc(size_t taille);
	 sextant_ret_t free(vaddr_t addr);
	 void memoireaffiche(EcranV *ec);
};


#endif /* MEMOIRELISTE_H_ */
