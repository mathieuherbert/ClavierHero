/*
 * Memoire.h
 *
 *  Created on: 23 oct. 2008
 *      Author: menaud
 */

#ifndef MEMOIRE_H_
#define MEMOIRE_H_

#include <drivers/EcranV.h>
#include <sextant/types.h>

class Memoire {

protected :
	Memoire();

public:
	int i; // pour test

	virtual void mem_setup(void *begin, int size,EcranV *ec);
	virtual vaddr_t malloc(size_t taille) ;
	virtual sextant_ret_t free(vaddr_t addr) ;
	virtual void memoireaffiche(EcranV *ec);
	virtual void test();
	static Memoire* nouveau();
};


void* operator new(size_t taille);
void  operator delete(void* ptr);
void* operator new[](size_t sz);
void* malloc(size_t taille);
void free(vaddr_t ptr);

#endif /* MEMOIRE_H_ */
