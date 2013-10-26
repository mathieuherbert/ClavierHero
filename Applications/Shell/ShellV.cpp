/*
 * ShellV.cpp
 *
 *  Created on: 8 decembre. 2010
 *      Author: pouda
 */

#include<Applications/Shell/ShellV.h>
#include<drivers/ClavierV.h>
#include<lib/String.h>
#include<Applications/Shell/ListeDouble.h>
#include<Applications/Shell/IntApp.h>
#include<drivers/EcranV.h>
#include<Applications/AppliShell/Compteur.h>
#include <sextant/ordonnancements/preemptif/thread.h>

//#include <Applications/Demenageur/Demenageur.h>
#include <Applications/Top/Top.h>
#include <Applications/Warcraft/Warcraft.h>
#include <Applications/Warcraft/Map.h>
#include <Applications/Pacman/JeuPacman.h>
#include <Applications/KeyboardHero/ClavierHero.h>
extern bool warInit;
extern Souris mouse;
//Space Invaders
#include <Applications/SpaceInvaders/SpaceInvaders.h>
//#include <drivers/TimerSpaceInvaders.h>

//CONSTANTES pour les commandes
const int LS = 0;
const int RUNAPPLI = 1;
const int KILLAPPLI = 2;
const int EXIT = 3;
const int TOP = 4;
const int PS = 5;
//CONSTANTES pour les applications
const int HORLOGE = 100;
const int SPACE_INVADERS = 101;
const int SUPER_PONG = 102;

//CONSTANTE pour le nombre maximum de caracteres
const int MAX_CHAR = 256;

// Constructeur du Shell
ShellV::ShellV(EcranV *ecran, ClavierV *clavier, Shell *shellPere,
		int numeroEcran, Scheduler *sched) {
	this->ecran = ecran;
	this->clavier = clavier;
	this->shellPere = shellPere;
	this->numeroEcran = numeroEcran;
	this->sched = sched;
	this->historique = new ListeDouble<String>();
}

// Affichage des commandes possibles
void ShellV::AfficherAide() {
	ecran->miniprintf(
			"\t 'ls' => liste des activites disponibles\n");
	ecran->miniprintf(
			"\t 'run appli' => Lance l'application appli.\n");
	ecran->miniprintf(
			"\t 'ps' => liste des activites en cours\n");
//	ecran->miniprintf(
//			"\t 'suspend pid' => Suspendre l'activite correspondant au pid\n");
	ecran->miniprintf(
			"\t 'kill pid' => Arreter l'activite correspondant au pid sans precautions\n");

}

int ShellV::dixPuissance(int i) {
	int retour = 1;
	for (int j = 0; j < i; j++) {
		retour = retour * 10;
	}
	return retour;
}

// Liste des applications disponibles
void ShellV::listerApplis(ListeDouble<String> *liste) {
	ecran->miniprintf("les applications disponibles sont :\n");

	bool search = !(liste->estVide());
	liste->retourDebut();

	while (search) {

		ecran->miniprintf("Appli : %s",liste->getActuel()->getString());
		ecran->miniprintf("\n");
//		while(1);
		if (liste->possedeSuivant()) {

			liste->suivant();
		} else {

			search = false;
		}
	}
}

// Liste des applications en cours
void ShellV::listerApplisEncours(ListeDouble<IntApp> *liste) {
	ecran->miniprintf("Voici la liste des applications en cours de fonctionnement\n");
	//ecran->miniprintf("pid:nom de l'aplication\n");
	bool search = !(liste->estVide());

	while (search) {
		ecran->afficherChiffre(liste->getActuel()->getPid());
		ecran->miniprintf(":");
		ecran->miniprintf(liste->getActuel()->getNom()->getString());
		ecran->miniprintf("\n");
		if (liste->possedeSuivant()) {
			liste->suivant();
		} else {
			search = false;
		}
	}
}


IntApp* ShellV::getAppli(int pid) {
	bool search = !(shellPere->getEncours()->estVide());
	bool finded = false;
	while (search) {
		IntApp* valeur = shellPere->getEncours()->getActuel();
		if (valeur->getPid() == pid) {
			search = false;
			finded = true;
		} else {
			if (shellPere->getEncours()->possedeSuivant()) {
				shellPere->getEncours()->suivant();
			} else {
				search = false;
			}
		}
	}
	if (finded) {
		return shellPere->getEncours()->getActuel();
	}
}

String* ShellV::getAppliAlancer(String nom) {
	// On est oblige de faire un premier tour de liste des applications disponibles
	ListeDouble<String> *liste = shellPere->getDisponible();
	bool searchappli = !(liste->estVide());
	liste->retourDebut();
	while (searchappli) {
		liste->getActuel();
		if (liste->possedeSuivant()) {
			liste->suivant();
		} else {
			searchappli = false;
		}
	}
	// On va ensuite verifier si cette appli existe
	bool search = !(liste->estVide());
	bool finded = false;
	while (search) {
		String* valeur = liste->getActuel();
		if (valeur->isEqual(nom)) {
			search = false;
			finded = true;
		} else {
			if (liste->possedeSuivant()) {
				liste->suivant();
			} else {
				search = false;
			}
		}
	}
	if (finded) {
		//ecran->miniprintf("fini trouve rend la main %s", liste->getActuel()->getNom());
		//clavier->getChar();
		return liste->getActuel();
	}
	return 0;
}
// getClavier() permet de recuperer l'instruction entree au clavier par l'utilisateur
String ShellV::getClavier() {

	char buffer[MAX_CHAR];					//buffer contenant l'intruction
	int i = 0;								//index du caractere en cours d'ecriture
	char c;									//caractere lu
	do {									//boucle de lecture
		c = clavier->getChar();				//lecture d'un caractere au clavier
		if(c=='-'){							//cas du caractere d'effacement (backspace)
			if(i>0){
				ecran->afficherCaractere(BLANC, NOIR, ' ');	// on efface la position du curseur
				ecran->reculerPositionCourante();
				i--;										// on recule d'une case l'index du buffer
				ecran->effacerCaractere();
				ecran->afficherCaractere(NOIR, BLANC, ' ');	// on recule le curseur
				ecran->reculerPositionCourante();
			}
		}
		else if(c==':'){
			//fleche haut
			if(historique->possedePrecedent()){										//Teste l'existence d'une entree precedente
				buffer[i]='\0';
				String ligneEnCours = String(buffer);								//Enregistrement la ligne en cours
				for(int l = 0; l < String::strlen(buffer);l++) {					//Effacement de la ligne en cours
					i--;
					ecran->effacerCaractere();
				}

				historique->setActuel(ligneEnCours.getString());					//ajout de la ligne en cours a l'historique
				historique->precedent();											//Decalage dans l'historique
				String lignePrecedente = *historique->getActuel();
				int taille = String::strlen(lignePrecedente.getString());

				for(int l = 0; l < taille;l++) {									//Ecriture de la ligne precedente
					buffer[i]= lignePrecedente.getString()[i];
					ecran->afficherCaractere(BLANC, NOIR, buffer[i]);
					i++;
				}
			}
		}
		else if(c==';'){
			//fleche bas
			if(historique->possedeSuivant()){			//Teste l'existence d'une entree suivante
				buffer[i]='\0';
				String ligneEnCours = String(buffer);							//Enregistrement la ligne en cours
				for(int l = 0; l < String::strlen(buffer);l++) {				//Effacement de la ligne en cours
					i--;
					ecran->effacerCaractere();
				}

				historique->setActuel(ligneEnCours.getString());					//ajout de la ligne en cours a l'historique
				historique->suivant();											//Decalage dans l'historique
				String ligneSuivante = *historique->getActuel();
				int taille = String::strlen(ligneSuivante.getString());

				for(int l = 0; l < taille;l++) {								//Ecriture de la ligne suivante
					buffer[i]= ligneSuivante.getString()[i];
					ecran->afficherCaractere(BLANC, NOIR, buffer[i]);
					i++;

				}
			}
		}
		else if(c=='<'){
			//fleche gauche
			//TO DO deplacement curseur
		}
		else if(c=='='){
			//fleche droite
			//TO DO deplacement curseur
		}
		else {
			if (c != '\n') {				// on ecrit le caractere lu dans le buffer
				buffer[i] = c;
				ecran->afficherCaractere(BLANC, NOIR, c); 	// on affiche le caractere
				//ecran->Chiffre(c);						// cette commande permet de tester la valeur d'une touche
				i++;
				ecran->afficherCaractere(NOIR, BLANC, ' '); // affichage du curseur
				ecran->reculerPositionCourante();
			}
		}
	} while (c != '\n' && i < (256 - 1));	// on sort de la boucle si le caractere lu est le retour chariot
	//ou si on atteint la taille maximale du buffer
	buffer[i] = '\0'; 						//on ajoute le caractere de fin de ligne
	String s(buffer);						//conversion du buffer en String
	ecran->sautDeLigne();

	return s;
}

// getCommande() permet de recuperer la commande
// L'attribution de numeros a chaque commande permet de faire
// un switch case dans le run
int ShellV::getCommande(String s){
	int aRetourner;
	String** tab = s.split(' ');
	String* commande = tab[0];

	if (commande->isEqual("ls")){
		aRetourner = LS;
	}
	if (commande->isEqual("ps")){
		aRetourner = PS;
	}
	else if (commande->isEqual("run")){
		aRetourner = RUNAPPLI;
	}
	else if (commande->isEqual("kill")) {
		aRetourner = KILLAPPLI;
	}
	else if (commande->isEqual("exit")){
		aRetourner = EXIT;
	}
	return aRetourner;


}

// getArgument permet de recuperer l'argument i de la commande
// ex : pour run compteur, on recupere compteur grace a l'appel getArgument(s,1)
// (attention le tab[0] contient la commande, le premier argument est en tab[1])
String ShellV::getArgument(String s, int i){
	String** tab = s.split(' ');
	return *tab[i];
}

// L'application ls liste les applications disponibles.
void ShellV::ls(String cmd) {
	String arg_1 = getArgument(cmd, 1);
	if(arg_1.isEqual("")) {
		ecran->miniprintf("Les applis disponnibles : \n");
		listerApplis(shellPere->getDisponible());
	}
	else {
		ecran->miniprintf("ls retourne la liste des applications disponibles.\nIl n'a pas d'arguments\n");
	}
}

// L'application ls liste les applications en cours.
void ShellV::top(String cmd) {
	String arg_1 = getArgument(cmd, 1);
	if(arg_1.isEqual(0)) {
		listerApplisEncours(shellPere->getEncours());
	}
	else {
		ecran->miniprintf("top retourne la liste des applications en cours.\nIl n'a pas d'arguments.\n");
	}
}

// L'application run execute le premier argument, si c'est une appli qui existe
void ShellV::runAppli(String cmd, int numThread) {
	Semaphore sem;
	Semaphore block;
	sem.V();
	String arg_1 = getArgument(cmd, 1);
	String vide = String("");
	if(!arg_1.isEqual(0)&&!arg_1.isEqual(vide)) {
		if(arg_1.isEqual("Compteur")) {
			sem.P();

			//sched->addThread((thread*) getAppliAlancer("Compteur"), numThread);
			ecran->miniprintf("run lance compteur\n");
			Compteur *myCpt = new Compteur(ecran);
			myCpt->start("Compteur");
			block.P(); // on bloque le shell

			sem.V();
		}
		/*if(arg_1.isEqual("Demenageur")) {
			sem.P();

			//sched->addThread((thread*) getAppliAlancer("Compteur"), numThread);
			ecran->miniprintf("run lance Demenageur\n");


			Plateau *plateau1;
			Demenageur *jeu1 = new Demenageur(ecran,clavier,plateau1);
			jeu1->start("Dem 1");
			block.P(); // on bloque le shell

			sem.V();
		}*/
		if(arg_1.isEqual("Top")) {
					sem.P();

					//sched->addThread((thread*) getAppliAlancer("Compteur"), numThread);
					ecran->miniprintf("run lance Top\n");


					Top *appli1 = new Top(ecran);
					appli1->start("Top 1");
					block.P(); // on bloque le shell

					sem.V();
				}
		if(arg_1.isEqual("War")) {
					sem.P();

					ecran->miniprintf("run lance War\n");

					Warcraft *war = new Warcraft(ecran,clavier,&mouse);
					war->start("War");

					block.P(); // on bloque le shell

					sem.V();
				}
		if(arg_1.isEqual("SP")) {
					sem.P();
					ecran->miniprintf("run lance SP\n");

					SpaceInvaders *spaceInvaders = new SpaceInvaders(ecran, clavier);
					spaceInvaders->start("SP 1");

					block.P(); // on bloque le shell

					sem.V();
				}

		if(arg_1.isEqual("Pacman")) {
					sem.P();

					//sched->addThread((thread*) getAppliAlancer("Compteur"), numThread);
					ecran->miniprintf("run lance Pacman\n");


					PlateauPacman *plateauPacman;

					JeuPacman *jeuP = new JeuPacman(ecran,clavier,plateauPacman);
					jeuP->start("Pac 1");
					block.P(); // on bloque le shell

					sem.V();
				}
		if(arg_1.isEqual("CH")) {
					sem.P();

					//sched->addThread((thread*) getAppliAlancer("Compteur"), numThread);
					ecran->miniprintf("run lance Clavier Hero\n");
					ClavierHero *clavierHero = new ClavierHero(ecran, clavier);
					clavierHero->start("CH");

					block.P(); // on bloque le shell

					sem.V();
				}
		else{
			ecran->miniprintf("Cette application n'existe pas.\n");
		}
	}
	else {
		ecran->miniprintf("run lance l'application passee en argument.\nPour avoir la liste des applications disponibles entrez ls\n");
	}

	/*
	    //ecran->miniprintf(arg_1.getString());
		//clavier->getChar();
		//sem.V();
		//sem.P();
		thread* test = (thread*) getAppliAlancer(arg_1.getString());
		//sem.V();
		//ecran->miniprintf(test->name);
		//clavier->getChar();
		ecran->miniprintf("\n");
		//sched->addThread(test, numThread);
	 */

}

void ShellV::killAppli(String cmd) {

	String stringpid = getArgument(cmd, 1);
	if (stringpid.isEqual("")) {ecran->miniprintf("PID demande\n");}
	else {
		int pid=String::atoi(&stringpid);
		sched_set_exit(getThreadByPid(pid));
	}

}

void ShellV::ps(){
	struct uneStruct *all_ready_thread;
	struct uneStructWaiting *all_waiting_thread;

	all_ready_thread = getReadyThread();
	all_waiting_thread = getWaitingThread();
	ecran->effacerEcranV(NOIR);
	ecran->miniprintf("TOP\n");

	struct thread *running = getRunningThread();
	String *mypid = new String(running->pid);
	ecran->miniprintf("%s Running   Name %s | State : %s\n",
						String::format(mypid->getString(),3)->getString(),
						String::format(running->name,10)->getString(),
						String::format(print_state(running->state),12)->getString());

	for (int i=0;i<MAX_THREAD;i++) {
		if (all_ready_thread[i].free==0) {
			// Conversion pid numerique en String
			String *mypid =
					new String(all_ready_thread[i].thread->pid);

			// formatage pid sur 3 caracteres
			ecran->miniprintf("%s Ready   Q Name %s | State : %s\n",
					String::format(mypid->getString(),3)->getString(),
					String::format(all_ready_thread[i].thread->name,10)->getString(),
					String::format(print_state(all_ready_thread[i].thread->state),12)->getString());
		}
	}
	for (int i=0;i<MAX_THREAD;i++) {
		if (all_waiting_thread[i].free==0) {
			String *mypid =
						new String(all_waiting_thread[i].thread->pid);

			ecran->miniprintf("%s Waiting Q Name %s | State : %s\n",
					String::format(mypid->getString(),3)->getString(),
					String::format(all_waiting_thread[i].thread->name,10)->getString(),
					String::format(print_state(all_waiting_thread[i].thread->state),12)->getString());

		}
	}
}


void ShellV::run() {

	// liste double utilisee pour le UP et le DOWN
	//	ListeDouble<String> *hist = ListeDouble();
	//	hist->ajouterFin(0);
	sem.V();
	do {
		sem.P();
		//variable du numero de l'application
		int numThread = 10;

		//initialisation
		ecran->miniprintf("Shell");
		ecran->afficherChiffre(numeroEcran);
		ecran->miniprintf(":>");

		ecran->afficherCaractere(NOIR, BLANC, ' '); // curseur
		ecran->reculerPositionCourante();

		//char c;
		//int i=0;

		//numero de l'ecran a prendre en compte
		int numEcran = 0;
		//int lancerProgramme = 0;

		//int proc = numEcran;
		String s = getClavier();
		int cmd = getCommande(s);

		// L'application a lancer selon la commande
		switch(cmd){
		case LS :
			ls(s);
			break;
//		case TOP :
//			top(s);
//			break;
		case RUNAPPLI :
			runAppli(s,numThread);
			numThread++;
			break;
		case KILLAPPLI :
			killAppli(s);
			//getAppli(proc)->killHard();
			break;
		case PS :
			ps();
			//getAppli(proc)->killHard();
			break;
		case EXIT :
			// a implementer
			break;
		default :
			AfficherAide();
			break;
		}

		historique->ajouterFin(s);
		historique->retourFin();
		//		ecran->miniprintf(s.getString());
		//		clavier->getChar();
		sem.V();

	} while (true);

}
