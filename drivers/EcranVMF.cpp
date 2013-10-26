/*
 * EcranV.cpp
 *
 *  Created on: 17 oct. 2008
 *      Author: Claire
 */

#include "EcranVMF.h"
#include <sextant/stdargs.h>


// Ici nous allons manipuler un tableau EcranV dont on fixe l'tab au debut de la zone memoire video.

EcranVMF::EcranVMF() {
	taille_x=30;
	taille_y=10;
	origine=0;

	effacerEcranV(NOIR);
};

unsigned char EcranVMF::coderCouleur(Couleur c) {
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

unsigned char EcranVMF::coderAttribut(Couleur prPlan, Couleur arPlan,int clign) {
	unsigned char paramClignotement ;

	if (clign== CLIGN_OUI) paramClignotement=1; else paramClignotement=0;

	unsigned char codePremierPlan = coderCouleur(prPlan);
	unsigned char codeArrierePlan = coderCouleur(arPlan);
	return ( codePremierPlan | (codeArrierePlan << 4) | (paramClignotement << 7));
}

unsigned char EcranVMF::coderAttribut(Couleur prPlan, Couleur arPlan) {
	unsigned char paramClignotement = 0 ;

	unsigned char codePremierPlan = coderCouleur(prPlan);
	unsigned char codeArrierePlan = coderCouleur(arPlan);
	return ( codePremierPlan | (codeArrierePlan << 4) | (paramClignotement << 7));
}

// Les accesseurs

int EcranVMF::getLigne(){
	return ligne;
}

int EcranVMF::getColonne(){
	return colonne;
}

void EcranVMF::getCase(caseEcran *C,int l,int c){
	int position = l* COLONNES + c;
	C->caractere=tab[position].caractere;
	C->couleurs=tab[position].couleurs;
}

void EcranVMF::setLigne(int i){
	ligne=i;
}

void EcranVMF::setColonne(int i){
	colonne=i;
}

int EcranVMF::positionCourrante(){
	return getLigne() * COLONNES + getColonne();
}

void EcranVMF::avancerPositionCourrante(){
	int c = getColonne();
	int l = getLigne();
	c=c+1;
	if(c >=COLONNES){//hors de l'ecran, trop e droite
		c = 0;
		l++;
		if(l>=LIGNES){//hors de l'ecran, trop bas
			defilement(1);
			l--;
		}
	}
	setColonne(c);
	setLigne(l);
}

void EcranVMF::sautDeLigne(){
	int c = getColonne();
	int l = getLigne();

	c=0;
	l=l+1;

	if(l>=LIGNES){//hors de l'ecran, trop bas
		defilement(1);
		l--;
	}
	setColonne(c);
	setLigne(l);
}

// Partie fonctionnelle



// Efface l'EcranV avec pour couleur de fond arPlan

void EcranVMF::effacerEcranV(Couleur arPlan) {
	arrierePlan = arPlan;
	unsigned char attribut = coderAttribut(arrierePlan, arrierePlan);
	for(int i = 0 ; i < LIGNES*COLONNES ; i++){
		tab[i].caractere = 0;
		tab[i].couleurs = attribut;
		setLigne(0);
		setColonne(0);
	}
	for(int i=0;i<taille_y;i++){
		setLigne(i);
		setColonne(0);
		afficherCaractere(BLANC,NOIR,179);
		setColonne(taille_x-1);
		afficherCaractere(BLANC,NOIR,179);
	}
	for(int i=0;i<taille_x;i++){
		setLigne(0);
		setColonne(i);
		if (i==0) afficherCaractere(BLANC,NOIR,213);
		if (i==taille_x-1) afficherCaractere(BLANC,NOIR,184);
		else afficherCaractere(BLANC,NOIR,205);
		setColonne(i);
		setLigne(taille_y-1);
		if (i==0) afficherCaractere(BLANC,NOIR,212);
		if (i==taille_x-1) afficherCaractere(BLANC,NOIR,190);
		else afficherCaractere(BLANC,NOIR,205);
		setLigne(1);
		setColonne(i);
		if (i==0) afficherCaractere(BLANC,NOIR,198);
		if (i==taille_x-1)afficherCaractere(BLANC,NOIR,181);
		else afficherCaractere(BLANC,NOIR,205);
	}
	setLigne(0);
	setColonne(taille_x-4);
	afficherCaractere(ROUGE,NOIR,'_');
	afficherCaractere(ROUGE,NOIR,'O');
	afficherCaractere(ROUGE,NOIR,'X');
	setLigne(1);
	setColonne(1);

}

void EcranVMF::ecrireBord() {
	for(int i=0;i<taille_y;i++){
		setLigne(i);
		setColonne(0);
		afficherCaractere(BLANC,NOIR,'|');
		setColonne(taille_x-1);
		afficherCaractere(VERT,NOIR,'|');
	}
	for(int i=0;i<taille_x;i++){
		setLigne(0);
		setColonne(i);
		afficherCaractere(JAUNE,NOIR,'|');
		setColonne(i);
		setLigne(taille_y-1);
		afficherCaractere(ROUGE,NOIR,'|');
		setLigne(1);
		setColonne(i);
		afficherCaractere(JAUNE,NOIR,'|');
	}
	setLigne(0);
	setColonne(taille_x-3);
	afficherCaractere(ROUGE,NOIR,'_');
	afficherCaractere(ROUGE,NOIR,'O');
	afficherCaractere(ROUGE,NOIR,'X');
	setLigne(1);
	setColonne(1);
}

void EcranVMF::effacerBord() {
	for(int i=0;i<taille_y;i++){
		setLigne(i);
		setColonne(0);
		afficherCaractere(BLANC,NOIR,0);
		setColonne(taille_x-1);
		afficherCaractere(VERT,NOIR,0);
	}
	for(int i=0;i<taille_x;i++){
		setLigne(0);
		setColonne(i);
		afficherCaractere(JAUNE,NOIR,0);
		setColonne(i);
		setLigne(taille_y-1);
		afficherCaractere(ROUGE,NOIR,0);
		setLigne(1);
		setColonne(i);
		afficherCaractere(JAUNE,NOIR,0);
	}
	setLigne(0);
	setColonne(taille_x-3);
	afficherCaractere(ROUGE,NOIR,0);
	afficherCaractere(ROUGE,NOIR,0);
	afficherCaractere(ROUGE,NOIR,0);
	setLigne(1);
	setColonne(1);
}

// Affiche un Caractere a la position courrante



void EcranVMF::afficherCaractere(Couleur prPlan,Couleur arPlan,const char caractere) {

	afficherCaractere(getLigne(),getColonne(), prPlan, arPlan, caractere);
	avancerPositionCourrante();
}

// Affiche un Caractere a la position donnee en parametre (l,c)

void EcranVMF::afficherCaractere(int l,int c,Couleur prPlan,Couleur arPlan,const char caractere) {
	unsigned char attribut = coderAttribut(prPlan, arPlan);

	//Si en dehors de l'ecran, ne rien faire
	if ((c >=COLONNES) || (l >= LIGNES)) return;

	int position = l * COLONNES + c; // position lineaire relative

	tab[position].caractere = caractere;
	tab[position].couleurs = attribut;
}

// Affiche une chaine de caractere a la position courante

void EcranVMF::afficherMot(int l,int c,const char *mot,Couleur prPlan) {

	setLigne(l);
	setColonne(c);
	afficherMot(mot,prPlan);
}

void EcranVMF::afficherMot(const char *mot,Couleur prPlan) {
	int i=0;

	while(mot[i]!='\0'){ // '\0' : caractere de fin
		if(mot[i] == '\n'){ // '\n' : passage e la ligne
			sautDeLigne();
		}else
			afficherCaractere(prPlan,arrierePlan, mot[i]);
		i++;
	}
	//afficherCurseur();
}

// Affiche le curseur (mais la postion courante ne change pas)

void EcranVMF::afficherCurseur(){
	int position = positionCourrante();

	unsigned char attribut = coderAttribut(BLANC, arrierePlan,CLIGN_OUI);
	tab[position].caractere = CURSEUR;
	tab[position].couleurs = attribut;

}

// gere le defilement de nline d'un coup. les nouvelles lignes ont pour fond la couler de fond courante

void EcranVMF::defilement(int nline) {
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

/* @return : appelee lors d'un clic retourne 1 si la souris est dans la fenetre, 0 sinon
 * @param : la position de la souris en x et en y
 */
bool EcranVMF::curseurDedans(int x, int y){
	//coordonnees en x et en y de l'origine de la fenetre
	int origine_x = origine%COLONNES;
	int origine_y = origine/COLONNES;

	//test pour savoir si le curseur est dans la fenetre
	if((x >= origine_x)&&(x  <= origine_x+taille_x)){
		if((y >= origine_y)&&(y <= origine_y+taille_y )){
			return true;
		}
	}
	return false;
}

bool EcranVMF::surCoinInfDroit(int x, int y){
	//coordonnees en x et en y de l'origine du petit carre en bas e droite de la fenetre
	int origineCarre_x = origine%COLONNES + taille_x - 3;
	int origineCarre_y = origine/COLONNES + taille_y - 3;


	//test pour savoir si le curseur est dans le coin inferieur droit de la fenetre
	if((x >= origineCarre_x)&&(x  <= origineCarre_x+3)){
		if((y >= origineCarre_y)&&(y <= origineCarre_y+3 )){
			return true;
		}
	}
	return false;
}

// Méthode qui nous aurait servi pour le déplacement des fenêtre si nous avions pu gérer le drag and drop
bool EcranVMF::surBarreDefilement(int x, int y){
	//coordonnees en x et en y de l'origine de la fenetre
	int origine_x = origine%80 ;
	int origine_y = origine/80 ;


	//test pour savoir si le curseur est dans la barre de defilement
	if((x >= origine_x )&&(x  <= origine_x + taille_x)){
		if((y >= origine_y)&&(y <= origine_y + 1)){
			return true;
		}
	}
	return false;
}

//Déplacement avec la méthode du clic droit
void EcranVMF::deplacement(int x, int y){

		int origineCarre_x = origine%COLONNES + taille_x ;
		int origineCarre_y = origine/COLONNES + taille_y ;

		/*   zone 6    	|zone 4
		 * 	___________	|__________________
		 *  			@@@@@@@@@
		 *   zone 5     @       @ zone 2
		 * 	            @@@@@@@@@__________
		 *              |       |
		 *              |zone1  |    zone 3
		 * 				|       |
		 *
		 *
		 * Bien que nous aurions pu déplacer la fenêtre vers un point présent dans la fenêtre
		 * nous avons préférer bloquer cette zone pour tout autre besoin du clic droit dans la fenetre
		 */

		//Détermination des zones
		bool Un, Deux, Trois, Quatre, Cinq, Six ;

		Un = (x<origineCarre_x)&&(x>(origineCarre_x-taille_x))&&(y>(origineCarre_y));
		Deux = (origineCarre_y>y)&&(y>(origineCarre_y-taille_y))&&(x>(origineCarre_x));
		Trois = (x>(origineCarre_x))&&(y>(origineCarre_y));
		Quatre = (x>origineCarre_x-taille_x)&&(y<(origineCarre_y-taille_y));
		Cinq = (y>(origineCarre_y-taille_y))&&(x<(origineCarre_x-taille_x));
		Six = ((y<(origineCarre_y-taille_y))&&(x<(origineCarre_x-taille_x)));

		// Quelle que soit la zone, on déplace la fenêtre
		if(Un||Deux||Trois||Quatre||Cinq||Six){

				int origine_x = origine%80 ;
				int origine_y = origine/80 ;

				origine_x = x;
				origine_y = y;

				origine = 80*origine_y + origine_x;
		}


}


//Redimensionnement avec le clic gauche
void EcranVMF::redimensionner(int x, int y){

	effacerBord();

	int origineCarre_x = origine%COLONNES + taille_x ;
	int origineCarre_y = origine/COLONNES + taille_y ;

	/*          	|zone 4
	 * 	___________	|__________________
	 *  			@@@@@@@@@
	 *   zone 5     @       @ zone 2
	 * 	            @@@@@@@@@__________
	 *              |       |
	 *              |zone1  |    zone 3
	 * 				|       |
	 *
	 * Zones 1, 2, 3 : on touche a x et y
	 * Zones 4 et 5 : on touche seulement (resp.) a x ou a y
	 *
	 */

	// On va tenter de rendre le code un peu lisible...
	bool Un, Deux, Trois, Quatre, Cinq ;

	Un = (x<origineCarre_x)&&(x>(origineCarre_x-taille_x))&&(y>(origineCarre_y));
	Deux = (origineCarre_y>y)&&(y>(origineCarre_y-taille_y))&&(x>(origineCarre_x));
	Trois = (x>(origineCarre_x))&&(y>(origineCarre_y));
	Quatre = (x>origineCarre_x-taille_x)&&(y<(origineCarre_y-taille_y));
	Cinq = (y>(origineCarre_y-taille_y))&&(x<(origineCarre_x-taille_x));

	// Si on est dans l'une des zones 1, 2, 3,4 on redimensionne x
	if(Un||Deux||Trois||Quatre){

		//On veut empêcher la fenetre d etre trop petite, alors on
		// la maintient a plus de 8 en largeur
		if(taille_x+x-origineCarre_x > 8){
			taille_x=taille_x+x-origineCarre_x;
		}
	}

	// Si on clique en zone 1,2,3,5 on change y
	if(Un||Deux||Trois||Cinq) {
		taille_y=taille_y+y-origineCarre_y;
	}


	ecrireBord();
}

void EcranVMF::afficherChiffre(int l,int c, const int valeur){
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

	// ajout du signe si valeur est negative
	if (valeur<0){
		chaine[count]='-';
		count=count+1;
	}

	for(i = 0, j=count-1 ; i< count ;i++, j--){
		resultat[j]=chaine[i];
	}

	// ajout du caractere de fin de chaine */
	resultat[count]='\0';

	afficherMot(l,c,resultat, BLANC);
}


void EcranVMF::afficherChiffre( const int valeur){
	afficherChiffre(getLigne(),getColonne(), valeur);

}

void EcranVMF::afficherBase(unsigned int entier,int base,Couleur prPlan) {
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

void EcranVMF::miniprintf(char *fmt, ...) {
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

