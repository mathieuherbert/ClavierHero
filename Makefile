OS=$(shell uname)
COMPILATEUR=CPP_$(OS)
LIEUR=LD_$(OS)
COMPILATEUR_OPTION=COMPOP_$(OS)
LIEUR_OPTION=LIEUR_$(OS)

#-------------------
##Pour Mac
CPP_Darwin=i386-elf-g++-4.3.2
LD_Darwin=i386-elf-ld

#-------------------
##Pour Linux
CPP_Linux=g++
LD_Linux=ld
COMPOP_Linux=-fno-stack-protector -m32
LIEUR_Linux=-m elf_i386

#-------------------
##POUR WINDOWS
CPP_WindowsNT=g++
LD_WindowsNT=ld
 
#-------------------
## Partie commune a toutes les configurations

CPPFLAGS  = -gdwarf-2 -g3 -Wall -fno-builtin -fno-rtti -fno-exceptions -nostdinc -fno-threadsafe-statics -fno-stack-protector -m32 -Wno-write-strings $($(COMPILATEUR_OPTION))
LDFLAGS = --warn-common -nostdlib $($(LIEUR_OPTION))

PWD :=.
DELE = rm
MV = mv -f


KERNEL_OBJ   = sextant.elf


OBJECTSNAMES=\
Alien\
BlocAliens Bunker\
CaseSP Canon ClavierP ClavierV Compteur cpu_context cpu_context_switch\
EcranP EcranV EntiteBase EntiteFactory EntiteVide Espace\
Warcraft Unite Position Menu Map Joueur Batiment Attaque Ennemi FabriqueDennemi JoueurTD MapTD MenuTD Tour \
fonctionsES FondEspace fs_fat\
gdt\
handler_tic handler_clavier\
i8259 ide idt ImpApp irq irq_wrappers\
ListeDouble\
main Memoire MemoireListe MemoirePaginee MemoirePion MemoireTab Missile MissileAlien MissileCanon mouse_handler multiboot Mutex\
op_memoire\
Pagination PortSerie \
Random\
sched Scheduler Semaphore Shell ShellV Son Souris SpaceInvaders Spinlock String\
TestAndSet thread timer TimerSpaceInvaders Trame Top\
EcranPMF EcranVMF \
SuperPong Raquette RandomSP Grille  Balle \
CasePacman JeuPacman PlateauPacman LecteurClavier LecteurTouche PersonnagePacman Pacman Blinky Clyde Inky Pinky Dijkstra \
AfficherReussiteNote AffichageFin Note SonClavierHero Soupire Partition Bibliotheque Conversion GestionToucheClavier ClavierHero \

 
OBJECTS=$(patsubst %,build/all-o/%.o,$(OBJECTSNAMES))					  		

#variable pour demander a make de chercher les dependances dans n'importe quel repertoire jusqu'à 3 rep de profondeur :
VPATH=$(wildcard *):$(wildcard */*):$(wildcard */*/*)

# les target all et clean ne sont pas "constructibles" mais appellent des recettes :
.PHONY:all clean run show


# Main target
all: $(KERNEL_OBJ)


OBJ_FILES = $(wildcard build/all-o/*.o)

$(KERNEL_OBJ): $(OBJECTS)
	echo 'Votre compilateur $(COMPILATEUR) et votre lieur $(LIEUR)'
	$($(LIEUR)) $(LDFLAGS) -T ./support/sextant.lds -o build/boot/$@ $(OBJECTS)

#compiler tout .cpp dans les repertoires de sources en .o dans le build/all-o . On cree d'abord le repertoire build/all-o s'il n'existe pas.
build/all-o/%.o:%.cpp %.h
	$($(COMPILATEUR)) -I$(PWD) -c $< $(CPPFLAGS) -o $@

# la meme que precedement, si pas de .h correspondant on compile quand meme.
build/all-o/%.o:%.cpp
	$($(COMPILATEUR)) -I$(PWD) -c $< $(CPPFLAGS) -o $@
	
#meme regle que precedente pour les fichiers .s
build/all-o/%.o: %.S
	$($(COMPILATEUR)) -I$(PWD)  -c $< $(CPPFLAGS) -DASM_SOURCE=1 -o $@



# Clean directory
clean:
	$(DELE) -rf build/all-o/*.o
	$(REM) -f *.s
	$(REM) -f build/boot/*.elf

run:
	cd build/boot && qemu -no-kvm -M isapc -L "/usr/share/qemu" -net nic,model=ne2k_isa -net user -tftp ./ -cdrom grub.iso -soundhw pcspk -m 4 

show:
	@echo "objects:$(OBJECTS)"
	@echo "VPATHS:$(VPATH)"
	@echo "compilateur:"$($(COMPILATEUR))" ; lieur:"$($(LIEUR))
 
	