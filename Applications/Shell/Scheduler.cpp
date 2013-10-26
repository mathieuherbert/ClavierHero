/*
 * Scheduler.cpp
 *
 *  Created on: 8 dŽc. 2010
 *      Author: jonathan
 */

#include "Scheduler.h"

Scheduler::Scheduler() {
	// TODO Auto-generated constructor stub

	this->listeAPPLIS = new ListeDouble<PID_to_THREADS>();
}

Scheduler::~Scheduler() {
	// TODO Auto-generated destructor stub
}

bool Scheduler::addThread(thread* t, int pid){

	this->listeAPPLIS->retourDebut();

	bool search = !(this->listeAPPLIS->estVide());
	bool finded = false;

	while(search){

		PID_to_THREADS* valeur = this->listeAPPLIS->getActuel();

		if(valeur->PID==pid){

			search = false;
			finded = true;

			valeur->listeThreads->ajouterFin(*t);
		}
		else{

			if(this->listeAPPLIS->possedeSuivant()){

				this->listeAPPLIS->suivant();
			}
			else{

				search = false;
			}
		}
	}

	if(!finded){

		PID_to_THREADS* nouvelle_entree = new PID_to_THREADS;

		nouvelle_entree->PID = pid;
		nouvelle_entree->listeThreads = new ListeDouble<thread>();
		nouvelle_entree->listeThreads->ajouterDebut(*t);

		this->listeAPPLIS->ajouterDebut(*nouvelle_entree);
	}

	// ON AJOUTE MAINTENANT DANS LES FONCTIONS BAS NIVEAU DU SCHEDULER

	// le thread va etre ajoutŽ dans la liste "ready"

	sched_set_ready(t);

	return(true);
}

bool Scheduler::enleverThread(thread* t){

	bool search = true;
	bool finded = false;

	int i=0;

	uneStructWaiting* ptr_struct = getWaitingThread();
	while(search){

		if(ptr_struct->thread==t){

			// on rend cette structure disponible
			ptr_struct->free=1;

			search=false;
			finded=true;
		}
		else{

			i++;

			if(i>=getMaxThread()){

				search=false;
			}
			else{

				ptr_struct++;
			}

		}

	}

	return(finded);
}

bool Scheduler::enleverThreads(int pid){

	this->listeAPPLIS->retourDebut();

	bool search = !(this->listeAPPLIS->estVide());
	bool finded = false;

	PID_to_THREADS* valeurRecherchee = 0;

	while(search){

		PID_to_THREADS* valeur = this->listeAPPLIS->getActuel();

		if(valeur->PID==pid){

			search = false;
			finded = true;

			valeurRecherchee=valeur;
		}
		else{

			if(this->listeAPPLIS->possedeSuivant()){

				this->listeAPPLIS->suivant();
			}
			else{

				search = false;
			}
		}
	}

	if(valeurRecherchee!=0){

		ListeDouble<thread>* listeDesThreads = valeurRecherchee->listeThreads;
		listeDesThreads->retourDebut();

		bool search = !(listeDesThreads->estVide());
		bool finded = false;

		while(search){

			thread* t = listeDesThreads->getActuel();

			this->enleverThread(t);

			search = listeDesThreads->possedeSuivant();

			if(search){
				listeDesThreads->suivant();
			}
		}

	}

	return(finded);
}
