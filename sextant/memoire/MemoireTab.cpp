/*
 * MemoireTab.cpp
 *
 *  Created on: 30 oct. 2008
 *      Author: menaud
 */

#define DEBUG_MEMOIRETAB 0
#define BIOS_N_VIDEO_START 0xa0000
#define BIOS_N_VIDEO_END   0x100000

#include "MemoireTab.h"
#define ALIGN_INF(val,boundary) (((unsigned)(val)) & (~((boundary)-1)))
/** Align on a boundary (MUST be a power of 2), so that return value >= val */
#define ALIGN_SUP(val,boundary) ({ unsigned int __bnd=(boundary); (((((unsigned)(val))-1) & (~(__bnd - 1))) + __bnd); })

#define PAGE_ALIGN_INF(val) ALIGN_INF((val), PAGE_SIZE)
#define PAGE_ALIGN_SUP(val) ALIGN_SUP((val), PAGE_SIZE)

extern char __b_kernel, __e_kernel;
paddr_t kernel_core_base,kernel_core_top;

struct bloc {
//	int adresse;
	int cpt;
	bool isFree;
};

#define PAGE_SIZE 4096
#define MAXMEM 3000

bloc TabPages[MAXMEM];

void MemoireTab::memoireaffiche(EcranV *ec){
	ec->sautDeLigne();
	for (int i=0;i<(int)((int)debut+taille);i=i+PAGE_SIZE) {
		if (TabPages[i/PAGE_SIZE].isFree==false && TabPages[i/PAGE_SIZE].cpt==0)
			ec->afficherCaractere(BLANC,NOIR,'*');
		else if (TabPages[i/PAGE_SIZE].isFree==false && TabPages[i/PAGE_SIZE].cpt>0)
			ec->afficherCaractere(BLANC,NOIR,'X');
		else if (TabPages[i/PAGE_SIZE].isFree==false && TabPages[i/PAGE_SIZE].cpt==-1)
			ec->afficherCaractere(BLANC,NOIR,'X');
		else if (TabPages[i/PAGE_SIZE].isFree==true && TabPages[i/PAGE_SIZE].cpt==0)
			ec->afficherCaractere(BLANC,NOIR,'-');
		else
			ec->afficherCaractere(BLANC,NOIR,'?');
	}
}


void MemoireTab::mem_setup(void * begin, int size,EcranV *ecran) {
	taille=size - (int) begin;
	debut=begin;
	ec=ecran;
//	int tmp;

	kernel_core_base = PAGE_ALIGN_INF((paddr_t)(& __b_kernel));
	kernel_core_top = PAGE_ALIGN_SUP((paddr_t)(& __e_kernel));

//		PAGE_DESCR_ARRAY_ADDR + PAGE_ALIGN_SUP(
//			(size >> PAGE_SHIFT) * sizeof(struct physical_page_descr));

	for (int i=0;i<(int)begin;i=i+PAGE_SIZE) {
		TabPages[i/PAGE_SIZE].isFree=false;
		TabPages[i/PAGE_SIZE].cpt=0;
	}

	for (int i=(int)begin;i<size;i=i+PAGE_SIZE) {
		TabPages[i/PAGE_SIZE].isFree=true;
		TabPages[i/PAGE_SIZE].cpt=0;
	}

	for (int i=size;i<MAXMEM;i=i+PAGE_SIZE) {
		TabPages[i/PAGE_SIZE].isFree=false;
		TabPages[i/PAGE_SIZE].cpt=0;
	}

	for (int i=kernel_core_base;i<(int)kernel_core_top;i=i+PAGE_SIZE) {
			TabPages[i/PAGE_SIZE].isFree=false;
			TabPages[i/PAGE_SIZE].cpt=-1;
		}

	for (int i=BIOS_N_VIDEO_START;i<(int)BIOS_N_VIDEO_END;i=i+PAGE_SIZE) {
			TabPages[i/PAGE_SIZE].isFree=false;
			TabPages[i/PAGE_SIZE].cpt=-1;
		}

}

vaddr_t MemoireTab::malloc(size_t nbytes)
{
	int i;

//	if (nbytes>PAGE_SIZE) return NULL;

//	nbytes=
	for (int i=0;i<(MAXMEM);i++) {
		if (TabPages[i].isFree==true) {
			TabPages[i].isFree=false;
			TabPages[i].cpt=1;
			i = i*PAGE_SIZE;
			return (vaddr_t) i;
		}
	}

	return NULL;

	if(DEBUG_MEMOIRETAB==1) {
		ec->sautDeLigne();
		ec->afficherMot("Adresse de debut : ");
//		ec->afficherBase((unsigned int) j,10,BLANC);
		ec->sautDeLigne();
		ec->afficherMot("Taille passee en param de malloc : ");
		ec->afficherBase((unsigned int) nbytes,10,BLANC);
		ec->sautDeLigne();
		ec->afficherMot("Taille enregistree : ");
//		ec->afficherBase((unsigned int) *p,10,BLANC);
		ec->sautDeLigne();
		ec->afficherMot("Al'adresse : ");
//		ec->afficherBase((unsigned int) p,10,BLANC);
		ec->sautDeLigne();
		ec->afficherMot("Adresse de fin : ");
		ec->afficherBase((unsigned int) i,10,BLANC);
		ec->sautDeLigne();
	}


}



sextant_ret_t MemoireTab::free(vaddr_t addr) {
	int *p;
	p=(int*)(addr);
	p=p-1;

//	if (TabPages[addr/PAGE_SIZE].isFree==true) return SEXTANT_ERROR;

//	else {
		if ((TabPages[addr/PAGE_SIZE].isFree==false) && (TabPages[addr/PAGE_SIZE].cpt>0)) {
			TabPages[addr/PAGE_SIZE].cpt--;
			if (TabPages[addr/PAGE_SIZE].cpt==0) TabPages[addr/PAGE_SIZE].isFree=true;
		}
//	}


	/* Question 2 */
	if(DEBUG_MEMOIRETAB==1) {
		ec->sautDeLigne();
		ec->afficherMot("Adresse de debut de free : ");
		ec->afficherBase((unsigned int) addr,10,BLANC);
		ec->sautDeLigne();
		ec->afficherMot("Taille retrouvee : ");
		ec->afficherBase((unsigned int) *p,10,BLANC);
		ec->sautDeLigne();
		ec->afficherMot("A l'adresse : ");
		ec->afficherBase((unsigned int) p,10,BLANC);
		ec->sautDeLigne();
	}

//	memset((void*)p,0,*p+4);

	return SEXTANT_OK;
}

sextant_ret_t MemoireTab::ref_physpage_at(paddr_t ppage_paddr) {

//  if(!ppage_paddr)
//    return -SEXTANT_ERROR;
  /* Increment the reference count for the page */

	TabPages[ppage_paddr/PAGE_SIZE].isFree=false;
	TabPages[ppage_paddr/PAGE_SIZE].cpt++;

  return true;
}
