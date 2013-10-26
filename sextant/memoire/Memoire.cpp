/*
 * Memoire.cpp
 *
 *  Created on: 23 oct. 2008
 *      Author: menaud
 */


#include "Memoire.h"
#include "MemoirePion.h"
#include "MemoireListe.h"
#include "MemoirePaginee.h"

#include "op_memoire.h"

MemoirePion uneMemoire;

Memoire::Memoire(){
	i=0;
}
void Memoire::memoireaffiche(EcranV *ec){
	uneMemoire.memoireaffiche(ec);
}


void Memoire::mem_setup(void * begin, int size,EcranV *ecran) {
	uneMemoire.mem_setup(begin, size, ecran);
}

vaddr_t Memoire::malloc(size_t nbytes){
	return uneMemoire.malloc(nbytes);
}

void Memoire::test(){
	return uneMemoire.test();
}
sextant_ret_t Memoire::free(vaddr_t addr) {
	return uneMemoire.free(addr);
}

// Ce pattern singleton n'est pas guarantie pour le multi-threading lors de la creation de
// InterfaceMemoireIn. Cependant nous ne pouvons utiliser ici de new().
// C'est pour cette raison qu'il faut creer l'objet avant l'initialisation du multitaches.

Memoire* Memoire::nouveau(){
	static Memoire InterfaceMemoireIn;
	return &InterfaceMemoireIn;
}

void* operator new(size_t taille) {
	return (void*) (*(Memoire::nouveau())).malloc(taille);
};

void  operator delete(void* ptr)  { (*(Memoire::nouveau())).free((vaddr_t)ptr); return;};

void* operator new[](size_t sz) { void* vp = operator new(sz); return vp;};


void* malloc(size_t taille) { return (void*) (*(Memoire::nouveau())).malloc(taille);};

void free(vaddr_t ptr) { (*(Memoire::nouveau())).free((vaddr_t)ptr); return;};
