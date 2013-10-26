/*
 * handler_clavier.cpp
 *
 *  Created on: 8 août 2008
 *      Author: jmenaud
 */
static int ControlKeys;
static char leds;

#include "handler_clavier.h"
#include <hal/fonctionsES.h>
#include <drivers/EcranP.h>
#include <drivers/EcranV.h>

int console; // numero de la console active.

int posBuf=0;
char buf[TAILLE_BUF_CLAVIER];
bool modifBuf=false;

Semaphore *semaphoreClavier;


extern EcranP *ecranP;
extern EcranV ecranV[6];

int writechar(int sc) {
	int ch = 0;
	if ((ControlKeys & KBD_SHIFT) == 0)
		switch (sc) { // No SHIFT
		case 16: ch=K16; break;
		case 17: ch=K17; break;
		case 18: ch=K18; break;
		case 19: ch=K19; break;
		case 20: ch=K20; break;
		case 21: ch=K21; break;
		case 22: ch=K22; break;
		case 23: ch=K23; break;
		case 24: ch=K24; break;
		case 25: ch=K25; break;
		case 30: ch=K30; break;
		case 31: ch=K31; break;
		case 32: ch=K32; break;
		case 33: ch=K33; break;
		case 34: ch=K34; break;
		case 35: ch=K35; break;
		case 36: ch=K36; break;
		case 37: ch=K37; break;
		case 38: ch=K38; break;
		case 39: ch=K39; break;
		case 44: ch=K44; break;
		case 45: ch=K45; break;
		case 46: ch=K46; break;
		case 47: ch=K47; break;
		case 48: ch=K48; break;
		case 49: ch=K49; break;
		case 50: ch=K50; break;

		case 2: ch='1'; break;
		case 3: ch='2'; break;
		case 4: ch='3'; break;
		case 5: ch='4'; break;
		case 6: ch='5'; break;
		case 7: ch='6'; break;
		case 8: ch='7'; break;
		case 9: ch='8'; break;
		case 10: ch='9'; break;
		case 11: ch='0'; break;
		case 57: ch=' '; break;
		case 14: ch=BS; break;
		case 28: ch=EN; break;

		case 185: ch=' '; break;
		case 142: ch=BS; break;
		case 156: ch=EN; break;

		case 59: ch=F1;	break;
		case 60: ch=F2;	break;
		case 61: ch=F3;	break;
		case 62: ch=F4;	break;
		case 63: ch=F5;	break;
		case 64: ch=F6;	break;
		case 65: ch=F7;	break;
		case 66: ch=F8;	break;
		case 67: ch=F9;	break;
		case 68: ch=F10; break;


		case 13: ch='='; break;
		case 26: ch='['; break;
		case 27: ch=']'; break;
		case 15: ch=TAB; break;
		case 122: ch='/'; break;
		case 43: ch='\\'; break;
		case 53: ch='/'; break;

		case 'H': ch=UP; break;
		case 'P': ch=DOWN; break;
		case 'K': ch=LEFT; break;
		case 'M': ch=RIGHT; break;


		default: ; break;
		}
	else
		switch (sc) { // We got SHIFT
		case 16: ch='A'; break;
		case 17: ch='Z'; break;
		case 18: ch='E'; break;
		case 19: ch='R'; break;
		case 20: ch='T'; break;
		case 21: ch='Y'; break;
		case 22: ch='U'; break;
		case 23: ch='I'; break;
		case 24: ch='O'; break;
		case 25: ch='P'; break;
		case 30: ch='Q'; break;
		case 31: ch='S'; break;
		case 32: ch='D'; break;
		case 33: ch='F'; break;
		case 34: ch='G'; break;
		case 35: ch='H'; break;
		case 36: ch='J'; break;
		case 37: ch='K'; break;
		case 38: ch='L'; break;
		case 39: ch='M'; break;
		case 44: ch='W'; break;
		case 45: ch='X'; break;
		case 46: ch='C'; break;
		case 47: ch='V'; break;
		case 48: ch='B'; break;
		case 49: ch='N'; break;

		case 2: ch='!'; break;
		case 3: ch='@'; break;
		case 4: ch='#'; break;
		case 5: ch='$'; break;
		case 6: ch='%'; break;
		case 7: ch='^'; break;
		case 8: ch='&'; break;
		case 9: ch='*'; break;
		case 10: ch='('; break;
		case 11: ch=')'; break;
		case 57: ch=' '; break;
		case 14: ch=BS; break;
		case 28: ch=EN; break;

		case 185: ch=' '; break;
		case 142: ch=BS; break;
		case 156: ch=EN; break;

		case 59: ch=F1;	break;
		case 60: ch=F2;	break;
		case 61: ch=F3;	break;
		case 62: ch=F4;	break;
		case 63: ch=F5;	break;
		case 64: ch=F6;	break;
		case 65: ch=F7;	break;
		case 66: ch=F8;	break;
		case 67: ch=F9;	break;
		case 68: ch=F10; break;


		case 13: ch='+'; break;
		case 26: ch='{'; break;
		case 27: ch='}'; break;
		case 15: ch=TAB; break;
		case 122: ch='/'; break;
		case 43: ch='|'; break;
		case 50: ch='?'; break;

		default: ch=0; break;
		}

	return ch;
}

void set_leds(void) {
	ecrireOctet(0x60, 0xED);
}

/* this is called by irq1 in irq.asm */
void handler_clavier(int irq) {
	int c = lireOctet(0x60);
	int cc;
	static int show_all = 0;
	static int doit = 0;


	if(c == 1)/* 1 = ESC */
		show_all = !show_all;
	if(c == 60)/* 60 = F2 */
		doit = !doit;
	if(c == 67)/* 67 - F9 */
		if(doit)
			if (show_all);
	if (c == 58) {
		leds = leds ^ CAPS;
		set_leds();
	}
	else
		if(c == 69) {/* num lock */
			leds = leds ^ NUM;
			set_leds();
		}
		else
			if (c == 70) {/* scroll lock */
				leds = leds ^ SCROLL;
				set_leds();
			}
	switch (c) {
	case 0x2a:
		ControlKeys |= (KBD_SHIFT | KBD_LEFTSHIFT);
		break;
	case 0x36:
		ControlKeys |= (KBD_SHIFT | KBD_RIGHTSHIFT);
		break;
	case 0xaa:
		ControlKeys &= ~KBD_LEFTSHIFT;
		if(!(ControlKeys & KBD_RIGHTSHIFT))
			ControlKeys &= ~KBD_SHIFT;
		break;
	case 0xb6:
		ControlKeys &= ~KBD_RIGHTSHIFT;
		if(!(ControlKeys & KBD_LEFTSHIFT))
			ControlKeys &= ~KBD_SHIFT;
		break;
	}
	if(c < 0x80) {
		if(c=='\n')
			c='\n';
		cc = writechar(c);
		switch(cc) {

		case EN:
			if ((TAILLE_BUF_CLAVIER-semaphoreClavier->Valeur())==0) {
				// Le buffer est plein
				// On Žcrase le dernier caract�re
				// On incremente par posbuf
				modifBuf = false;
				if (posBuf==0) buf[TAILLE_BUF_CLAVIER-1]='\n';
				else buf[posBuf-1]='\n';
				break;
			}
			modifBuf = true;
			buf[posBuf]='\n';
			if(posBuf<TAILLE_BUF_CLAVIER-1)
				posBuf++;
			else posBuf=0;
			break;
		case TAB:
			break;
		case 0: break;
		case F1:
			console=0;
			ecranP->setEcran(0);
			break;
		case F2:
			console=1;
			ecranP->setEcran(1);
			break;
		case F3:
			console=2;
					ecranP->setEcran(2);
					break;
				case F4:
					console=3;
					ecranP->setEcran(3);
					break;
				case F5:
					console=4;
					ecranP->setEcran(4);
					break;
				case F6:
					console=5;
					ecranP->setEcran(5);
					break;
				case F7:
					console=6;
					ecranP->setEcran(6);
					break;
				case F8:
					console=7;
					ecranP->setEcran(7);
					break;
				case F9:
					console=8;
					ecranP->setEcran(8);
					break;
				case F10:
					console=9;
					ecranP->setEcran(9);
					break;

		default:
			if ((TAILLE_BUF_CLAVIER-semaphoreClavier->Valeur())==0) {
				// Le buffer est plein
				// On Žcrase le dernier caract�re
				// On incremente par posbuf
				modifBuf = false;
				if (posBuf==0) buf[TAILLE_BUF_CLAVIER-1]=cc;
				else buf[posBuf-1]=cc;
				break;
			}
			buf[posBuf]=cc;
			modifBuf = true;
			if(posBuf<(TAILLE_BUF_CLAVIER-1))
				posBuf++;
			else posBuf=0;
			break;
		}
	}
	if (modifBuf==true) {
		//ecranV[5].miniprintf("Console %d Car %c Sem %d\n",console,buf[posBuf-1],semaphoreClavier.Valeur());
		semaphoreClavier->V();modifBuf=false;};
}

void clavier_install() {
	semaphoreClavier = new Semaphore();
	irq_set_routine(IRQ_KEYBOARD, handler_clavier);
}
