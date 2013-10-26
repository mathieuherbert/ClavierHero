#include "config.h"
#include "CasePacman.h"

class NiveauPacman{
public :



	static void generer(PlateauPacman* plateau){
		//Case niveau[HAUTEUR-2][LARGEUR-2];
		for (int j=0;j<HAUTEUR;j++){
			for(int i=0;i<LARGEUR;i++){
				(plateau->tab)[j][i].init(j,i,plateau->ecran);
			}
		}

		for (int j=1;j<23;j++){
			for(int i=29;i<51;i++){
			(plateau->tab)[j][i].setCaseFruit();
							}
		}


		//TELEPORTATION
		(plateau->tab)[11][28].setCaseTeleportG();
		(plateau->tab)[11][51].setCaseTeleportD();


		(plateau->tab)[10][39].setCaseVide();
		(plateau->tab)[10][40].setCaseVide();

		(plateau->tab)[11][37].setCaseVide();
		(plateau->tab)[11][38].setCaseVide();
		(plateau->tab)[11][39].setCaseVide();
		(plateau->tab)[11][40].setCaseVide();
		(plateau->tab)[11][41].setCaseVide();
		(plateau->tab)[11][42].setCaseVide();
		(plateau->tab)[11][43].setCaseVide();

		(plateau->tab)[12][37].setCaseVide();
		(plateau->tab)[12][38].setCaseVide();
		(plateau->tab)[12][39].setCaseVide();
		(plateau->tab)[12][40].setCaseVide();
		(plateau->tab)[12][41].setCaseVide();
		(plateau->tab)[12][42].setCaseVide();
		(plateau->tab)[12][43].setCaseVide();


		(plateau->tab)[1][28].setCaseMur();
		(plateau->tab)[1][29].setCaseMur();
		(plateau->tab)[1][30].setCaseMur();
		(plateau->tab)[1][31].setCaseMur();
		(plateau->tab)[1][32].setCaseMur();
		(plateau->tab)[1][33].setCaseMur();
		(plateau->tab)[1][34].setCaseMur();
		(plateau->tab)[1][35].setCaseMur();
		(plateau->tab)[1][36].setCaseMur();
		(plateau->tab)[1][37].setCaseMur();
		(plateau->tab)[1][38].setCaseMur();
		(plateau->tab)[1][39].setCaseMur();

		(plateau->tab)[1][40].setCaseMur();
		(plateau->tab)[1][41].setCaseMur();
		(plateau->tab)[1][42].setCaseMur();
		(plateau->tab)[1][43].setCaseMur();
		(plateau->tab)[1][44].setCaseMur();

		(plateau->tab)[1][45].setCaseMur();
		(plateau->tab)[1][46].setCaseMur();
		(plateau->tab)[1][47].setCaseMur();

		(plateau->tab)[1][48].setCaseMur();
		(plateau->tab)[1][49].setCaseMur();
		(plateau->tab)[1][50].setCaseMur();
		(plateau->tab)[1][51].setCaseMur();

		(plateau->tab)[2][28].setCaseMur();
		(plateau->tab)[2][39].setCaseMur();

		(plateau->tab)[2][40].setCaseMur();
		(plateau->tab)[2][51].setCaseMur();
		(plateau->tab)[3][28].setCaseMur();

		(plateau->tab)[3][30].setCaseMur();
		(plateau->tab)[3][31].setCaseMur();
		(plateau->tab)[3][32].setCaseMur();
		(plateau->tab)[3][34].setCaseMur();
		(plateau->tab)[3][35].setCaseMur();
		(plateau->tab)[3][36].setCaseMur();
		(plateau->tab)[3][37].setCaseMur();
		(plateau->tab)[3][39].setCaseMur();

		(plateau->tab)[3][40].setCaseMur();
		(plateau->tab)[3][42].setCaseMur();
		(plateau->tab)[3][43].setCaseMur();
		(plateau->tab)[3][44].setCaseMur();

		(plateau->tab)[3][45].setCaseMur();
		(plateau->tab)[3][47].setCaseMur();

		(plateau->tab)[3][48].setCaseMur();
		(plateau->tab)[3][49].setCaseMur();

		(plateau->tab)[3][51].setCaseMur();
		(plateau->tab)[4][28].setCaseMur();

		(plateau->tab)[4][30].setCaseMur();
		(plateau->tab)[4][31].setCaseMur();
		(plateau->tab)[4][32].setCaseMur();
		(plateau->tab)[4][34].setCaseMur();
		(plateau->tab)[4][35].setCaseMur();
		(plateau->tab)[4][36].setCaseMur();
		(plateau->tab)[4][37].setCaseMur();
		(plateau->tab)[4][39].setCaseMur();

		(plateau->tab)[4][40].setCaseMur();
		(plateau->tab)[4][42].setCaseMur();
		(plateau->tab)[4][43].setCaseMur();
		(plateau->tab)[4][44].setCaseMur();
		(plateau->tab)[4][45].setCaseMur();
		(plateau->tab)[4][47].setCaseMur();
		(plateau->tab)[4][48].setCaseMur();
		(plateau->tab)[4][49].setCaseMur();

		(plateau->tab)[4][51].setCaseMur();
		(plateau->tab)[5][28].setCaseMur();

		(plateau->tab)[5][51].setCaseMur();
		(plateau->tab)[6][28].setCaseMur();
		(plateau->tab)[6][30].setCaseMur();
		(plateau->tab)[6][31].setCaseMur();

		(plateau->tab)[6][32].setCaseMur();
		(plateau->tab)[6][34].setCaseMur();
		(plateau->tab)[6][36].setCaseMur();
		(plateau->tab)[6][37].setCaseMur();

		(plateau->tab)[6][38].setCaseMur();
		(plateau->tab)[6][39].setCaseMur();

		(plateau->tab)[6][40].setCaseMur();
		(plateau->tab)[6][41].setCaseMur();
		(plateau->tab)[6][42].setCaseMur();
		(plateau->tab)[6][43].setCaseMur();

		(plateau->tab)[6][45].setCaseMur();
		(plateau->tab)[6][47].setCaseMur();
		(plateau->tab)[6][48].setCaseMur();
		(plateau->tab)[6][49].setCaseMur();

		(plateau->tab)[6][51].setCaseMur();
		(plateau->tab)[7][28].setCaseMur();
		(plateau->tab)[7][34].setCaseMur();

		(plateau->tab)[7][38].setCaseMur();
		(plateau->tab)[7][39].setCaseMur();

		(plateau->tab)[7][40].setCaseMur();
		(plateau->tab)[7][41].setCaseMur();
		(plateau->tab)[7][45].setCaseMur();
		(plateau->tab)[7][51].setCaseMur();

		(plateau->tab)[8][28].setCaseMur();
		(plateau->tab)[8][29].setCaseMur();

		(plateau->tab)[8][30].setCaseMur();
		(plateau->tab)[8][31].setCaseMur();
		(plateau->tab)[8][32].setCaseMur();
		(plateau->tab)[8][34].setCaseMur();
		(plateau->tab)[8][35].setCaseMur();
		(plateau->tab)[8][36].setCaseMur();
		(plateau->tab)[8][38].setCaseMur();
		(plateau->tab)[8][39].setCaseMur();

		(plateau->tab)[8][40].setCaseMur();
		(plateau->tab)[8][41].setCaseMur();
		(plateau->tab)[8][43].setCaseMur();
		(plateau->tab)[8][44].setCaseMur();
		(plateau->tab)[8][45].setCaseMur();
		(plateau->tab)[8][47].setCaseMur();
		(plateau->tab)[8][48].setCaseMur();
		(plateau->tab)[8][49].setCaseMur();
		(plateau->tab)[8][50].setCaseMur();

		(plateau->tab)[8][51].setCaseMur();
		(plateau->tab)[9][28].setCaseMur();
		(plateau->tab)[9][29].setCaseMur();
		(plateau->tab)[9][30].setCaseMur();
		(plateau->tab)[9][31].setCaseMur();

		(plateau->tab)[9][32].setCaseMur();
		(plateau->tab)[9][34].setCaseMur();
		(plateau->tab)[9][45].setCaseMur();
		(plateau->tab)[9][47].setCaseMur();
		(plateau->tab)[9][48].setCaseMur();
		(plateau->tab)[9][49].setCaseMur();
		(plateau->tab)[9][50].setCaseMur();
		(plateau->tab)[9][51].setCaseMur();

		(plateau->tab)[10][28].setCaseMur();
		(plateau->tab)[10][29].setCaseMur();
		(plateau->tab)[10][30].setCaseMur();
		(plateau->tab)[10][31].setCaseMur();

		(plateau->tab)[10][32].setCaseMur();
		(plateau->tab)[10][34].setCaseMur();
		(plateau->tab)[10][36].setCaseMur();
		(plateau->tab)[10][37].setCaseMur();
		(plateau->tab)[10][38].setCaseMur();
		(plateau->tab)[10][41].setCaseMur();

		(plateau->tab)[10][42].setCaseMur();
		(plateau->tab)[10][43].setCaseMur();
		(plateau->tab)[10][45].setCaseMur();
		(plateau->tab)[10][47].setCaseMur();
		(plateau->tab)[10][48].setCaseMur();
		(plateau->tab)[10][49].setCaseMur();

		(plateau->tab)[10][50].setCaseMur();
		(plateau->tab)[10][51].setCaseMur();

		(plateau->tab)[11][36].setCaseMur();
		(plateau->tab)[11][43].setCaseMur();
		(plateau->tab)[12][28].setCaseMur();
		(plateau->tab)[12][29].setCaseMur();

		(plateau->tab)[12][30].setCaseMur();
		(plateau->tab)[12][31].setCaseMur();
		(plateau->tab)[12][32].setCaseMur();
		(plateau->tab)[12][34].setCaseMur();
		(plateau->tab)[12][36].setCaseMur();
		(plateau->tab)[12][43].setCaseMur();
		(plateau->tab)[12][45].setCaseMur();

		(plateau->tab)[12][47].setCaseMur();
		(plateau->tab)[12][48].setCaseMur();
		(plateau->tab)[12][49].setCaseMur();
		(plateau->tab)[12][50].setCaseMur();

		(plateau->tab)[12][51].setCaseMur();
		(plateau->tab)[13][28].setCaseMur();
		(plateau->tab)[13][29].setCaseMur();
		(plateau->tab)[13][30].setCaseMur();
		(plateau->tab)[13][31].setCaseMur();

		(plateau->tab)[13][32].setCaseMur();
		(plateau->tab)[13][34].setCaseMur();
		(plateau->tab)[13][36].setCaseMur();
		(plateau->tab)[13][37].setCaseMur();
		(plateau->tab)[13][38].setCaseMur();
		(plateau->tab)[13][39].setCaseMur();

		(plateau->tab)[13][40].setCaseMur();
		(plateau->tab)[13][41].setCaseMur();
		(plateau->tab)[13][42].setCaseMur();

		(plateau->tab)[13][43].setCaseMur();
		(plateau->tab)[13][45].setCaseMur();
		(plateau->tab)[13][47].setCaseMur();
		(plateau->tab)[13][48].setCaseMur();
		(plateau->tab)[13][49].setCaseMur();

		(plateau->tab)[13][50].setCaseMur();
		(plateau->tab)[13][51].setCaseMur();
		(plateau->tab)[14][28].setCaseMur();
		(plateau->tab)[14][29].setCaseMur();

		(plateau->tab)[14][30].setCaseMur();
		(plateau->tab)[14][31].setCaseMur();
		(plateau->tab)[14][32].setCaseMur();
		(plateau->tab)[14][34].setCaseMur();
		(plateau->tab)[14][45].setCaseMur();
		(plateau->tab)[14][47].setCaseMur();
		(plateau->tab)[14][48].setCaseMur();
		(plateau->tab)[14][49].setCaseMur();

		(plateau->tab)[14][50].setCaseMur();
		(plateau->tab)[14][51].setCaseMur();

		(plateau->tab)[15][28].setCaseMur();
		(plateau->tab)[15][36].setCaseMur();

		(plateau->tab)[15][37].setCaseMur();
		(plateau->tab)[15][38].setCaseMur();
		(plateau->tab)[15][39].setCaseMur();

		(plateau->tab)[15][40].setCaseMur();
		(plateau->tab)[15][41].setCaseMur();

		(plateau->tab)[15][42].setCaseMur();
		(plateau->tab)[15][43].setCaseMur();

		(plateau->tab)[15][51].setCaseMur();
		(plateau->tab)[16][28].setCaseMur();
		(plateau->tab)[16][30].setCaseMur();
		(plateau->tab)[16][31].setCaseMur();

		(plateau->tab)[16][32].setCaseMur();
		(plateau->tab)[16][34].setCaseMur();
		(plateau->tab)[16][39].setCaseMur();

		(plateau->tab)[16][40].setCaseMur();
		(plateau->tab)[16][45].setCaseMur();
		(plateau->tab)[16][47].setCaseMur();

		(plateau->tab)[16][48].setCaseMur();
		(plateau->tab)[16][49].setCaseMur();

		(plateau->tab)[16][51].setCaseMur();
		(plateau->tab)[17][28].setCaseMur();

		(plateau->tab)[17][32].setCaseMur();
		(plateau->tab)[17][34].setCaseMur();
		(plateau->tab)[17][35].setCaseMur();

		(plateau->tab)[17][36].setCaseMur();
		(plateau->tab)[17][37].setCaseMur();
		(plateau->tab)[17][39].setCaseMur();

		(plateau->tab)[17][40].setCaseMur();
		(plateau->tab)[17][42].setCaseMur();
		(plateau->tab)[17][43].setCaseMur();
		(plateau->tab)[17][44].setCaseMur();
		(plateau->tab)[17][45].setCaseMur();
		(plateau->tab)[17][47].setCaseMur();

		(plateau->tab)[17][51].setCaseMur();
		(plateau->tab)[18][28].setCaseMur();
		(plateau->tab)[18][29].setCaseMur();

		(plateau->tab)[18][30].setCaseMur();
		(plateau->tab)[18][32].setCaseMur();

		(plateau->tab)[18][47].setCaseMur();
		(plateau->tab)[18][49].setCaseMur();

		(plateau->tab)[18][50].setCaseMur();
		(plateau->tab)[18][51].setCaseMur();

		(plateau->tab)[19][28].setCaseMur();
		(plateau->tab)[19][29].setCaseMur();
		(plateau->tab)[19][30].setCaseMur();
		(plateau->tab)[19][32].setCaseMur();

		(plateau->tab)[19][33].setCaseMur();
		(plateau->tab)[19][35].setCaseMur();

		(plateau->tab)[19][37].setCaseMur();
		(plateau->tab)[19][38].setCaseMur();
		(plateau->tab)[19][39].setCaseMur();
		(plateau->tab)[19][40].setCaseMur();
		(plateau->tab)[19][41].setCaseMur();
		(plateau->tab)[19][42].setCaseMur();
		(plateau->tab)[19][44].setCaseMur();
		(plateau->tab)[19][46].setCaseMur();
		(plateau->tab)[19][47].setCaseMur();
		(plateau->tab)[19][49].setCaseMur();
		(plateau->tab)[19][50].setCaseMur();
		(plateau->tab)[19][51].setCaseMur();

		(plateau->tab)[20][28].setCaseMur();
		(plateau->tab)[20][35].setCaseMur();

		(plateau->tab)[20][37].setCaseMur();
		(plateau->tab)[20][38].setCaseMur();
		(plateau->tab)[20][39].setCaseMur();

		(plateau->tab)[20][40].setCaseMur();
		(plateau->tab)[20][41].setCaseMur();
		(plateau->tab)[20][42].setCaseMur();
		(plateau->tab)[20][44].setCaseMur();

		(plateau->tab)[20][51].setCaseMur();
		(plateau->tab)[21][28].setCaseMur();
		(plateau->tab)[21][30].setCaseMur();

		(plateau->tab)[21][31].setCaseMur();
		(plateau->tab)[21][32].setCaseMur();
		(plateau->tab)[21][33].setCaseMur();
		(plateau->tab)[21][34].setCaseMur();
		(plateau->tab)[21][35].setCaseMur();
		(plateau->tab)[21][37].setCaseMur();

		(plateau->tab)[21][38].setCaseMur();
		(plateau->tab)[21][39].setCaseMur();
		(plateau->tab)[21][40].setCaseMur();
		(plateau->tab)[21][41].setCaseMur();

		(plateau->tab)[21][42].setCaseMur();
		(plateau->tab)[21][44].setCaseMur();
		(plateau->tab)[21][45].setCaseMur();
		(plateau->tab)[21][46].setCaseMur();
		(plateau->tab)[21][47].setCaseMur();
		(plateau->tab)[21][48].setCaseMur();
		(plateau->tab)[21][49].setCaseMur();
		(plateau->tab)[21][51].setCaseMur();

		(plateau->tab)[22][28].setCaseMur();
		(plateau->tab)[22][51].setCaseMur();

		(plateau->tab)[23][28].setCaseMur();
		(plateau->tab)[23][29].setCaseMur();
		(plateau->tab)[23][30].setCaseMur();
		(plateau->tab)[23][31].setCaseMur();
		(plateau->tab)[23][32].setCaseMur();
		(plateau->tab)[23][33].setCaseMur();
		(plateau->tab)[23][34].setCaseMur();
		(plateau->tab)[23][35].setCaseMur();
		(plateau->tab)[23][36].setCaseMur();
		(plateau->tab)[23][37].setCaseMur();
		(plateau->tab)[23][38].setCaseMur();
		(plateau->tab)[23][39].setCaseMur();
		(plateau->tab)[23][40].setCaseMur();
		(plateau->tab)[23][41].setCaseMur();
		(plateau->tab)[23][42].setCaseMur();
		(plateau->tab)[23][43].setCaseMur();

		(plateau->tab)[23][44].setCaseMur();
		(plateau->tab)[23][45].setCaseMur();

		(plateau->tab)[23][46].setCaseMur();
		(plateau->tab)[23][47].setCaseMur();
		(plateau->tab)[23][48].setCaseMur();
		(plateau->tab)[23][49].setCaseMur();

		(plateau->tab)[23][50].setCaseMur();
		(plateau->tab)[23][51].setCaseMur();




	}

};

