/*
 * ImpApp.cpp
 *
 *  Created on: 24 nov. 2010
 *      Author: pouda
 */

#ifndef INTAPPCPP_H_
#define INTAPPCPP_H_

#include<Applications/Shell/IntApp.h>
#include<Applications/Shell/ShellV.h>
#include<lib/String.h>
class ImpApp : public IntApp{
private:
	String *nom;
	int pid;
	EcranV* ecran;
	int numShell;
protected:
	ShellV *shellV;

public:
ImpApp(String *name, ShellV *shellV, EcranV *ecranConsole){
	pid=pid++;
	nom=name;
	this->shellV=shellV;
	this->numShell=numShell;
	ecran = ecranConsole;
}
String* getNom(){
	return nom;
}
int getPid(){
	return pid;
}

EcranV* getEcran(){
	return ecran;
}

void ajouterThread(Threads *thread){
	//à faire
}

void killThread(Threads *thread){
	//thread->suspend(getPid());
}
void killHard(){
	//à faire
}
int getNumShell(){
	return numShell;
}

};

#endif /* INTAPP_H_ */
