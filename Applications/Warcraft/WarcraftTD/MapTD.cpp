#include "MapTD.h"




MapTD::MapTD(EcranV *ecr):ecr(ecr),nombreEnnemi(0),nombreTours(0){
	fabrique=new FabriqueDennemi();
	ecr->afficherMot("\nChargement");
	initialiserChemin(0);
	initialiserMap();
}

void MapTD::initialiserChemin(int n){
	int k=0;
	if(n==0){
		for(int i=0;i<51;i++) {
			che[k]= new Position(5,i);
			k++;
		}
		for(int i=1;i<16;i++) {
			che[k]= new Position(5+i,50);
			k++;
		}
		for(int i=1;i<30;i++) {
			che[k]= new Position(20,50-i);
			k++;
		}
	}
	tailleChemin=k;
}

void MapTD::initialiserMap(){
	for(int i=0;i<H;i++){
		for (int j=0;j<L;j++){
			ecr->afficherCaractere(i,j,VERT_LEGER,VERT,TERRAIN);
		}
	}
	for(int i=0;i<tailleChemin;i++){
		ecr->afficherCaractere(che[i]->x,che[i]->y,MARRON,MARRON,CHEMIN);
	}
}



int MapTD::gererLesEnnemi(){
	int vainqueur=0;
	bool a=fabrique->round();
	//on fait avancer les ennemis
	for(int i=0;i<nombreEnnemi;i++){
		if(position[i]>out&&a){
			delete ennemi[i];
			ennemi[i]=fabrique->getEnnemi();
			position[i]=0;
			a=false;
		}
		else if(position[i]==tailleChemin) {
			vainqueur++;
			position[i]=out;
		}
		else if(ennemi[i]->round()){
			position[i]++;
		}
	}
	if(a){
		ennemi[nombreEnnemi]=fabrique->getEnnemi();
		position[nombreEnnemi++]=0;
	}
	//on affiche le chemin
	for(int i=0;i<tailleChemin;i++){
		if (contientEnnemi(i)) ecr->afficherCaractere(che[i]->x,che[i]->y,JAUNE,MARRON,ENNEMI);
		else ecr->afficherCaractere(che[i]->x,che[i]->y,MARRON,MARRON,CHEMIN);
	}
	return vainqueur;
}

bool MapTD::contientEnnemi(int n){
	int i=0;
	bool a=false;
	while(i<nombreEnnemi&&!a){
		a=position[i++]==n;
	}
	return a;
}

int MapTD::gererLesTours(){
	int k=0;
	for(int i=0;i<nombreTours;i++){
		if(tours[i]->round()){
			if(tours[i]->caractere!='z'&&attaquer(tours[i],positionsTours[i])) k++;
			else k+= attaquerZone(tours[i],positionsTours[i]);
		}
	}
	return k*5;
}
bool MapTD::estDansLeTableau(int x,int y){
	for(int i=0;i<tailleChemin;i++){
		if(che[i]->x==x && che[i]->y==y){
			return true;
		}
	}
	return false;
}

int MapTD::construireTour(char c,int x,int y, int gold){
	Tour *t = new Tour(c, x, y);
	if(gold>=t->cout && getInfo(x,y)==0 && !estDansLeTableau(y, x)){
		ecr->afficherCaractere(y, x,BLEU,VERT,(char) t->logo);
		tours[nombreTours]=t;
		positionsTours[nombreTours++]=new Position(y,x);
		return t->cout;
	}
	return 0;
}

bool MapTD::attaquer(Tour *tour,Position *p){
	int po=tour->getPortee();
	int k=H*L;
	for (int i=0;i<tailleChemin;i++){
		if(abs(p->x-che[i]->x)+abs(p->y-che[i]->y)<=po){
			if(contientEnnemi(i)){
				k=i;
			}
		}
	}
	int j=-1;
	bool c=k==H*L;
	while(!c){
		c=position[++j]==k;
	}
	if(j==-1) return false;
	else {
		bool boubou = ennemi[j]->subirAttaque(tour->attaquer());
		if(boubou)
			position[j]=out;
		return boubou;
	}
}

int MapTD::attaquerZone(Tour *tour,Position *p){
	int po=tour->getPortee();
	int collateraux = 0;
	int k=H*L;
	for (int i=0;i<tailleChemin;i++){
		if(abs(p->x-che[i]->x)+abs(p->y-che[i]->y)<=po){
			if(contientEnnemi(i)){
				k=i;
				int j=-1;
				bool c=k==H*L;
				while(!c){
					c=position[++j]==k;
				}
				if(j==-1) 42;
				else {
					bool boubou = ennemi[j]->subirAttaque(tour->attaquer());
					if(boubou){
						position[j]=out;
						collateraux++;
					}
				}
			}
		}
	}

	return collateraux;
}

Tour *MapTD::getInfo(int x,int y){
	for(int i=0;i<nombreTours;i++){
		if(positionsTours[i]->y==x && positionsTours[i]->x==y){
			return tours[i];
		}
	}
	return 0;
}

int MapTD::abs(int x){
	if(x<0) return -x;
	else return x;
}








