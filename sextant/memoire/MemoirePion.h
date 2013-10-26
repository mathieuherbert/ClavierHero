/*
 * MemoirePion.h
 *
 *  Created on: 23 oct. 2008
 *      Author: menaud
 */

#ifndef MEMOIREPION_H_
#define MEMOIREPION_H_
#include "Memoire.h"


class MemoirePion : public Memoire {
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



#endif /* MEMOIREPION_H_ */
