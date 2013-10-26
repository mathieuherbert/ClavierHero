/*
 * PortSerie.h
 *
 *  Created on: 4 août 2008
 *      Author: jmenaud
 */

#ifndef PORTSERIE_H_
#define PORTSERIE_H_

#include <hal/fonctionsES.h>

#define COM1 0
#define COM2 1
#define COM3 2
#define COM4 3
#define PAIRE 24
#define IMPAIRE 8
#define SANS 0
#define COM COM2

/*-------------------------------------------------------------------------

* LSR - Line Status Register

*-------------------------------------------------------------------------*/



#define LELSR 	5	      /* offset du registre LSR par rapport a COMx */

typedef struct {	      /* Line Status Register */
	unsigned DR:1;	      /* donnee recue : le registre de reception TBR est plein */
	unsigned OE:1;	      /* erreur de congestion */
	unsigned PE:1;	      /* erreur de parite */
	unsigned FE:1;	      /* erreur de format de caractere */
	unsigned BI:1;	      /* reception d'un signal "break" */
	unsigned DE:1;	      /* donnee emise : le registre d'emission THR est vide */
	unsigned TEMT:1;     /* Tous les registres d'emission sont vides */
	unsigned LSR_nul:1;  /* 1 bit toujours a zero */
} lsr;

typedef union {
	lsr s;
	unsigned char c;
} Lsr;


class PortSerie {
public :


	void ecrireMot(const char*);
	void ecrireCaractere(char c);

	char lireCaractere();

	// port _COM1_ COM2 COM3 COM4
	// vitesse : 50 75 110 150 300 600 1200 2400 4800 _9600_
	// longueur : 7 8
	// parite : P I S (paire impaire sans)
	// stop : nbr bit de stop

	void init_Com(int port, long vitesse, int longueur, char parite, char stop);
	void afficherChiffre(const int valeur);

};
#endif /* PORTSERIE_H_ */
