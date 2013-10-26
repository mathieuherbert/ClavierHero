/*
 * MemoirePaginee.h
 *
 *  Created on: 24 oct. 2008
 *      Author: menaud
 */

#ifndef MEMOIREPAGINEE_H_
#define MEMOIREPAGINEE_H_

#include "Memoire.h"
#include "pagination/MemoirePhysique.h"
#include "pagination/Pagination.h"


class MemoirePaginee : public Memoire {


//	MemoirePhysique maMemoirePhysique;
//	Pagination maPagination;

	EcranV *monEcran;
	void test_paging(vaddr_t kernel_core_top_vaddr);

public:
//	 MemoirePhysique maMemoirePhysique;

	 void mem_setup(void *begin, int size,EcranV *ec);
	 vaddr_t malloc(size_t taille);
	 sextant_ret_t free(vaddr_t addr);
	 void memoireaffiche(EcranV *ec);
	 void test();
	 static void testP();

//	 void memoireaffiche();
};

#endif /* MEMOIREPAGINEE_H_ */
