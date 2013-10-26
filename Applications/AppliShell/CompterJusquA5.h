/*
 * CompterJusquA5.h
 *
 *  Created on: 8 déc. 2010
 *      Author: Antoine
 */

#ifndef COMPTERJUSQUA5_H_
#define COMPTERJUSQUA5_H_
#include <sextant/types.h>
#include <drivers/timer.h>
#include <Applications/Shell/ShellV.h>
#include <Applications/Shell/ImpApp.cpp>
class CompterJusquA5  {
private:
	ShellV *shellV;
	Timer *timer;
	EcranV *ecranV;
public:
	CompterJusquA5(ShellV *shellV, EcranV *ecranV,Timer *timer);
	void run();
	void compterJusquA5();
	void killSoft();

	IntApp* getClone(EcranV* ecran);
};

#endif /* COMPTERJUSQUA5_H_ */
