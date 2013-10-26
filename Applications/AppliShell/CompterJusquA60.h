/*
 * CompterJusquA10.h
 *
 *  Created on: 8 déc. 2010
 *      Author: Antoine
 */

#ifndef COMPTERJUSQUA60_H_
#define COMPTERJUSQUA60_H_
#include <drivers/EcranV.h>
#include <drivers/Clavier.h>
#include <sextant/types.h>
#include <drivers/timer.h>
#include <Applications/Shell/ShellV.h>
#include <Applications/Shell/IntApp.h>
class CompterJusquA60 {
private:
	ShellV *shellV;
	Timer *timer;
public:
	CompterJusquA60(ShellV *shellV, EcranV *ecranV,Timer *timer);
	void run();
	void compterJusquA60();
	void killSoft();
	static IntApp getClone();
};
#endif /* COMPTERJUSQUA60_H_ */
