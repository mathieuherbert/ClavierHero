#include "Dijkstra.h"
#define INFINITY 999

int Dijkstra::adjMatrix[23][23][4];

Dijkstra::Dijkstra() {

	this->generer();

}


void Dijkstra::initialize(int sourceX, int sourceY, int destX, int destY){

	this->destX = destX;
	this->destY = destY;

	this->sourceX = sourceX;
	this->sourceY = sourceY;

    for(int x=0;x<23;x++) {

    	for(int y = 0;y<23;y++) {
			mark[x][y] = false;

			predecessor[x][y] = -1;

			distance[x][y] = INFINITY;
    	}

    }

    distance[sourceX][sourceY]= 0;

}


int* Dijkstra::getClosestUnmarkedNode(){

    int minDistance = INFINITY;

    int closestUnmarkedNode[2];


    for(int x=0;x<23;x++) {

    	for(int y = 0;y<23;y++) {

            if((!mark[x][y]) && ( minDistance >= distance[x][y])) {

            	minDistance = distance[x][y];
            	closestUnmarkedNode[0] = x;
            	closestUnmarkedNode[1] = y;

            	if(minDistance == 1)
            		return closestUnmarkedNode;

            }

    	}

    }

    return closestUnmarkedNode;

}


void Dijkstra::calculateDistance(){

    int* closestUnmarkedNode;

    int count = 0;

    int notMarked = numberNotMarked();

    while(count < notMarked) {

        closestUnmarkedNode = getClosestUnmarkedNode();

        int xclose = closestUnmarkedNode[0];
        int yclose = closestUnmarkedNode[1];

        mark[xclose][yclose] = true;
        notMarked--;
       // PortSerie p;

        for(int dir=0;dir<=3;dir++) {

        	int x = xclose;
        	int y = yclose;
        	//p.ecrireMot("Test de dir = ");
        	//p.afficherChiffre(dir);

        	switch(dir) {
				case 0:
					x++;
					break;
				case 1:
					x--;
					break;
				case 2:
					y++;
					break;
				case 3:
					y--;
					break;
        	}

			if((!mark[x][y]) && (adjMatrix[xclose][yclose][dir]>0) ) {

		    	/*p.ecrireMot("Test du noeud ");
				p.afficherChiffre(xclose);
				p.ecrireMot(";");
				p.afficherChiffre(yclose);
				p.ecrireMot("\n");*/

				if(distance[x][y] > distance[xclose][yclose]+adjMatrix[xclose][yclose][dir]) {

					distance[x][y] = distance[xclose][yclose]+adjMatrix[xclose][yclose][dir];
					predecessor[x][y] = xclose*1000+yclose;


					// FIN DE L'ALGO
					if(x == destX && y == destY)
						return;

					/*p.ecrireMot("Predecesseur de ");
					p.afficherChiffre(x);
					p.ecrireMot(";");
					p.afficherChiffre(y);
					p.ecrireMot(" = ");
					p.afficherChiffre(predecessor[x][y]);
					p.ecrireMot("\n");*/

				}

			}

        }

        count++;

    }

}


void Dijkstra::printPath(int x, int y){

	PortSerie p;

    if(x == sourceX && y == sourceY) {

    	p.ecrireMot("Chemin trouvé !");
    	p.afficherChiffre(x);
    	p.ecrireMot(";y=");
    	p.afficherChiffre(y);


    }
    else if(predecessor[x][y] == -1) {

       p.ecrireMot("Chemin pas trouvé");
    }

    else {

    	p.ecrireMot("Chemin passé par :");
    	p.afficherChiffre(x);
    	p.ecrireMot(";y=");
    	p.afficherChiffre(y);

        printPath((int)(predecessor[x][y]/1000), (int)(predecessor[x][y]%1000));

        //Chemin trouvé;

    }

}


int Dijkstra::nextPosition(int x, int y) {
	PortSerie p;

	p.ecrireMot("Test du predecesseur de x=");
	p.afficherChiffre(x);
	p.ecrireMot(";y=");
	p.afficherChiffre(y);
	p.ecrireMot(";p=");
	p.afficherChiffre(predecessor[x][y]);
	p.ecrireMot("---------------");

	if(predecessor[x][y] == -1)
		return predecessor[x][y];

	if((int)(predecessor[x][y]/1000) == sourceX && predecessor[x][y]%1000 == sourceY) {
		return x*1000+y;
	}
	else
		return nextPosition((int)(predecessor[x][y]/1000), predecessor[x][y]%1000);

}

void Dijkstra::output(){

    /*for(int i=0;i<numOfVertices;i++) {

        if(i == source)

            //cout<<(char)(source + 97)<<".."<<source;

        else

            printPath(i);

        //cout<<"->"<<distance[i]<<endl;

    }
*/
}

int Dijkstra::numberNotMarked() {

	int count = 0;

    for(int x=0;x<23;x++) {

    	for(int y = 0;y<23;y++) {
    		if(!mark[x][y])
    			count++;
    	}

    }

    return count;
}

int main() {


    //G.read();

    //cout << G.adjMatrix[22][23][21][23];

    //G.calculateDistance();

    //G.printPath(21,20);

    return 0;

}
