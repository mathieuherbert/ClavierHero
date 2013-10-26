#include <hal/multiboot.h>

#include <sextant/interruptions/idt.h>
#include <sextant/interruptions/irq.h>
#include <sextant/interruptions/handler/handler_tic.h>
#include <sextant/interruptions/handler/handler_clavier.h>

#include <drivers/PortSerie.h>
#include <drivers/timer.h>
#include <drivers/Trame.h>

#include <sextant/memoire/Memoire.h>
#include <sextant/memoire/segmentation/gdt.h>
#include <sextant/memoire/MemoirePion.h>
#include <sextant/memoire/pagination/MemoirePhysique.h>
#include <sextant/memoire/pagination/Pagination.h>

#include <sextant/ordonnancements/cpu_context.h>
#include <sextant/ordonnancements/preemptif/thread.h>
#include <sextant/types.h>
#include <sextant/Synchronisation/Spinlock/Spinlock.h>

//#include <Applications/Horloge/Horloge.h>

extern "C" void __cxa_pure_virtual() { while (1); }

//#include <Applications/SuperPong/SuperPong.h>



// Souris

#include <sextant/interruptions/handler/mouse_handler.h>
#include <drivers/Souris.h>

// Ecran Virtuel

#include <drivers/EcranV.h>
#include <drivers/EcranP.h>

// Clavier Virtuel

#include <drivers/ClavierP.h>
#include <drivers/ClavierV.h>


// Son

#include <drivers/Son.h>

// Disque

#include <sextant/Fichiers/fs_fat.h>
#include <drivers/ide.h>

// MultiFenetrage
#include <drivers/EcranPMF.h>

// Applications
/////////////////

//Demenageur
//#include <Applications/Demenageur/Demenageur.h>

// Shell
#include <Applications/Shell/Shell.h>

//Space Invaders
//#include <Applications/SpaceInvaders/SpaceInvaders.h>
//#include <drivers/TimerSpaceInvaders.h>

//Warcraft
#include <Applications/Warcraft/Warcraft.h>
#include <Applications/Warcraft/Map.h>
bool warInit = false;
Warcraft *war;

// Top
#include <Applications/Top/Top.h>
Top *myTop;

#include <Applications/SuperPong/SuperPong.h>
SuperPong *SPong;

extern struct ide_controller ide_controllers[MAX_IDE_CONTROLLERS];

extern char __e_kernel,__b_kernel, __b_data, __e_data,  __b_stack, __e_load ;
int i;

extern vaddr_t bootstrap_stack_bottom; //Adresse de dÃ©but de la pile d'exÃ©cution
extern size_t bootstrap_stack_size;//Taille de la pile d'exÃ©cution
unsigned long address; // TODO first assignement of this variable (required for Sextant_init)

// Variable d'initialisation
bool avecdisque=false;
bool avecSpaceInvaders=true;

Timer timer;
//Clavier *clavier;

EcranV ecranV[6];
EcranP *ecranP;

Souris mouse;

Memoire *InterfaceMemoire;


extern Semaphore *semClavierV[MAXCONSOLE]; // dans ClavierP.cpp
extern char buffeur[MAXCONSOLE][TAILLE_BUF_CLAVIER]; // dans ClavierP.cpp

ClavierP *clavierPhysique;
ClavierV *clavierVirtuel[MAXCONSOLE];

Semaphore block_me;

void TicTacToc(int i){
	int position;
	volatile caseEcran *Video = ecranP->getOrigine();

	ticTac(0);

	// Raffaraichir l'ecran

	ecranP->raffraichir();

	// Afficher le curseur

	mouse.bouger(ecranP->getEcranActif());
	position = mouse.y * COLONNES + mouse.x; // position lineaire relative
	Video[position].caractere = '>';
	Video[position].couleurs = BLANC;
	if ((mouse.clicD)||(mouse.clicG)||(mouse.clicM))
		Video[position].couleurs = ROUGE;

	// Appeller l'ordonanceur
	sched_clk(i);
}


void Sextant_Init(){


	idt_setup();
	irq_setup();

	//Initialisation de la frequence de l'horloge

	timer.i8254_set_frequency(1000);
	asm volatile("sti\n");//Autorise les interruptions

	// Initialisation de la mŽmoire

	multiboot_info_t* mbi;
	mbi = (multiboot_info_t*)address;

	gdt_setup();

	InterfaceMemoire=Memoire::nouveau();

	InterfaceMemoire->mem_setup(& __e_kernel,(mbi->mem_upper<<10) + (1<<20),(EcranV*)&ecranV[0]);

	thread_subsystem_setup(bootstrap_stack_bottom,bootstrap_stack_size);

	// Initialisation de l'ordo

	sched_subsystem_setup();
	irq_set_routine(IRQ_TIMER, TicTacToc);

	// Initialisation de la souris sur l'ecran virtuel 0

	mouse.initialiser(&(ecranV[0]));

	// Innitialisation de l'Žcran physique

	ecranP = new EcranP((EcranV *)ecranV);

	// Initialisation des claviers Physiques et Virtuels.

	clavierPhysique = new ClavierP(&(ecranV[1]));
	clavierPhysique->start("Keyboard");

	for (int i=0;i<MAXCONSOLE;i++)
		clavierVirtuel[i] = new ClavierV(semClavierV[i],(char*)&(buffeur[i]));

	// Initialisation du handler clavier

	clavier_install();

	// Init du disque
	if (avecdisque==true) {
		ide_subsystem_setup(&(ecranV[0]));
		fat_setup(false); // FALSE = Pas de formatage, TRUE = Formatage du disque.
	}
}

extern "C" void Sextant_main(unsigned long magic, unsigned long addr){

	Sextant_Init();

	Son son;
	son.octave = 4;

	ecranV[0].afficherMot("CONSOLE 1\n");
	ecranV[0].miniprintf("Bienvenue dans sextant l'OS de l'EMN\nhttp://sextant.menaud.fr/");
	ecranV[0].sautDeLigne();
	ecranV[0].afficherCaractere(BLANC,ROUGE,0xB0);
	ecranV[0].afficherCaractere(BLANC,ROUGE,0xB1);
	ecranV[0].afficherCaractere(BLANC,ROUGE,0xB2);
	ecranV[0].sautDeLigne();
	ecranV[0].afficherMot("Cette OS minimaliste a ete developpe 'from scratch' par les etudiants dans le cadre de l'UV Systeme et Reseaux", ROUGE);
	ecranV[0].sautDeLigne();
	ecranV[0].sautDeLigne();
	ecranV[0].afficherMot("D'un point de vue utilisation, il pourrait etre comparer a un mini DOS (ancetre de windows)", ROUGE);
	ecranV[0].afficherMot("D'un point de vue technique, il integre plusieurs concepts avances comme par exemple l'ordonnancement preemptif\n", ROUGE);

	ecranV[1].afficherMot("CONSOLE 1\n");
	ecranV[2].afficherMot("CONSOLE 2\n");
	ecranV[3].afficherMot("CONSOLE 3\n");

//	warInit = true;
//	war = new Warcraft(&(ecranV[1]),clavierVirtuel[1],&mouse);
//	war->start("WarMain");

	Shell *init = new Shell (ecranV, clavierVirtuel, 3);

//	myTop = new Top(&(ecranV[4]));
//	myTop->start("Top");

//	war = new Warcraft(&(ecranV[1]),clavierVirtuel[1],&mouse);
//	warInit = true;
//	war->start("WarMain");

		while(1);

	EcranPMF *myMultiEcran = new EcranPMF(&(ecranV[4]));

//	SPong = new SuperPong(&(ecranV[2]),clavierVirtuel[2]);
//	SPong->start();

//	while(1);
	// Jeux : 1 - Demenageur






//




//
//// Lorsuque l'on lance le jeu, on ne peut plus crŽer de Thread (ou en tout cas ca reste bloquer apres le start()
//
	ecranV[2].miniprintf("Create Demenageur\n");
	//Plateau *plateau1;
	//Demenageur *jeu1 = new Demenageur(&(ecranV[2]),(clavierVirtuel[2]),plateau1);
	//jeu1->start("Dem 1");
//

	myTop = new Top(&(ecranV[0]));
	myTop->start("Top");

	//TimerSpaceInvaders *timer;
		//	timer = new TimerSpaceInvaders(&(ecranV[3]));
			//On doit rajouter le paramétre clavier a la méthode qu'initialize le jeu
			//SpaceInvaders spaceInvaders(&(ecranV[3]), clavierVirtuel[3] , timer);




			//Plateau *plateau2;
	//Demenageur *jeu2 = new Demenageur(&(ecranV[4]),(clavierVirtuel[4]),plateau2);
	//jeu2->start("Dem 2");



	// sizeof(int);

//	ecranP->setEcran(0);

//	while(1);

	if (avecdisque==true) {
		// sŽrie de test pour la gestion du disque
		//char chien[512];
		//struct fat_directory *fic;

		//Creation du fichier chien
		//if(create_file("chien") != -SEXTANT_ERROR) {
			//fic = fopen("chien");
			//fwrite(fic,"Le chien et le chat jouent.\n",String::strlen("Le chien et le chat jouent.\n")+1);
		//}
		/* else

			chien[0]='\0';
			if(create_file("toto.txt") != SEXTANT_ERROR) {
			ecranV[0].miniprintf("creation fichier ");
		}
		else ecranV[0].miniprintf("Erreur creation");


		fic = fopen("chien");
		//	fseek(fic,13);
		if (fic == NULL) {ecranV[0].miniprintf("Erreur ouverture");while(1);}
		fread(fic,chien,512);
		//	fclose(fic);
		ecranV[0].miniprintf("Le message %s",chien);
		while(1);*/
	} // fin de avecdisque

// Lancement du Shell

//	Shell *init = new Shell (ecranV, clavierVirtuel, 3);




// Space Invaders

	/*
	if (avecSpaceInvaders==true) {
		TimerSpaceInvaders *timer;
		timer = new TimerSpaceInvaders(&(ecranV[4]));
		//On doit rajouter le paramétre clavier a la méthode qu'initialize le jeu
		SpaceInvaders spaceInvaders(&(ecranV[4]), clavierVirtuel[4] , timer);
	}
*/

//	while (1) {ecranP->setEcran(0);son.note(clavier->getChar());}
//	while (1) {ecranP->setEcran(0);mouse.bouger(&(ecranV[0]));}
//	block_me.P();

	while(1);// ecranV[1].afficherMot("BLOCK\n");;

}
