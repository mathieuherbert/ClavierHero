#include "EntiteVide.h"


EntiteVide::EntiteVide(int ligne, int colonne, char *caractere, Couleur couleur) :
	EntiteBase(0, ligne, colonne, caractere, 1, 1, couleur) {
}

bool EntiteVide::estEntiteVide() {
	return true;
}
