/*
 * MemoireBloc.h
 *
 *  Created on: 26 oct. 2008
 *      Author: menaud
 */

#ifndef MEMOIREBLOC_H_
#define MEMOIREBLOC_H_

#include "Memoire.h"

struct	mblock	{
	struct mblock* mnext;
	unsigned int mlen;
};

class MemoireBloc : public Memoire {
private:
	void *debut;
	int taille;
	EcranV *ec;
	static const int taillebloc = 4096;
	struct mblock memlist;


public:
	 void mem_setup(void *begin, int size,EcranV *ec);
	 vaddr_t malloc(size_t taille);
	 sextant_ret_t free(vaddr_t addr);
	 void memoireaffiche(EcranV *ec);
};

#endif /* MEMOIREBLOC_H_ */
