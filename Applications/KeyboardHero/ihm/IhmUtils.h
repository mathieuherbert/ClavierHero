/*
 * IhmUtils.h
 *
 *  Created on: 22 oct. 2013
 *      Author: mathieu
 */

#ifndef UHMUTILS_H_
#define UHMUTILS_H_

#include <drivers/EcranVMF.h>

class IhmUtils{
private:
	EcranVMF ecran;
	int score;

public:
	IhmUtils();
	void initialize();
	void createNote();
	int downNote(int position);
	void printScore();
	void printTouches();
	void printScoreContainer();
	void setScore(int newScore);
	int getScore();
};

#endif /* IHMUTILS_H_ */
