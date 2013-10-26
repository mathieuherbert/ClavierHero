#include <drivers/PortSerie.h>


#ifndef DIJKSTRA_H
#define DIJKSTRA_H


class Dijkstra{

    private:

        int predecessor[23][23],distance[23][23];

        bool mark[23][23]; //keep track of visited node

        int sourceX, sourceY, destX, destY;

        int numOfVertices;

    public:

        static int adjMatrix[23][23][4];

        int nextPosition(int, int);

        Dijkstra();

        static void generer() {

        	adjMatrix[1][1][0] = 1;
        	adjMatrix[1][1][2] = 1;

        	adjMatrix[1][2][2] = 1;
        	adjMatrix[1][2][3] = 1;

        	adjMatrix[1][3][2] = 1;
        	adjMatrix[1][3][3] = 1;

        	adjMatrix[1][4][2] = 1;
        	adjMatrix[1][4][3] = 1;

        	adjMatrix[1][5][0] = 1;
        	adjMatrix[1][5][2] = 1;
        	adjMatrix[1][5][3] = 1;

        	adjMatrix[1][6][2] = 1;
        	adjMatrix[1][6][3] = 1;

        	adjMatrix[1][7][2] = 1;
        	adjMatrix[1][7][3] = 1;

        	adjMatrix[1][8][2] = 1;
        	adjMatrix[1][8][3] = 1;

        	adjMatrix[1][9][2] = 1;
        	adjMatrix[1][9][3] = 1;

        	adjMatrix[1][10][0] = 1;
        	adjMatrix[1][10][3] = 1;

        	adjMatrix[1][13][0] = 1;
        	adjMatrix[1][13][2] = 1;

        	adjMatrix[1][14][2] = 1;
        	adjMatrix[1][14][3] = 1;

        	adjMatrix[1][15][2] = 1;
        	adjMatrix[1][15][3] = 1;

        	adjMatrix[1][16][2] = 1;
        	adjMatrix[1][16][3] = 1;

        	adjMatrix[1][17][2] = 1;
        	adjMatrix[1][17][3] = 1;

        	adjMatrix[1][18][0] = 1;
        	adjMatrix[1][18][2] = 1;
        	adjMatrix[1][18][3] = 1;

        	adjMatrix[1][19][2] = 1;
        	adjMatrix[1][19][3] = 1;

        	adjMatrix[1][20][2] = 1;
        	adjMatrix[1][20][3] = 1;

        	adjMatrix[1][21][2] = 1;
        	adjMatrix[1][21][3] = 1;

        	adjMatrix[1][22][0] = 1;
        	adjMatrix[1][22][3] = 1;

        	adjMatrix[2][1][0] = 1;
        	adjMatrix[2][1][1] = 1;

        	adjMatrix[2][5][0] = 1;
        	adjMatrix[2][5][1] = 1;

        	adjMatrix[2][10][0] = 1;
        	adjMatrix[2][10][1] = 1;

        	adjMatrix[2][13][0] = 1;
        	adjMatrix[2][13][1] = 1;

        	adjMatrix[2][18][0] = 1;
        	adjMatrix[2][18][1] = 1;

        	adjMatrix[2][22][0] = 1;
        	adjMatrix[2][22][1] = 1;

        	adjMatrix[3][1][0] = 1;
        	adjMatrix[3][1][1] = 1;

        	adjMatrix[3][5][0] = 1;
        	adjMatrix[3][5][1] = 1;

        	adjMatrix[3][10][0] = 1;
        	adjMatrix[3][10][1] = 1;

        	adjMatrix[3][13][0] = 1;
        	adjMatrix[3][13][1] = 1;

        	adjMatrix[3][18][0] = 1;
        	adjMatrix[3][18][1] = 1;

        	adjMatrix[3][22][0] = 1;
        	adjMatrix[3][22][1] = 1;

        	adjMatrix[4][1][0] = 1;
        	adjMatrix[4][1][1] = 1;
        	adjMatrix[4][1][2] = 1;

        	adjMatrix[4][2][2] = 1;
        	adjMatrix[4][2][3] = 1;

        	adjMatrix[4][3][2] = 1;
        	adjMatrix[4][3][3] = 1;

        	adjMatrix[4][4][2] = 1;
        	adjMatrix[4][4][3] = 1;

        	adjMatrix[4][5][0] = 1;
        	adjMatrix[4][5][1] = 1;
        	adjMatrix[4][5][2] = 1;
        	adjMatrix[4][5][3] = 1;

        	adjMatrix[4][6][2] = 1;
        	adjMatrix[4][6][3] = 1;

        	adjMatrix[4][7][0] = 1;
        	adjMatrix[4][7][2] = 1;
        	adjMatrix[4][7][3] = 1;

        	adjMatrix[4][8][2] = 1;
        	adjMatrix[4][8][3] = 1;

        	adjMatrix[4][9][2] = 1;
        	adjMatrix[4][9][3] = 1;

        	adjMatrix[4][10][1] = 1;
        	adjMatrix[4][10][2] = 1;
        	adjMatrix[4][10][3] = 1;

        	adjMatrix[4][11][2] = 1;
        	adjMatrix[4][11][3] = 1;

        	adjMatrix[4][12][2] = 1;
        	adjMatrix[4][12][3] = 1;

        	adjMatrix[4][13][1] = 1;
        	adjMatrix[4][13][2] = 1;
        	adjMatrix[4][13][3] = 1;

        	adjMatrix[4][14][2] = 1;
        	adjMatrix[4][14][3] = 1;

        	adjMatrix[4][15][2] = 1;
        	adjMatrix[4][15][3] = 1;

        	adjMatrix[4][16][0] = 1;
        	adjMatrix[4][16][2] = 1;
        	adjMatrix[4][16][3] = 1;

        	adjMatrix[4][17][2] = 1;
        	adjMatrix[4][17][3] = 1;

        	adjMatrix[4][18][0] = 1;
        	adjMatrix[4][18][1] = 1;
        	adjMatrix[4][18][2] = 1;
        	adjMatrix[4][18][3] = 1;

        	adjMatrix[4][19][2] = 1;
        	adjMatrix[4][19][3] = 1;

        	adjMatrix[4][20][2] = 1;
        	adjMatrix[4][20][3] = 1;

        	adjMatrix[4][21][2] = 1;
        	adjMatrix[4][21][3] = 1;

        	adjMatrix[4][22][0] = 1;
        	adjMatrix[4][22][1] = 1;
        	adjMatrix[4][22][3] = 1;

        	adjMatrix[5][1][0] = 1;
        	adjMatrix[5][1][1] = 1;

        	adjMatrix[5][5][0] = 1;
        	adjMatrix[5][5][1] = 1;

        	adjMatrix[5][7][0] = 1;
        	adjMatrix[5][7][1] = 1;

        	adjMatrix[5][16][0] = 1;
        	adjMatrix[5][16][1] = 1;

        	adjMatrix[5][18][0] = 1;
        	adjMatrix[5][18][1] = 1;

        	adjMatrix[5][22][0] = 1;
        	adjMatrix[5][22][1] = 1;

        	adjMatrix[6][1][1] = 1;
        	adjMatrix[6][1][2] = 1;

        	adjMatrix[6][2][2] = 1;
        	adjMatrix[6][2][3] = 1;

        	adjMatrix[6][3][2] = 1;
        	adjMatrix[6][3][3] = 1;

        	adjMatrix[6][4][2] = 1;
        	adjMatrix[6][4][3] = 1;

        	adjMatrix[6][5][0] = 1;
        	adjMatrix[6][5][1] = 1;
        	adjMatrix[6][5][3] = 1;

        	adjMatrix[6][7][1] = 1;
        	adjMatrix[6][7][2] = 1;

        	adjMatrix[6][8][2] = 1;
        	adjMatrix[6][8][3] = 1;

        	adjMatrix[6][9][0] = 1;
        	adjMatrix[6][9][3] = 1;

        	adjMatrix[6][14][0] = 1;
        	adjMatrix[6][14][2] = 1;

        	adjMatrix[6][15][2] = 1;
        	adjMatrix[6][15][3] = 1;

        	adjMatrix[6][16][1] = 1;
        	adjMatrix[6][16][3] = 1;

        	adjMatrix[6][18][0] = 1;
        	adjMatrix[6][18][1] = 1;
        	adjMatrix[6][18][2] = 1;

        	adjMatrix[6][19][2] = 1;
        	adjMatrix[6][19][3] = 1;

        	adjMatrix[6][20][2] = 1;
        	adjMatrix[6][20][3] = 1;

        	adjMatrix[6][21][2] = 1;
        	adjMatrix[6][21][3] = 1;

        	adjMatrix[6][22][1] = 1;
        	adjMatrix[6][22][3] = 1;

        	adjMatrix[7][5][0] = 1;
        	adjMatrix[7][5][1] = 1;

        	adjMatrix[7][9][0] = 1;
        	adjMatrix[7][9][1] = 1;

        	adjMatrix[7][14][0] = 1;
        	adjMatrix[7][14][1] = 1;

        	adjMatrix[7][18][0] = 1;
        	adjMatrix[7][18][1] = 1;

        	adjMatrix[8][5][0] = 1;
        	adjMatrix[8][5][1] = 1;

        	adjMatrix[8][7][0] = 1;
        	adjMatrix[8][7][2] = 1;

        	adjMatrix[8][8][2] = 1;
        	adjMatrix[8][8][3] = 1;

        	adjMatrix[8][9][1] = 1;
        	adjMatrix[8][9][2] = 1;
        	adjMatrix[8][9][3] = 1;

        	adjMatrix[8][10][2] = 1;
        	adjMatrix[8][10][3] = 1;

        	adjMatrix[8][11][0] = 1;
        	adjMatrix[8][11][2] = 1;
        	adjMatrix[8][11][3] = 1;

        	adjMatrix[8][12][0] = 1;
        	adjMatrix[8][12][2] = 1;
        	adjMatrix[8][12][3] = 1;

        	adjMatrix[8][13][2] = 1;
        	adjMatrix[8][13][3] = 1;

        	adjMatrix[8][14][1] = 1;
        	adjMatrix[8][14][2] = 1;
        	adjMatrix[8][14][3] = 1;

        	adjMatrix[8][15][2] = 1;
        	adjMatrix[8][15][3] = 1;

        	adjMatrix[8][16][0] = 1;
        	adjMatrix[8][16][3] = 1;

        	adjMatrix[8][18][0] = 1;
        	adjMatrix[8][18][1] = 1;

        	adjMatrix[9][5][0] = 1;
        	adjMatrix[9][5][1] = 1;

        	adjMatrix[9][7][0] = 1;
        	adjMatrix[9][7][1] = 1;

        	adjMatrix[9][11][0] = 1;
        	adjMatrix[9][11][1] = 1;
        	adjMatrix[9][11][2] = 1;

        	adjMatrix[9][12][0] = 1;
        	adjMatrix[9][12][1] = 1;
        	adjMatrix[9][12][3] = 1;

        	adjMatrix[9][16][0] = 1;
        	adjMatrix[9][16][1] = 1;

        	adjMatrix[9][18][0] = 1;
        	adjMatrix[9][18][1] = 1;

        	//adjMatrix[10][0][2] = 1;
        	//adjMatrix[10][0][3] = 1;

        	adjMatrix[10][1][2] = 1;
        	adjMatrix[10][1][3] = 1;

        	adjMatrix[10][2][2] = 1;
        	adjMatrix[10][2][3] = 1;

        	adjMatrix[10][3][2] = 1;
        	adjMatrix[10][3][3] = 1;

        	adjMatrix[10][4][2] = 1;
        	adjMatrix[10][4][3] = 1;

        	adjMatrix[10][5][0] = 1;
        	adjMatrix[10][5][1] = 1;
        	adjMatrix[10][5][2] = 1;
        	adjMatrix[10][5][3] = 1;

        	adjMatrix[10][6][2] = 1;
        	adjMatrix[10][6][3] = 1;

        	adjMatrix[10][7][0] = 1;
        	adjMatrix[10][7][1] = 1;
        	adjMatrix[10][7][3] = 1;

        	adjMatrix[10][9][0] = 1;
        	adjMatrix[10][9][2] = 1;

        	adjMatrix[10][10][0] = 1;
        	adjMatrix[10][10][2] = 1;
        	adjMatrix[10][10][3] = 1;

        	adjMatrix[10][11][0] = 1;
        	adjMatrix[10][11][1] = 1;
        	adjMatrix[10][11][2] = 1;
        	adjMatrix[10][11][3] = 1;

        	adjMatrix[10][12][0] = 1;
        	adjMatrix[10][12][1] = 1;
        	adjMatrix[10][12][2] = 1;
        	adjMatrix[10][12][3] = 1;

        	adjMatrix[10][13][0] = 1;
        	adjMatrix[10][13][2] = 1;
        	adjMatrix[10][13][3] = 1;

        	adjMatrix[10][14][0] = 1;
        	adjMatrix[10][14][3] = 1;

        	adjMatrix[10][16][0] = 1;
        	adjMatrix[10][16][1] = 1;
        	adjMatrix[10][16][2] = 1;

        	adjMatrix[10][17][2] = 1;
        	adjMatrix[10][17][3] = 1;

        	adjMatrix[10][18][0] = 1;
        	adjMatrix[10][18][1] = 1;
        	adjMatrix[10][18][2] = 1;
        	adjMatrix[10][18][3] = 1;

        	adjMatrix[10][19][2] = 1;
        	adjMatrix[10][19][3] = 1;

        	adjMatrix[10][20][2] = 1;
        	adjMatrix[10][20][3] = 1;

        	adjMatrix[10][21][2] = 1;
        	adjMatrix[10][21][3] = 1;

        	adjMatrix[10][22][2] = 1;
        	adjMatrix[10][22][3] = 1;

        	//adjMatrix[10][23][2] = 1;
        	//adjMatrix[10][23][3] = 1;

        	adjMatrix[11][5][0] = 1;
        	adjMatrix[11][5][1] = 1;

        	adjMatrix[11][7][0] = 1;
        	adjMatrix[11][7][1] = 1;

        	adjMatrix[11][9][1] = 1;
        	adjMatrix[11][9][2] = 1;

        	adjMatrix[11][10][1] = 1;
        	adjMatrix[11][10][2] = 1;
        	adjMatrix[11][10][3] = 1;

        	adjMatrix[11][11][1] = 1;
        	adjMatrix[11][11][2] = 1;
        	adjMatrix[11][11][3] = 1;

        	adjMatrix[11][12][1] = 1;
        	adjMatrix[11][12][2] = 1;
        	adjMatrix[11][12][3] = 1;

        	adjMatrix[11][13][1] = 1;
        	adjMatrix[11][13][2] = 1;
        	adjMatrix[11][13][3] = 1;

        	adjMatrix[11][14][1] = 1;
        	adjMatrix[11][14][3] = 1;

        	adjMatrix[11][16][0] = 1;
        	adjMatrix[11][16][1] = 1;

        	adjMatrix[11][18][0] = 1;
        	adjMatrix[11][18][1] = 1;

        	adjMatrix[12][5][0] = 1;
        	adjMatrix[12][5][1] = 1;

        	adjMatrix[12][7][0] = 1;
        	adjMatrix[12][7][1] = 1;

        	adjMatrix[12][16][0] = 1;
        	adjMatrix[12][16][1] = 1;

        	adjMatrix[12][18][0] = 1;
        	adjMatrix[12][18][1] = 1;

        	adjMatrix[13][5][0] = 1;
        	adjMatrix[13][5][1] = 1;

        	adjMatrix[13][7][0] = 1;
        	adjMatrix[13][7][1] = 1;
        	adjMatrix[13][7][2] = 1;

        	adjMatrix[13][8][2] = 1;
        	adjMatrix[13][8][3] = 1;

        	adjMatrix[13][9][2] = 1;
        	adjMatrix[13][9][3] = 1;

        	adjMatrix[13][10][2] = 1;
        	adjMatrix[13][10][3] = 1;

        	adjMatrix[13][11][2] = 1;
        	adjMatrix[13][11][3] = 1;

        	adjMatrix[13][12][2] = 1;
        	adjMatrix[13][12][3] = 1;

        	adjMatrix[13][13][2] = 1;
        	adjMatrix[13][13][3] = 1;

        	adjMatrix[13][14][2] = 1;
        	adjMatrix[13][14][3] = 1;

        	adjMatrix[13][15][2] = 1;
        	adjMatrix[13][15][3] = 1;

        	adjMatrix[13][16][0] = 1;
        	adjMatrix[13][16][1] = 1;
        	adjMatrix[13][16][3] = 1;

        	adjMatrix[13][18][0] = 1;
        	adjMatrix[13][18][1] = 1;

        	adjMatrix[14][1][0] = 1;
        	adjMatrix[14][1][2] = 1;

        	adjMatrix[14][2][2] = 1;
        	adjMatrix[14][2][3] = 1;

        	adjMatrix[14][3][2] = 1;
        	adjMatrix[14][3][3] = 1;

        	adjMatrix[14][4][2] = 1;
        	adjMatrix[14][4][3] = 1;

        	adjMatrix[14][5][0] = 1;
        	adjMatrix[14][5][1] = 1;
        	adjMatrix[14][5][2] = 1;
        	adjMatrix[14][5][3] = 1;

        	adjMatrix[14][6][2] = 1;
        	adjMatrix[14][6][3] = 1;

        	adjMatrix[14][7][0] = 1;
        	adjMatrix[14][7][1] = 1;
        	adjMatrix[14][7][3] = 1;

        	adjMatrix[14][16][0] = 1;
        	adjMatrix[14][16][1] = 1;
        	adjMatrix[14][16][2] = 1;

        	adjMatrix[14][17][2] = 1;
        	adjMatrix[14][17][3] = 1;

        	adjMatrix[14][18][0] = 1;
        	adjMatrix[14][18][1] = 1;
        	adjMatrix[14][18][2] = 1;
        	adjMatrix[14][18][3] = 1;

        	adjMatrix[14][19][2] = 1;
        	adjMatrix[14][19][3] = 1;

        	adjMatrix[14][20][2] = 1;
        	adjMatrix[14][20][3] = 1;

        	adjMatrix[14][21][2] = 1;
        	adjMatrix[14][21][3] = 1;

        	adjMatrix[14][22][0] = 1;
        	adjMatrix[14][22][3] = 1;

        	adjMatrix[15][1][0] = 1;
        	adjMatrix[15][1][1] = 1;

        	adjMatrix[15][5][0] = 1;
        	adjMatrix[15][5][1] = 1;

        	adjMatrix[15][7][1] = 1;
        	adjMatrix[15][7][2] = 1;

        	adjMatrix[15][8][2] = 1;
        	adjMatrix[15][8][3] = 1;

        	adjMatrix[15][9][2] = 1;
        	adjMatrix[15][9][3] = 1;

        	adjMatrix[15][10][0] = 1;
        	adjMatrix[15][10][3] = 1;

        	adjMatrix[15][13][0] = 1;
        	adjMatrix[15][13][2] = 1;

        	adjMatrix[15][14][2] = 1;
        	adjMatrix[15][14][3] = 1;

        	adjMatrix[15][15][2] = 1;
        	adjMatrix[15][15][3] = 1;

        	adjMatrix[15][16][1] = 1;
        	adjMatrix[15][16][3] = 1;

        	adjMatrix[15][18][0] = 1;
        	adjMatrix[15][18][1] = 1;

        	adjMatrix[15][22][0] = 1;
        	adjMatrix[15][22][1] = 1;

        	adjMatrix[16][1][1] = 1;
        	adjMatrix[16][1][2] = 1;

        	adjMatrix[16][2][2] = 1;
        	adjMatrix[16][2][3] = 1;

        	adjMatrix[16][3][0] = 1;
        	adjMatrix[16][3][3] = 1;

        	adjMatrix[16][5][0] = 1;
        	adjMatrix[16][5][1] = 1;

        	adjMatrix[16][10][0] = 1;
        	adjMatrix[16][10][1] = 1;

        	adjMatrix[16][13][0] = 1;
        	adjMatrix[16][13][1] = 1;

        	adjMatrix[16][18][0] = 1;
        	adjMatrix[16][18][1] = 1;

        	adjMatrix[16][20][0] = 1;
        	adjMatrix[16][20][2] = 1;

        	adjMatrix[16][21][2] = 1;
        	adjMatrix[16][21][3] = 1;

        	adjMatrix[16][22][1] = 1;
        	adjMatrix[16][22][3] = 1;

        	adjMatrix[17][3][0] = 1;
        	adjMatrix[17][3][1] = 1;

        	adjMatrix[17][5][1] = 1;
        	adjMatrix[17][5][2] = 1;

        	adjMatrix[17][6][0] = 1;
        	adjMatrix[17][6][2] = 1;
        	adjMatrix[17][6][3] = 1;

        	adjMatrix[17][7][2] = 1;
        	adjMatrix[17][7][3] = 1;

        	adjMatrix[17][8][0] = 1;
        	adjMatrix[17][8][2] = 1;
        	adjMatrix[17][8][3] = 1;

        	adjMatrix[17][9][2] = 1;
        	adjMatrix[17][9][3] = 1;

        	adjMatrix[17][10][1] = 1;
        	adjMatrix[17][10][2] = 1;
        	adjMatrix[17][10][3] = 1;

        	adjMatrix[17][11][2] = 1;
        	adjMatrix[17][11][3] = 1;

        	adjMatrix[17][12][2] = 1;
        	adjMatrix[17][12][3] = 1;

        	adjMatrix[17][13][1] = 1;
        	adjMatrix[17][13][2] = 1;
        	adjMatrix[17][13][3] = 1;

        	adjMatrix[17][14][2] = 1;
        	adjMatrix[17][14][3] = 1;

        	adjMatrix[17][15][0] = 1;
        	adjMatrix[17][15][2] = 1;
        	adjMatrix[17][15][3] = 1;

        	adjMatrix[17][16][2] = 1;
        	adjMatrix[17][16][3] = 1;

        	adjMatrix[17][17][0] = 1;
        	adjMatrix[17][17][2] = 1;
        	adjMatrix[17][17][3] = 1;

        	adjMatrix[17][18][1] = 1;
        	adjMatrix[17][18][3] = 1;

        	adjMatrix[17][20][0] = 1;
        	adjMatrix[17][20][1] = 1;

        	adjMatrix[18][3][0] = 1;
        	adjMatrix[18][3][1] = 1;

        	adjMatrix[18][6][0] = 1;
        	adjMatrix[18][6][1] = 1;

        	adjMatrix[18][8][0] = 1;
        	adjMatrix[18][8][1] = 1;

        	adjMatrix[18][15][0] = 1;
        	adjMatrix[18][15][1] = 1;

        	adjMatrix[18][17][0] = 1;
        	adjMatrix[18][17][1] = 1;

        	adjMatrix[18][20][0] = 1;
        	adjMatrix[18][20][1] = 1;

        	adjMatrix[19][1][0] = 1;
        	adjMatrix[19][1][2] = 1;

        	adjMatrix[19][2][2] = 1;
        	adjMatrix[19][2][3] = 1;

        	adjMatrix[19][3][1] = 1;
        	adjMatrix[19][3][2] = 1;
        	adjMatrix[19][3][3] = 1;

        	adjMatrix[19][4][2] = 1;
        	adjMatrix[19][4][3] = 1;

        	adjMatrix[19][5][2] = 1;
        	adjMatrix[19][5][3] = 1;

        	adjMatrix[19][6][1] = 1;
        	adjMatrix[19][6][3] = 1;

        	adjMatrix[19][8][0] = 1;
        	adjMatrix[19][8][1] = 1;

        	adjMatrix[19][15][0] = 1;
        	adjMatrix[19][15][1] = 1;

        	adjMatrix[19][17][1] = 1;
        	adjMatrix[19][17][2] = 1;

        	adjMatrix[19][18][2] = 1;
        	adjMatrix[19][18][3] = 1;

        	adjMatrix[19][19][2] = 1;
        	adjMatrix[19][19][3] = 1;

        	adjMatrix[19][20][1] = 1;
        	adjMatrix[19][20][2] = 1;
        	adjMatrix[19][20][3] = 1;

        	adjMatrix[19][21][2] = 1;
        	adjMatrix[19][21][3] = 1;

        	adjMatrix[19][22][0] = 1;
        	adjMatrix[19][22][3] = 1;

        	adjMatrix[20][1][0] = 1;
        	adjMatrix[20][1][1] = 1;

        	adjMatrix[20][8][0] = 1;
        	adjMatrix[20][8][1] = 1;

        	adjMatrix[20][15][0] = 1;
        	adjMatrix[20][15][1] = 1;

        	adjMatrix[20][22][0] = 1;
        	adjMatrix[20][22][1] = 1;

        	adjMatrix[21][1][1] = 1;
        	adjMatrix[21][1][2] = 1;

        	adjMatrix[21][2][2] = 1;
        	adjMatrix[21][2][3] = 1;

        	adjMatrix[21][3][2] = 1;
        	adjMatrix[21][3][3] = 1;

        	adjMatrix[21][4][2] = 1;
        	adjMatrix[21][4][3] = 1;

        	adjMatrix[21][5][2] = 1;
        	adjMatrix[21][5][3] = 1;

        	adjMatrix[21][6][2] = 1;
        	adjMatrix[21][6][3] = 1;

        	adjMatrix[21][7][2] = 1;
        	adjMatrix[21][7][3] = 1;

        	adjMatrix[21][8][1] = 1;
        	adjMatrix[21][8][2] = 1;
        	adjMatrix[21][8][3] = 1;

        	adjMatrix[21][9][2] = 1;
        	adjMatrix[21][9][3] = 1;

        	adjMatrix[21][10][2] = 1;
        	adjMatrix[21][10][3] = 1;

        	adjMatrix[21][11][2] = 1;
        	adjMatrix[21][11][3] = 1;

        	adjMatrix[21][12][2] = 1;
        	adjMatrix[21][12][3] = 1;

        	adjMatrix[21][13][2] = 1;
        	adjMatrix[21][13][3] = 1;

        	adjMatrix[21][14][2] = 1;
        	adjMatrix[21][14][3] = 1;

        	adjMatrix[21][15][1] = 1;
        	adjMatrix[21][15][2] = 1;
        	adjMatrix[21][15][3] = 1;

        	adjMatrix[21][16][2] = 1;
        	adjMatrix[21][16][3] = 1;

        	adjMatrix[21][17][2] = 1;
        	adjMatrix[21][17][3] = 1;

        	adjMatrix[21][18][2] = 1;
        	adjMatrix[21][18][3] = 1;

        	adjMatrix[21][19][2] = 1;
        	adjMatrix[21][19][3] = 1;

        	adjMatrix[21][20][2] = 1;
        	adjMatrix[21][20][3] = 1;

        	adjMatrix[21][21][2] = 1;
        	adjMatrix[21][21][3] = 1;

        	adjMatrix[21][22][1] = 1;
        	adjMatrix[21][22][3] = 1;


        }

    /*

    * Function read() reads No of vertices, Adjacency Matrix and source

    * Matrix from the user. The number of vertices must be greather than

    * zero, all members of Adjacency Matrix must be postive as distances

    * are always positive. The source vertex must also be positive from 0

    * to noOfVertices - 1

    */


        void read();


    /*

    * Function initialize initializes all the data members at the begining of

    * the execution. The distance between source to source is zero and all other

    * distances between source and vertices are infinity. The mark is initialized

    * to false and predecessor is initialized to -1

    */


        void initialize(int, int, int, int);


    /*

    * Function getClosestUnmarkedNode returns the node which is nearest from the

    * Predecessor marked node. If the node is already marked as visited, then it search

    * for another node.

    */

        int* getClosestUnmarkedNode();


    /*

    * Function calculateDistance calculates the minimum distances from the source node to

    * Other node.

    */

        void calculateDistance();


    /*

    * Function output prints the results

    */

        void output();


        void printPath(int, int);

        int numberNotMarked();

};
#endif
