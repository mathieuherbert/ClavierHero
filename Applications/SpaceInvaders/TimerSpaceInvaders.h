/*
 * TimerSpaceInvaders.h
 *
 *  Created on: 27 oct. 2008
 *      Author: Aurélien
 */

#ifndef TIMERSPACEINVADERS_H_
#define TIMERSPACEINVADERS_H_

#include <drivers/timer.h>
#include <drivers/EcranV.h>
#include <sextant/Synchronisation/Semaphore/Semaphore.h>
#include "Applications/SpaceInvaders/ConfigSpaceInvader.h"
#include <sextant/interruptions/handler/handler_tic.h>

//extern int compteurTicHandler;

void ticTacSpaceInvader();

class Espace;

class TimerSpaceInvaders: public Timer {

private:
	EcranV *ecran;

	/*
	 * Sémaphore bloquant les threads.
	 */
	Semaphore *missileAliens[MISSILES_ALIENS_MAX];
	Semaphore *missileCanon;
	Semaphore *deplacementAliens;

	/*
	 * Temps d'attente en ms entre mis à jour du sémaphore.
	 */
	int timerMissileAliens;
	int timerMissilesCanon;
	int timerDeplacementAliens;

	//Compteur de secondes interruptible.
	int secondesTimer;
	//Compteur de secondes activé.
	bool compteurSecondesOn;

public:
	TimerSpaceInvaders(EcranV *ecran);

	/*
	 * Permet de faire le lien entre l'IRQ et le driver.
	 * Méthode appelée en boucle dans la méthode principale du jeu.
	 * A modifier afin de faire marcher le sémaphore du handler avec le driver.
	 */
	void handler(Espace *espace);

	/*
	 * Accesseurs simples permettant de récuperer les sémaphores pour chacuns des
	 * objets concernés.
	 * Ceux-ci sont débloqués automatiquement par le handler tic lorsque le délai
	 * est dépassé.
	 */
	Semaphore *getMissileAliens(int numeroMissile);
	Semaphore *getMissileCanon();
	Semaphore *getDeplacementAliens();

	/*
	 * Permet de fixer le délai de mise à jour pour chacun des objets suivants.
	 * Le délai est exprimé en ms.
	 */
	void setTimerMissileAliens(int ms);
	void setTimerMissileCanon(int ms);
	void setTimerDeplacementAliens(int ms);

	int getTimerDeplacementAliens();

	int getTemps();

	/*
	 * Relache tous les semaphores de 1, afin de couper les processus en attente
	 * et stoppe le compteur de seconde.
	 */
	void stopperTimer();

	/*
	 * Reset tous les semaphores et redémarre le compteur de seconde.
	 */
	void demarrerTimer();

	void afficherTemps(int l, int c, int temps);
	void afficherChiffreCommente(int l, int c, const char* label,
			const int valeur, const int nbChiffres);
};

#endif /* TIMERSPACEINVADERS_H_ */
