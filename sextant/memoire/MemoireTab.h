/*
 * MemoireTab.h
 *
 *  Created on: 30 oct. 2008
 *      Author: menaud
 */

#ifndef MEMOIRETAB_H_
#define MEMOIRETAB_H_

#include "Memoire.h"

class MemoireTab : public Memoire {
private:
	void *debut;
	int taille;
	EcranV *ec;
public:
	 void mem_setup(void *begin, int size,EcranV *ec);
	 vaddr_t malloc(size_t taille);
	 sextant_ret_t free(vaddr_t addr);
	 void memoireaffiche(EcranV *ec);
	 sextant_ret_t ref_physpage_at(paddr_t ppage_paddr);

};

#endif /* MEMOIRETAB_H_ */
