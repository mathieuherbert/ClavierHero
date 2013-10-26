/*
 * ImpApp.cpp
 *
 *  Created on: 24 nov. 2010
 *      Author: pouda
 */

#ifndef IMPAPP_H_
#define IMPAPP_H_

#include<Applications/Shell/IntApp.h>
#include<Applications/Shell/ShellV.h>
#include<lib/String.h>

class ImpApp: public IntApp {
private:
	String *nom;
	int pid;
	EcranV* ecran;
	int numShell;
protected:
	ShellV *shellV;

public:
	ImpApp(String *name, ShellV *shellV, EcranV *ecranConsole);
	virtual ~ImpApp();

	virtual void killSoft();
	virtual void ajouterThread(Threads *thread);
	virtual void killThread(Threads *thread);
	virtual String* getNom();
	virtual int getPid();
	virtual void killHard();
	virtual int getNumShell();
	virtual EcranV* getEcran();
};

#endif /* IMPAPP_H_ */
