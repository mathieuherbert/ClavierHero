#include "Souris.h"
#include <sextant/interruptions/handler/mouse_handler.h>
#include <drivers/EcranV.h>

#define ACCELERATION 5

extern signed char mouse_x;        	//signed char
extern signed char mouse_y;        	//signed char
extern signed char mouse_clic;

caseEcran temp;

void Souris::initialiser(EcranV *ecran){

	mouse_install();

	x = COLONNES/2;
	y = LIGNES/2;
	clicG=false;
	clicD=false;
	clicM=false;
	actualiser(ecran);

}
void Souris::actualiser(EcranV *ecran){


	Couleur fond=NOIR;

	if(clicG){
		fond=ROUGE;
	}
	if(clicD){
		fond=VERT;
	}
	if(clicM){
		fond=BLEU;
	}

/*	if((x0!=x)||(y0!=y)){
		ecran->afficherCaractere(y0,x0,(Couleur) temp.couleurs,ecran->arrierePlan,temp.caractere);
		ecran->getCase(&temp,y,x);
	}
*/
	ecran->afficherCaractere(y,x,BLANC,fond,CURSEUR);
}

int abs(int x) {
	if (x<0)
		return -x;
	else x;
}

bool accelaration(int x){
	if (abs(x)>20)
		return true;
	return false;
}

int round(int x){
	if (abs(x)<5) return 0;
	return x;
}
void Souris::bouger(EcranV *ecran){

		x0=x;
		y0=y;
		clicG=false;
		clicD=false;
		clicM=false;

		if(mouse_clic==9){
			clicG=true;
		}
		if(mouse_clic==10){
			clicD=true;
		}
		if(mouse_clic==12){
			clicM=true;
		}

//		if ((clicD)||(clicG)||(clicM)) ecran->miniprintf("CLICK\n");

		if ((mouse_x==0)&&(mouse_y==0)) return;

			bool go = false;
			int acc_x=1;
			int acc_y=1;

		// Deux cas de figure :
		// 	- mouvement lent :
			// pour eviter des mouvements aleatoire de la souris
			// nous demandons a ce que le deplacement soit realise deux fois
			// cela evite que la souris passe de case en case de maniere brutale
			// mais cela empeche de se deplacer rapidement dans la fenetre
		// 	- mouvement rapide :
		//		nous incrementons/decrementons la souris de acc_x

		if ((accelaration(mouse_x)||accelaration(mouse_y))==false) {
			if ((before_mouse_x==mouse_x)&&(before_mouse_y==mouse_y)) {
					go=true;
			}
			acc_x=1;
			acc_y=1;
		}


		if (accelaration(mouse_x)||accelaration(mouse_y)) {
			mouse_x=round(mouse_x);
			mouse_y=round(mouse_y);
			go=true;
			acc_x=abs(mouse_x)/10;
			acc_y=abs(mouse_y)/10;
		}

		if (go)
			{
//			ecran->miniprintf("ancien (%d,%d) nouveau (%d,%d)\n",before_mouse_x,before_mouse_y,mouse_x,mouse_y);

				if((mouse_x<0)&&(!(x-1<0))){
					x=x-acc_x;
					if (x<0) x=0;
				}

				if((mouse_x>0)&&(!(x+1>=COLONNES))){
					x=x+acc_x;
					if (x>COLONNES) x=COLONNES;
				}

				if((mouse_y<0)&&(!(y+1>=LIGNES))){
					y=y+acc_y;
					if (y>LIGNES) y=LIGNES;
				}
				if((mouse_y>0)&&(!(y-1<0))){
					y=y-acc_y;
					if (y<0) y=0;
				}


			}



		before_mouse_x=mouse_x;
		before_mouse_y=mouse_y;

		mouse_x=0;
		mouse_y=0;

//	actualiser(ecran);

}

