#ifndef PILE_H_
#define PILE_H_


template <class T>
struct ItemListe{

	T* item;
	struct ItemListe* precedent;
	struct ItemListe* suivant;
};

template <class T>
class ListeDouble{

private:
	ItemListe<T>* debut;
	ItemListe<T>* fin;
	ItemListe<T>* actuel;

	int longueur;

public:
	ListeDouble();

	bool ajouterDebut(T& nouveau);
	bool ajouterFin(T& nouveau);

	bool ajouterAvantActuel(T& nouveau);
	bool ajouterApresActuel(T& nouveau);
	bool ajouterAvantElement(T& element, T& nouveau);
	bool ajouterApresElement(T& element, T& nouveau);

	bool enleverActuel();
	bool enleverPremierElement(T& element);
	bool enleverChaqueElement(T& element);

	bool possedeSuivant();
	bool possedePrecedent();

	bool suivant();
	bool precedent();
	bool retourDebut();
	bool retourFin();

	T* getDebut();
	T* getFin();
	T* getActuel();
	int getLongueur();

	T* getSuivant(T& element);
	T* getPrecedent(T& element);

	ListeDouble<T>* getClone();

	void setActuel(T element);

	bool estVide();
};


template <class T>
ListeDouble<T>::ListeDouble(){

	this->debut = 0;
	this->fin = 0;
	this->actuel = 0;
	this->longueur = 0;
}


template <class T>
bool ListeDouble<T>::ajouterDebut(T& nouveau){

	ItemListe<T>* nouveauItem = new ItemListe<T>();
	nouveauItem->item = &nouveau;
	nouveauItem->suivant = 0;
	nouveauItem->precedent = 0;

	ItemListe<T>* referenceAncienSuivant = this->debut;
	nouveauItem->suivant = referenceAncienSuivant;

	this->debut = nouveauItem;

	if(this->fin==0 || this->debut ==0){

		this->fin = nouveauItem;
	}

	if(referenceAncienSuivant!=0){

		referenceAncienSuivant->precedent = nouveauItem;
	}

	this->longueur++;
	return(true);
}

template <class T>
bool ListeDouble<T>::ajouterFin(T& nouveau){

	ItemListe<T>* nouveauItem = new ItemListe<T>();
	nouveauItem->item = &nouveau;
	nouveauItem->suivant = 0;
	nouveauItem->precedent = 0;

	ItemListe<T>* referenceAncienPrecedent = this->fin;
	nouveauItem->precedent = referenceAncienPrecedent;

	this->fin = nouveauItem;

	if(this->fin==0 || this->debut ==0){

		this->debut = nouveauItem;
	}

	if(referenceAncienPrecedent!=0){

		referenceAncienPrecedent->suivant = nouveauItem;
	}

	this->longueur++;
	return(true);
}

template <class T>
bool ListeDouble<T>::ajouterAvantActuel(T& nouveau){

	ItemListe<T>* nouveauItem = new ItemListe<T>();
	nouveauItem->item = &nouveau;
	nouveauItem->suivant = 0;
	nouveauItem->precedent = 0;

	if(this->actuel == 0){

		this->actuel = nouveauItem;

		this->debut=nouveauItem;
		this->fin=nouveauItem;
	}
	else{
//		bool ajouterAvantElement(T& element, T& nouveau);
	//	bool ajouterApresElement(T& element, T& nouveau);

		ItemListe<T>* referenceAncienPrecedent = this->actuel->precedent;
		nouveauItem->precedent = referenceAncienPrecedent;

		this->actuel->precedent = nouveauItem;

		if(this->actuel == this->debut){

			this->debut=nouveauItem;
		}

		nouveauItem->suivant = this->actuel;

		if(referenceAncienPrecedent!=0){

			referenceAncienPrecedent->suivant = nouveauItem;
		}


	}

	this->longueur++;
	return(true);
}

template <class T>
bool ListeDouble<T>::ajouterApresActuel(T& nouveau){

	ItemListe<T>* nouveauItem = new ItemListe<T>();
	nouveauItem->item = &nouveau;
	nouveauItem->suivant = 0;
	nouveauItem->precedent = 0;

	if(this->actuel == 0){

		this->actuel = nouveauItem;

		this->debut = this->actuel;
		this->fin = this->actuel;
	}
	else{

		ItemListe<T>* referenceAncienSuivant = this->actuel->suivant;
		nouveauItem->suivant = referenceAncienSuivant;

		this->actuel->suivant = nouveauItem;
		nouveauItem->precedent = this->actuel;

		if(this->actuel == this->fin){

			this->fin=nouveauItem;
		}

		if(referenceAncienSuivant!=0){

			referenceAncienSuivant->precedent = nouveauItem;
		}


	}

	this->longueur++;
	return(true);
}


template <class T>
bool ListeDouble<T>::ajouterAvantElement(T& element, T& nouveau){

	ItemListe<T>* curseur = debut;
	bool chercher=true;
	bool trouver=false;

	while(chercher){

		if(curseur ==0){

			chercher = false;
		}
		else{
			if(curseur->item == &element){

				chercher = false;
				trouver = true;

				ItemListe<T>* nouveauItem = new ItemListe<T>();
				nouveauItem->item = &nouveau;
				nouveauItem->suivant = 0;
				nouveauItem->precedent = 0;

				if(curseur==this->debut){

					this->debut = nouveauItem;
				}

				ItemListe<T>* referenceAncienPrecedent = curseur->precedent;
				nouveauItem->precedent = referenceAncienPrecedent;

				curseur->precedent = nouveauItem;
				nouveauItem->suivant = curseur;

				if(referenceAncienPrecedent!=0){

					referenceAncienPrecedent->suivant = nouveauItem;
				}

				this->longueur++;

			}
			else{

				curseur = curseur->suivant;
			}
		}

	}

	return(trouver);
}


template <class T>
bool ListeDouble<T>::ajouterApresElement(T& element, T& nouveau){

	ItemListe<T>* curseur = debut;
	bool chercher=true;
	bool trouver=false;

	while(chercher){

		if(curseur==0){

			chercher = false;
		}
		else{
			if(curseur->item == &element){

				chercher = false;
				trouver = true;

				ItemListe<T>* nouveauItem = new ItemListe<T>();
				nouveauItem->item = &nouveau;
				nouveauItem->suivant = 0;
				nouveauItem->precedent = 0;

				if(curseur == this->fin){

					this->fin = nouveauItem;
				}

				ItemListe<T>* referenceAncienSuivant = curseur->suivant;
				nouveauItem->suivant = referenceAncienSuivant;

				curseur->suivant = nouveauItem;
				nouveauItem->precedent = curseur;

				if(referenceAncienSuivant!=0){

					referenceAncienSuivant->precedent = nouveauItem;
				}

				this->longueur++;
			}
			else{

				curseur = curseur->suivant;
			}
		}

	}

	return(trouver);
}

template <class T>
bool ListeDouble<T>::enleverActuel(){

	if(actuel!=0){

		ItemListe<T>* curseur = actuel;

		if(curseur == debut){

			debut = curseur->suivant;
		}

		ItemListe<T>* referencePrecedent = curseur->precedent;
		ItemListe<T>* referenceSuivant = curseur->suivant;


		if(debut == actuel){

			if(referenceSuivant!=0){

				debut = referenceSuivant;
			}
			else{

				debut=0;
			}
		}

		if(fin == actuel){

			if(referencePrecedent!=0){

				fin = referencePrecedent;
			}
			else{

				fin=0;
			}
		}


		if(referenceSuivant!=0){

			referenceSuivant->precedent = referencePrecedent;
			actuel=referenceSuivant;
		}
		else{
			actuel=debut;

		}

		if(referencePrecedent!=0){

			referencePrecedent->suivant = referenceSuivant;

			if(referenceSuivant==0){

				actuel=referencePrecedent;
			}
		}

		this->longueur--;

		return(true);
	}

	return(false);
}

template <class T>
bool ListeDouble<T>::enleverPremierElement(T& element){

	ItemListe<T>* curseur = debut;

	while(curseur->precedent!=0){

		curseur=curseur->precedent;
	}

	bool chercher=true;
	bool trouver=false;

	while(chercher){

		if(curseur==0){

			chercher = false;
		}
		else{

			if(curseur->item == &element){

				chercher = false;
				trouver = true;

				if(curseur == debut){

					debut = curseur->suivant;
				}

				if(curseur == fin){

					fin = curseur->precedent;
				}

				ItemListe<T>* referencePrecedent = curseur->precedent;
				ItemListe<T>* referenceSuivant = curseur->suivant;

				if(referenceSuivant!=0){

					referenceSuivant->precedent = referencePrecedent;
				}

				if(referencePrecedent!=0){

					referencePrecedent->suivant = referenceSuivant;
				}

				this->longueur--;
			}
			else{

				curseur = curseur->suivant;
			}
		}

	}

	return(trouver);
}

template <class T>
bool ListeDouble<T>::enleverChaqueElement(T& element){

	ItemListe<T>* curseur = debut;

	while(curseur->precedent!=0){

		curseur=curseur->precedent;
	}

	bool chercher=true;
	bool trouver=false;

	while(chercher){

		if(curseur==0){

			chercher = false;
		}
		else{

			if(curseur->item == &element){

				trouver = true;


				ItemListe<T>* referencePrecedent = curseur->precedent;
				ItemListe<T>* referenceSuivant = curseur->suivant;

				if(curseur == debut){

					debut = referenceSuivant;
				}

				if(curseur == fin){

					fin = referencePrecedent;
				}

				if(referenceSuivant!=0){

					referenceSuivant->precedent = referencePrecedent;
				}

				if(referencePrecedent!=0){

					referencePrecedent->suivant = referenceSuivant;
				}

				this->longueur--;
			}

			curseur = curseur->suivant;

		}

	}

	return(trouver);
}

template <class T>
bool ListeDouble<T>::suivant(){

	if(actuel == 0){

		return(false);
	}
	else{

		if(actuel->suivant==0){

			return(false);
		}
		else{

			actuel = actuel->suivant;
		}
	}

	return(true);
}

template <class T>
bool ListeDouble<T>::precedent(){

	if(actuel == 0){

		return(false);
	}
	else{

		if(actuel->precedent==0){

			return(false);
		}
		else{

			actuel = actuel->precedent;
		}
	}

	return(true);
}

template <class T>
bool ListeDouble<T>::retourDebut(){

	if(debut == 0){

		return(false);
	}
	else{

		actuel = debut;
	}

	return(true);
}

template <class T>
bool ListeDouble<T>::retourFin(){

	if(fin == 0){

		return(false);
	}
	else{

		actuel = fin;
	}

	return(true);
}

template <class T>
T* ListeDouble<T>::getActuel(){
	if(actuel==0){
		return(0);
	}
	else{
		return (actuel->item);
	}
}

template <class T>
bool ListeDouble<T>::possedeSuivant(){
	return(actuel->suivant != 0);
}

template <class T>
bool ListeDouble<T>::possedePrecedent(){
	return(actuel->precedent != 0);
}

template <class T>
T* ListeDouble<T>::getDebut(){
	return(this->debut->item);
}

template <class T>
T* ListeDouble<T>::getFin(){
	return(this->fin->item);
}

template <class T>
int ListeDouble<T>::getLongueur(){
	return(this->longueur);
}

template <class T>
void ListeDouble<T>::setActuel(T element){
	this->actuel->item=new T(element);
}

template <class T>
bool ListeDouble<T>::estVide(){
	return(this->longueur==0);
}

template <class T>
ListeDouble<T>* ListeDouble<T>::getClone(){
	ListeDouble* nouvelleListe = new ListeDouble<T>();

	nouvelleListe->debut = this->debut;
	nouvelleListe->actuel = nouvelleListe->debut;
	nouvelleListe->longueur = this->longueur;

	return(nouvelleListe);
}

template <class T>
T* ListeDouble<T>::getPrecedent(T& element){
	ItemListe<T>* curseur = debut;
	ItemListe<T>* precedent=0;

	while(curseur->precedent!=0){
		curseur=curseur->precedent;
	}
	bool chercher=true;
	bool trouver=false;

	while(chercher){
		if(curseur==0){
			chercher = false;
		}
		else{
			if(curseur->item == &element){
				chercher = false;
				trouver = true;

				if(curseur == debut){
					debut = curseur->suivant;
				}
				if(curseur == fin){
					fin = curseur->precedent;
				}
				ItemListe<T>* referencePrecedent = curseur->precedent;
				ItemListe<T>* referenceSuivant = curseur->suivant;
				if(referenceSuivant!=0){
					referenceSuivant->precedent = referencePrecedent;
				}
				if(referencePrecedent!=0){
					referencePrecedent->suivant = referenceSuivant;
				}
				this->longueur--;
			}
			else{
				precedent = curseur;
				curseur = curseur->suivant;
			}
		}
	}
	return(precedent->item);
}

template <class T>
T* ListeDouble<T>::getSuivant(T& element){
	ItemListe<T>* curseur = debut;
	ItemListe<T>* suivant=0;

	while(curseur->precedent!=0){
		curseur=curseur->precedent;
	}
	bool chercher=true;
	bool trouver=false;

	while(chercher){
		if(curseur==0){
			chercher = false;
		}
		else{
			if(curseur->item == &element){
				chercher = false;
				trouver = true;
				if(curseur == debut){
					debut = curseur->suivant;
				}
				if(curseur == fin){
					fin = curseur->precedent;
				}
				ItemListe<T>* referencePrecedent = curseur->precedent;
				ItemListe<T>* referenceSuivant = curseur->suivant;
				if(referenceSuivant!=0){
					referenceSuivant->precedent = referencePrecedent;
				}
				if(referencePrecedent!=0){
					referencePrecedent->suivant = referenceSuivant;
				}
				this->longueur--;
			}
			else{
				curseur = curseur->suivant;
			}
		}
	}
	if(curseur==0){
		return(0);
	}
	else{
		return(curseur->item);
	}
}


#endif
