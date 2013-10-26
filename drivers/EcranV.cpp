/*
 * EcranV.cpp
 *
 *  Created on: 17 oct. 2008
 *      Author: Claire
 */

#include "EcranV.h"
#include <sextant/stdargs.h>


// Ici nous allons manipuler un tableau EcranV dont on fixe l'tab au début de la zone mémoire video.

EcranV::EcranV() {effacerEcranV(NOIR);};

unsigned char EcranV::coderCouleur(Couleur c) {
	unsigned char r;
	switch(c){
	case NOIR:
		r = 0;
		break;
	case GRIS_SOMBRE:
		r = 8;
		break;
	case BLEU:
		r = 1;
		break;
	case BLEU_LEGER:
		r = 9;
		break;
	case VERT:
		r = 2;
		break;
	case VERT_LEGER:
		r = 10;
		break;
	case CYAN:
		r = 3;
		break;
	case CYAN_LEGER:
		r = 11;
		break;
	case ROUGE:
		r = 4;
		break;
	case ROUGE_LEGER:
		r = 12;
		break;
	case MAGENTA:
		r = 5;
		break;
	case MAGENTA_LEGER:
		r = 13;
		break;
	case MARRON:
		r = 6;
		break;
	case JAUNE:
		r = 14;
		break;
	case GRIS_LEGER:
		r = 7;
		break;
	case BLANC:
		r = 15;
		break;
	}
	return r;
}

unsigned char EcranV::coderAttribut(Couleur prPlan, Couleur arPlan,int clign) {
	unsigned char paramClignotement ;

	if (clign== CLIGN_OUI) paramClignotement=1; else paramClignotement=0;

	unsigned char codePremierPlan = coderCouleur(prPlan);
	unsigned char codeArrierePlan = coderCouleur(arPlan);
	return ( codePremierPlan | (codeArrierePlan << 4) | (paramClignotement << 7));
}

unsigned char EcranV::coderAttribut(Couleur prPlan, Couleur arPlan) {
	unsigned char paramClignotement = 0 ;

	unsigned char codePremierPlan = coderCouleur(prPlan);
	unsigned char codeArrierePlan = coderCouleur(arPlan);
	return ( codePremierPlan | (codeArrierePlan << 4) | (paramClignotement << 7));
}

// Les accesseurs

int EcranV::getLigne(){
	return ligne;
}

int EcranV::getColonne(){
	return colonne;
}

void EcranV::getCase(caseEcran *C,int l,int c){
	int position = l* COLONNES + c;
	C->caractere=tab[position].caractere;
	C->couleurs=tab[position].couleurs;
}

void EcranV::setLigne(int i){
	ligne=i;
}

void EcranV::setColonne(int i){
	colonne=i;
}

int EcranV::positionCourrante(){
	return getLigne() * COLONNES + getColonne();
}

void EcranV::avancerPositionCourrante(){
	int c = getColonne();
	int l = getLigne();
	c=c+1;
	if(c >=COLONNES){//hors de l'écran, trop à  droite
		c = 0;
		l++;
		if(l>=LIGNES){//hors de l'écran, trop bas
			defilement(1);
			l--;
		}
	}
	setColonne(c);
	setLigne(l);
}
// Recule la position courante
void EcranV::reculerPositionCourante() {
	int c = getColonne();
	int l = getLigne();
	c=c-1;
	if(c < 0){//hors de l'écran, trop à gauche
		c = COLONNES-1;
		l--;
		if(l<0){//hors de l'écran, trop haut
			defilement(-1);
			l++;
		}
	}
	setColonne(c);
	setLigne(l);
}

void EcranV::sautDeLigne(){
	int c = getColonne();
	int l = getLigne();

	c=0;
	l=l+1;

	if(l>=LIGNES){//hors de l'écran, trop bas
		defilement(1);
		l--;
	}
	setColonne(c);
	setLigne(l);
}

// Partie fonctionnelle



// Efface l'EcranV avec pour couleur de fond arPlan

void EcranV::effacerEcranV(Couleur arPlan) {
	arrierePlan = arPlan;
	unsigned char attribut = coderAttribut(arrierePlan, arrierePlan);
	for(int i = 0 ; i < LIGNES*COLONNES ; i++){
		tab[i].caractere = 0;
		tab[i].couleurs = attribut;
		setLigne(0);
		setColonne(0);
	}
}

// Affiche un Caractere a la position courrante



void EcranV::afficherCaractere(Couleur prPlan,Couleur arPlan,const char caractere) {

	afficherCaractere(getLigne(),getColonne(), prPlan, arPlan, caractere);
	avancerPositionCourrante();
}

// Supprime le caractere de la position precedent la position courante
void EcranV::effacerCaractere(){
	afficherCaractere(getLigne(),getColonne()-1, arrierePlan, arrierePlan, 0);
	reculerPositionCourante();
}

// Affiche un Caractere a la position donnée en parametre (l,c)

void EcranV::afficherCaractere(int l,int c,Couleur prPlan,Couleur arPlan,const char caractere) {
	unsigned char attribut = coderAttribut(prPlan, arPlan);

	//Si en dehors de l'écran, ne rien faire
	if ((c >=COLONNES) || (l >= LIGNES) || (c < 0)) return;

	int position = l * COLONNES + c; // position lineaire relative

	tab[position].caractere = caractere;
	tab[position].couleurs = attribut;
}

// Affiche une chaine de caractere a la position courante

void EcranV::afficherMot(int l,int c,const char *mot,Couleur prPlan) {

	setLigne(l);
	setColonne(c);
	afficherMot(mot,prPlan);
}

void EcranV::afficherMot(const char *mot,Couleur prPlan) {
	int i=0;

	while(mot[i]!='\0'){ // '\0' : caractère de fin
		if(mot[i] == '\n'){ // '\n' : passage à  la ligne
			sautDeLigne();
		}else
			afficherCaractere(prPlan,arrierePlan, mot[i]);
		i++;
	}
	//afficherCurseur();
}

// Affiche le curseur (mais la postion courante ne change pas)

void EcranV::afficherCurseur(){
	int position = positionCourrante();

	unsigned char attribut = coderAttribut(BLANC, arrierePlan,CLIGN_OUI);
	tab[position].caractere = CURSEUR;
	tab[position].couleurs = attribut;

}

// gere le défilement de nline d'un coup. les nouvelles lignes ont pour fond la couler de fond courante

void EcranV::defilement(int nline) {
	int i,j;

	for(i=0;i<LIGNES;i++)
		for(j=0;j<COLONNES;j++)
			if(i+nline<LIGNES) {
				tab[(i*COLONNES)+j].caractere = tab[((i + nline)* COLONNES) + j].caractere;
				tab[(i*COLONNES)+j].couleurs = tab[((i + nline)* COLONNES) + j].couleurs;
			}
			else {
				tab[(i*COLONNES)+j].caractere = 0;
				tab[(i*COLONNES)+j].couleurs = arrierePlan;
			}
}


void EcranV::afficherChiffre(int l,int c, const int valeur){
	static const char num[] = {'0','1','2','3','4','5','6','7','8','9'};
	int i,j;
	char resultat[40];
	char chaine[36];
	int reste;
	int count=0;
	int quotient=valeur;

	if(quotient<0) quotient=-quotient;

	chaine[0]='0';

	if(quotient==0) count++;

	while (quotient!=0){
		reste = quotient % 10 ;
		// pour passer chiffre suivant
		quotient = (int) quotient/10;
		// conversion du chiffre en caractere
		chaine[count]=(char) num[reste];
		count=count+1;
	}

	// ajout du signe si valeur est négative
	if (valeur<0){
		chaine[count]='-';
		count=count+1;
	}

	for(i = 0, j=count-1 ; i< count ;i++, j--){
		resultat[j]=chaine[i];
	}

	// ajout du caractère de fin de chaine */
	resultat[count]='\0';

	afficherMot(l,c,resultat, BLANC);
}


void EcranV::afficherChiffre( const int valeur){
	afficherChiffre(getLigne(),getColonne(), valeur);

}

void EcranV::afficherBase(unsigned int entier,int base,Couleur prPlan) {
	int pret[9],compt;
	unsigned int nb;
	if(entier == 0)
		afficherCaractere(ligne,colonne,prPlan,NOIR,48);
	else
		if(entier == 0x0FFFFFF8)
			afficherMot("Fin de cluster\n");
		else
			if(entier > 999999999)
				afficherMot("Entier trop grand\n");
			else {
				for(int i=0;i<9;i++)
					pret[i] = -1;
				for(nb=base,compt=0;entier >= nb; nb*=base,compt++);
				while(compt >= 0){
					nb /= base;
					pret[compt] = entier / nb;
					entier = entier - pret[compt] * nb;
					compt--;
				}
				for(int i=8;i>=0;i--)
					if(pret[i]>=0){
						switch(pret[i]) {
						case 10 :
							afficherCaractere(ligne,colonne,prPlan,NOIR,'a');
							break;
						case 11 :
							afficherCaractere(ligne,colonne,prPlan,NOIR,'b');
							break;
						case 12 :
							afficherCaractere(ligne,colonne,prPlan,NOIR,'c');
							break;
						case 13 :
							afficherCaractere(ligne,colonne,prPlan,NOIR,'d');
							break;
						case 14 :
							afficherCaractere(ligne,colonne,prPlan,NOIR,'e');
							break;
						case 15 :
							afficherCaractere(ligne,colonne,prPlan,NOIR,'f');
							break;
						default :
							afficherCaractere(ligne,colonne,prPlan,NOIR,pret[i]+48);
						}
						colonne=colonne+1;
					}
			}
}

void EcranV::modifierPosition(int l, int c){
	setLigne(l);
	setColonne(c);
}

void EcranV::miniprintf(char *fmt, ...) {
	va_list ap;
	char *p;
	int ival;
	//  double dval;
	char c;
	char *s;

	va_start(ap, fmt);
	for (p = fmt; *p; p++) {
		if (*p != '%') {
			if(*p == '\n')
				sautDeLigne();
			else if(*p == '\t')
				afficherMot("    ");
			else
				afficherCaractere(BLANC,NOIR,*p);
			continue;
		}
		switch (*++p) {
		case 'd':
			ival = va_arg(ap, int);
			afficherChiffre(ival);
			break;
		case 'c' :
			c = va_arg(ap, int);
			afficherCaractere( BLANC,NOIR,c );
			break;
		case 's' :
			s = va_arg(ap, char *);
			for ( ; *s != '\0'; s++ )
				afficherCaractere( BLANC,NOIR,*s );
			break;
		default:
			break;
		}
	}
	va_end(ap);
}
