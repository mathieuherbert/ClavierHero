#include "EcranPMF.h"
#include <sextant/interruptions/handler/handler_clavier.h>
#include "Souris.h"
#include <sextant/memoire/op_memoire.h>
// Ici nous allons manipuler un tableau ecran dont on fixe l'origine au début de la zone mémoire video.

volatile caseEcran* EcranPMF::origine = (volatile caseEcran*)VIDEO;


extern Souris mouse;
EcranPMF::EcranPMF(EcranV *lecran){
//	ecran = ecr;
	origine=(caseEcran*)lecran;
	nombreFenetres=2;
	//ecranActif = *ecran;
	//ecranActif = &(ecran[0]);
	tabEcran[1]=new EcranVMF();
	tabEcran[1]->origine=20;
	tabEcran[1]->miniprintf("Fenetre 1");
	tabEcran[2]=new EcranVMF();
	tabEcran[2]->origine=520;
	tabEcran[2]->miniprintf("Fenetre 2");
	ecranActif=tabEcran[nombreFenetres];
	for(int i=0;i<LIGNES*COLONNES;i++){
		vide[i].caractere=0;
		//vide[i].couleurs=ecranActif->arrierePlan;
		vide[i].couleurs=ROUGE;

	}
	tabEcran[0]=new EcranVMF();
	tabEcran[0]->taille_x=COLONNES;
	tabEcran[0]->taille_y=LIGNES;
	tabEcran[0]->effacerEcranV(NOIR);
	memcpy((void*)(tabEcran[0]->tab),
			(void*)(&vide),
			LIGNES*COLONNES*sizeof(caseEcran));

//	mouse.initialiser(tabEcran[0]);
	setEcran(nombreFenetres);
}

void EcranPMF::ouvrirFenetre(){
	if(nombreFenetres<MAXECRAN){
		nombreFenetres++;
		tabEcran[nombreFenetres]=new EcranVMF();
		setEcran(nombreFenetres);
	}

}

void EcranPMF::fermerFenetre(){
	if(nombreFenetres>0){
		nombreFenetres--;
		setEcran(nombreFenetres);
	}
}

//EcranV Ecran::getEcran(){
//return ecranActif;
//}
EcranVMF* EcranPMF::getEcransV(){
	return tabEcran[0];
}
void EcranPMF::vider(){
	memcpy((void*)origine, vide, LIGNES*COLONNES*sizeof(caseEcran));
}

void EcranPMF::setEcran(int index){
	//vider();
	//ecranActif=&(ecran[index]);
	setFenetre(0);
	if(index==0) return;
	EcranVMF* temp=tabEcran[index];
	for(int i=0;i<nombreFenetres+1;i++){
		if(i>=index){
			tabEcran[i]=tabEcran[i+1];
		}

	}
	tabEcran[nombreFenetres]=temp;
	ecranActif=tabEcran[nombreFenetres];
	//ecranActif->taille_x=(ecranActif->taille_x+10);
	//ecranActif=ecran[index];
	setFenetre(index);


	//memcpy((void*)origine, ecranActif->tab, LIGNES*COLONNES*sizeof(caseEcran));
	//memcpy((void*)origine, ecranActif->tab, ecranActif->taille_x*ecranActif->taille_y*sizeof(caseEcran));
}

void EcranPMF::setFenetre(int index){
	vider();
	//ecranActif=&(ecran[index]);
	//ecranActif=ecran[index];
	/*
	for(int i=0; i<=ecranActif->taille_y; i++){
		memcpy((void*)(origine+ecranActif->origine+i*COLONNES),
				(void*)(&ecranActif->tab[i*COLONNES]),
				ecranActif->taille_x*sizeof(caseEcran));
	}
	 */

	for(int j=0;j<nombreFenetres+1;j++){
		for(int i=0; i<=tabEcran[j]->taille_y; i++){
			if(tabEcran[j]->origine%COLONNES+tabEcran[j]->taille_x > COLONNES){
				int charACopier = COLONNES-tabEcran[j]->origine%COLONNES;
				memcpy((void*)(origine+tabEcran[j]->origine+i*COLONNES),
						(void*)(&tabEcran[j]->tab[i*COLONNES]),
						charACopier*sizeof(caseEcran));
			}else{
				memcpy((void*)(origine+tabEcran[j]->origine+i*COLONNES),
						(void*)(&tabEcran[j]->tab[i*COLONNES]),
						tabEcran[j]->taille_x*sizeof(caseEcran));
			}

		}
	}
	memcpy((void*)(origine+mouse.x+mouse.y*COLONNES),
			(void*)(&tabEcran[0]->tab[mouse.x+mouse.y*COLONNES]),
			sizeof(caseEcran));


}

void EcranPMF::deplacerBas(){

	//ecranActif->effacerEcranV(NOIR);
	int numeroColonne=ecranActif->origine%COLONNES;

	int pseudoOrigine = (ecranActif->origine-numeroColonne)/COLONNES;
	//ecranActif->afficherChiffre(pseudoOrigine);
	if(pseudoOrigine+ecranActif->taille_y < LIGNES){
		ecranActif->origine=ecranActif->origine+COLONNES;
		setFenetre(nombreFenetres);
	}

}

void EcranPMF::deplacerHaut(){

	//ecranActif->effacerEcranV(NOIR);
	int numeroColonne=ecranActif->origine%COLONNES;

	int pseudoOrigine = (ecranActif->origine-numeroColonne)/COLONNES;
	//ecranActif->afficherChiffre(pseudoOrigine);
	if(pseudoOrigine > 0){
		ecranActif->origine=ecranActif->origine-COLONNES;
		setFenetre(nombreFenetres);
	}

}

void EcranPMF::deplacerGauche(){
	//ecranActif->effacerEcranV(NOIR);
	int pseudoOrigine = ecranActif->origine%COLONNES;
	//ecranActif->afficherChiffre(pseudoOrigine);
	if(pseudoOrigine > 0){
		ecranActif->origine=ecranActif->origine-1;
		setFenetre(nombreFenetres);
	}


}

void EcranPMF::deplacerDroite(){
	int pseudoOrigine = ecranActif->origine%COLONNES;
	pseudoOrigine = pseudoOrigine + ecranActif->taille_x;
	//ecranActif->effacerEcranV(NOIR);
	//ecranActif->afficherChiffre(pseudoOrigine);
	if(pseudoOrigine<COLONNES){
		ecranActif->origine=ecranActif->origine+1;
		setFenetre(nombreFenetres);
	}

}

void EcranPMF::ecrire(char c){
	ecranActif->afficherCaractere(BLANC,ecranActif->arrierePlan,c);
	setFenetre(nombreFenetres);
}

void EcranPMF::start(){
	int buffer[256]; //char
	int  i;
	char *src;
// JMM : LE CLAVIER DOITE ETRE GERER AILLEUR : handler_clavier.cpp

	/*while(true) {
		if(clavier->testChar()) {

			src=clavier->getString();

			for(i=0;i<256-1 && src[i]!='\0';i++)
				buffer[i]=src[i];
			buffer[i]='\0';

			for(i=0;buffer[i]!='\0';i++)
				switch(buffer[i]){

				case K16:
					ecranActif->origine=ecranActif->origine+1;
					break;
				case K17:
					ecranActif->origine=ecranActif->origine-1;
					break;
				case F1:
					setEcran(0);
					break;
				case F2:
					ecranActif->origine=(ecranActif->origine+10);
					ecranActif->miniprintf("Totot");
					setEcran(0);
					break;
				case F3:
					setFenetre(0);
					break;
				case F4:
					setFenetre(1);
					break;
				case F5:
					setEcran(4);
					break;
				case F6:
					setEcran(5);
					break;
				case F7:
					setEcran(6);
					break;
				case F8:
					setEcran(7);
					break;
				case F9:
					setEcran(8);
					break;
				case F10:
					setEcran(9);
					break;
				}
		}
	}*/
}




