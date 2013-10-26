/*
 * MemoireBloc.cpp
 *
 *  Created on: 26 oct. 2008
 *      Author: menaud
 */

#include "MemoireBloc.h"

#define DEBUG_MEMOIREBLOC 0


void MemoireBloc::mem_setup(void* begin, int size,EcranV* ecran) {
	memlist.mnext = (mblock*) begin;
	memlist.mlen = size - (unsigned)begin;
	(memlist.mnext)->mlen= size - (unsigned)begin;
	ec=ecran;
}

void MemoireBloc::memoireaffiche(EcranV *ec){

	mblock* bloc = &memlist;
	bloc = memlist.mnext;

	while (bloc!=NULL) {
	ec->afficherMot("\nBloc addr: ");
	ec->afficherBase((unsigned int) bloc,10,BLANC);
	ec->afficherMot(" | taille: ");
	ec->afficherBase((unsigned int) bloc->mlen,10,BLANC);
	ec->afficherMot("; bloc suiv: ");
	ec->afficherBase((unsigned int) bloc->mnext,10,BLANC);
	bloc=bloc->mnext;
	}

}

vaddr_t MemoireBloc::malloc(size_t nbytes) {
	struct mblock *p, *q, *leftover;
//	int *taille;

	if (nbytes > (size_t) taillebloc) return SEXTANT_ERROR; // pour sauvegarder la taille
	else nbytes=taillebloc;

	if(DEBUG_MEMOIREBLOC==1) {
		ec->sautDeLigne();
		ec->afficherMot("Malloc adresse de retour : ");
	}

	if(nbytes==0 || memlist.mnext== (struct mblock *) NULL) {
		return(NULL);
	}
	//q pointe sur le bloc courant et p sur le bloc suivant
	for (q= &memlist,p=memlist.mnext ;p != (struct mblock *) NULL ;q=p,p=p->mnext)
		if(p->mlen == nbytes) {//On demande toute la mŽmoire
			q->mnext = p->mnext;

//			taille=(int*)p;
//			*taille=(nbytes);
//			taille=taille+1;

			if(DEBUG_MEMOIREBLOC==1) {
				ec->afficherBase((unsigned int) p,10,BLANC);
				ec->afficherMot(" Taille : ");
				ec->afficherBase((unsigned int) nbytes,10,BLANC);
			}
			return( (vaddr_t)p );
		} else if ( p->mlen > nbytes ) {
			leftover = (struct mblock *)( (unsigned)p + nbytes );//Recucupere le bloc de taille voulue
			q->mnext = leftover;//insertion du nouveau bloc dans la liste

			leftover->mnext = p->mnext;
			leftover->mlen = p->mlen - nbytes;

//			taille=(int*)p;


			if(DEBUG_MEMOIREBLOC==1) {
				ec->afficherBase((unsigned int) p,10,BLANC);
				ec->afficherMot(" Taille : ");
				ec->afficherBase((unsigned int) nbytes,10,BLANC);

			}

			return((vaddr_t)p);
		}
	return NULL;
}

sextant_ret_t MemoireBloc::free(unsigned int addr) {
	struct mblock *p,*q, *block;
	unsigned top;

	block = (struct mblock*) addr;
	int size = taillebloc;

	if(DEBUG_MEMOIREBLOC==1) {
		ec->sautDeLigne();
		ec->afficherMot("Free adresse de debut : ");
		ec->afficherBase((unsigned int) block,10,BLANC);
		ec->afficherMot(" Taille : ");
		ec->afficherBase((unsigned int) size,10,BLANC);
	}

	/* Recherche ou inserer le bloc */

	for( p=memlist.mnext,q= &memlist;
	     p != (struct mblock *) NULL && p < block ;
	     q=p,p=p->mnext )
		;

	/* test pour verifier si l'adresse passee est bien valide */
	if ((top=q->mlen+(unsigned)q)>(unsigned)block && q!= &memlist ||
	    p!=NULL && (size+(unsigned)block) > (unsigned)p ) {
		return(SEXTANT_ERROR);
	}

	/* Ajout du bloc dans la liste chainee */
	if ( q!= &memlist && top == (unsigned)block )
			q->mlen += size;
	else {
		block->mlen = size;
		block->mnext = p;
		q->mnext = block;
		q = block;
	}

	/* ici on realise une concatenation */
	if ( (unsigned)( q->mlen + (unsigned)q ) == (unsigned)p) {
		q->mlen += p->mlen;
		q->mnext = p->mnext;
	}
	return(SEXTANT_OK);


}
