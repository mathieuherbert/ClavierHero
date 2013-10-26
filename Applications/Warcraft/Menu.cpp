#include "Menu.h"

Menu::Menu(EcranV *ecr, ClavierV *clavier):ecr(ecr),clavier(clavier){
	initialiserSalementLeMenu();
}

EcranV *Menu::getEcranV() {
	return this->ecr;
}


void Menu::changerValeur(int grandeur,int valeur){
	int
	x,
	y,
	centre;
	switch(grandeur){
	case BOIS :
		x = 2;
		y = 6;
		centre = 0;
		break;
	case OR :
		x = 1;
		y = 4;
		centre = 0;
		break;
	case POPULATION :
		x = 3;
		y = 5;
		centre = 0;
		break;
	case PAYSAN :
		x = 9;
		y = 1;
		centre = 1;
		break;
	case GUERRIER :
		x = 9;
		y = 6;
		centre = 1;
		break;
	}
	tab[x][y] = 32;
	tab[x][y+1] = 32;
	tab[x][y+2] = 32;

	if(valeur>99){
		tab[x][y] = 48+(int)(valeur/100);
		tab[x][y+1] = 48+(int)((valeur%100)/10);
		tab[x][y+2] = 48+(int)(valeur%10);
	}
	else if(valeur>9){
		tab[x][y+centre] = 48+(int)(valeur/10);
		tab[x][y+1+centre] = 48+(int)(valeur%10);
	}
	else{
		tab[x][y+centre] = 48+(int)(valeur%10);
	}
}

void Menu::afficher() {
	for(int i=0;i<25;i++) {
		for(int j=0;j<10;j++) {
			this->getEcranV()->afficherCaractere(i, 70+j,JAUNE,NOIR,(char) tab[i][j]);
		}
	}
}

void Menu::initialiserSalementLeMenu(){
	tab[0][0] = 218;
	tab[0][1] = 196;
	tab[0][2] = 196;
	//MENU
	tab[0][3] = 77;
	tab[0][4] = 69;
	tab[0][5] = 78;
	tab[0][6] = 85;

	tab[0][7] = 196;
	tab[0][8] = 196;
	tab[0][9] = 191;

	tab[1][0] = 179;
	//Or:
	tab[1][1] = 79;
	tab[1][2] = 114;
	tab[1][3] = 58;
	tab[1][4] = 32;
	tab[1][5] = 32;
	tab[1][6] = 32;
	tab[1][7] = 32;
	tab[1][8] = 32;
	tab[1][9] = 179;

	tab[2][0] = 179;
	//Bois:
	tab[2][1] = 66;
	tab[2][2] = 111;
	tab[2][3] = 105;
	tab[2][4] = 115;
	tab[2][5] = 58;
	tab[2][6] = 32;
	tab[2][7] = 32;
	tab[2][8] = 32;
	tab[2][9] = 179;

	tab[3][0] = 179;
	//Pop:
	tab[3][1] = 80;
	tab[3][2] = 111;
	tab[3][3] = 112;
	tab[3][4] = 58;
	tab[3][5] = 32;
	tab[3][6] = 32;
	tab[3][7] = 32;
	tab[3][8] = 32;
	tab[3][9] = 179;

	tab[4][0] = 195;
	tab[4][1] = 196;
	tab[4][2] = 196;
	tab[4][3] = 196;
	tab[4][4] = 196;
	tab[4][5] = 196;
	tab[4][6] = 196;
	tab[4][7] = 196;
	tab[4][8] = 196;
	tab[4][9] = 180;

	tab[5][0] = 195;
	tab[5][1] = 67;
	tab[5][2] = 114;
	tab[5][3] = 130;
	tab[5][4] = 97;
	tab[5][5] = 116;
	tab[5][6] = 105;
	tab[5][7] = 111;
	tab[5][8] = 110;
	tab[5][9] = 180;

	tab[6][0] = 195;
	tab[6][1] = 196;
	tab[6][2] = 196;
	tab[6][3] = 196;
	tab[6][4] = 194;
	tab[6][5] = 194;
	tab[6][6] = 196;
	tab[6][7] = 196;
	tab[6][8] = 196;
	tab[6][9] = 180;

	tab[7][0] = 179;
	tab[7][1] = 32;
	tab[7][2] = 1;
	tab[7][3] = 32;
	tab[7][4] = 179;
	tab[7][5] = 179;
	tab[7][6] = 32;
	tab[7][7] = 2;
	tab[7][8] = 32;
	tab[7][9] = 179;

	tab[8][0] = 179;
	tab[8][1] = 80;
	tab[8][2] = 97;
	tab[8][3] = 121;
	tab[8][4] = 179;
	tab[8][5] = 179;
	tab[8][6] = 71;
	tab[8][7] = 117;
	tab[8][8] = 101;
	tab[8][9] = 179;

	tab[9][0] = 179;
	tab[9][1] = 32;
	tab[9][2] = 32;
	tab[9][3] = 32;
	tab[9][4] = 179;
	tab[9][5] = 179;
	tab[9][6] = 32;
	tab[9][7] = 32;
	tab[9][8] = 32;
	tab[9][9] = 179;

	tab[10][0] = 195;
	tab[10][1] = 196;
	tab[10][2] = 196;
	tab[10][3] = 196;
	tab[10][4] = 193;
	tab[10][5] = 193;
	tab[10][6] = 196;
	tab[10][7] = 196;
	tab[10][8] = 196;
	tab[10][9] = 180;

	//menu bat/unit

	tab[11][0] = 179;
	tab[11][1] = 32;
	tab[11][2] = 32;
	tab[11][3] = 32;
	tab[11][4] = 32;
	tab[11][5] = 32;
	tab[11][6] = 32;
	tab[11][7] = 32;
	tab[11][8] = 32;
	tab[11][9] = 179;

	tab[12][0] = 179;
	tab[12][1] = 32;
	tab[12][2] = 32;
	tab[12][3] = 32;
	tab[12][4] = 32;
	tab[12][5] = 32;
	tab[12][6] = 32;
	tab[12][7] = 32;
	tab[12][8] = 32;
	tab[12][9] = 179;

	tab[13][0] = 179;
	tab[13][1] = 32;
	tab[13][2] = 32;
	tab[13][3] = 32;
	tab[13][4] = 32;
	tab[13][5] = 32;
	tab[13][6] = 32;
	tab[13][7] = 32;
	tab[13][8] = 32;
	tab[13][9] = 179;

	tab[14][0] = 179;
	tab[14][1] = 32;
	tab[14][2] = 32;
	tab[14][3] = 32;
	tab[14][4] = 32;
	tab[14][5] = 32;
	tab[14][6] = 32;
	tab[14][7] = 32;
	tab[14][8] = 32;
	tab[14][9] = 179;

	tab[15][0] = 179;
	tab[15][1] = 32;
	tab[15][2] = 32;
	tab[15][3] = 32;
	tab[15][4] = 32;
	tab[15][5] = 32;
	tab[15][6] = 32;
	tab[15][7] = 32;
	tab[15][8] = 32;
	tab[15][9] = 179;

	tab[16][0] = 179;
	tab[16][1] = 32;
	tab[16][2] = 32;
	tab[16][3] = 32;
	tab[16][4] = 32;
	tab[16][5] = 32;
	tab[16][6] = 32;
	tab[16][7] = 32;
	tab[16][8] = 32;
	tab[16][9] = 179;

	tab[17][0] = 179;
	tab[17][1] = 32;
	tab[17][2] = 32;
	tab[17][3] = 32;
	tab[17][4] = 32;
	tab[17][5] = 32;
	tab[17][6] = 32;
	tab[17][7] = 32;
	tab[17][8] = 32;
	tab[17][9] = 179;

	tab[18][0] = 179;
	tab[18][1] = 32;
	tab[18][2] = 32;
	tab[18][3] = 32;
	tab[18][4] = 32;
	tab[18][5] = 32;
	tab[18][6] = 32;
	tab[18][7] = 32;
	tab[18][8] = 32;
	tab[18][9] = 179;

	tab[19][0] = 179;
	tab[19][1] = 32;
	tab[19][2] = 32;
	tab[19][3] = 32;
	tab[19][4] = 32;
	tab[19][5] = 32;
	tab[19][6] = 32;
	tab[19][7] = 32;
	tab[19][8] = 32;
	tab[19][9] = 179;

	tab[20][0] = 179;
	tab[20][1] = 32;
	tab[20][2] = 32;
	tab[20][3] = 32;
	tab[20][4] = 32;
	tab[20][5] = 32;
	tab[20][6] = 32;
	tab[20][7] = 32;
	tab[20][8] = 32;
	tab[20][9] = 179;

	tab[21][0] = 195;
	tab[21][1] = 196;
	tab[21][2] = 196;
	tab[21][3] = 196;
	tab[21][4] = 196;
	tab[21][5] = 196;
	tab[21][6] = 196;
	tab[21][7] = 196;
	tab[21][8] = 196;
	tab[21][9] = 180;

	tab[22][0] = 179;
	tab[22][1] = 87;
	tab[22][2] = 97;
	tab[22][3] = 114;
	tab[22][4] = 99;
	tab[22][5] = 114;
	tab[22][6] = 97;
	tab[22][7] = 102;
	tab[22][8] = 116;
	tab[22][9] = 179;

	tab[23][0] = 179;
	tab[23][1] = 32;
	tab[23][2] = 32;
	tab[23][3] = 86;
	tab[23][4] = 49;
	tab[23][5] = 46;
	tab[23][6] = 48;
	tab[23][7] = 32;
	tab[23][8] = 32;
	tab[23][9] = 179;

	tab[24][0] = 192;
	tab[24][1] = 196;
	tab[24][2] = 196;
	tab[24][3] = 196;
	tab[24][4] = 196;
	tab[24][5] = 196;
	tab[24][6] = 196;
	tab[24][7] = 196;
	tab[24][8] = 196;
	tab[24][9] = 217;
}
