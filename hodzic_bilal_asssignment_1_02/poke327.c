#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "poke327.h"
#include <time.h>
int main(int argc, char* argv[]){
	map_t* m = mapInit(0,0);
	printMap(*m);
}
tile_t* tileInit(int type, int xCoord, int yCoord){
	tile_t* newTile = (tile_t*)malloc(sizeof(tile_t));
	newTile->type = type;
	newTile->xCoord = xCoord;
	newTile->yCoord = yCoord;
	return newTile;
};
map_t* mapInit(int x, int y){
	int i, j, k;
	int tallCount = 0;
	int plainCount = 0;
	srand(time(NULL));
	map_t* newMap = (map_t*)malloc(sizeof(map_t));
	for(i = 0; i < 50; i++){
		int xCoord = rand() % 70 + 4;
	      	int yCoord = rand() % 18 + 2;
		int xLength = rand() % 13 + 2;
		int yLength = rand() % 4 + 1;
		j = xCoord - xLength;
		if(j < 1){
			j = 1;
		}
		k = yCoord - yLength;
		if(k < 1){
			k = 1;
		}
		if(xCoord + xLength > 79){
			xCoord = 79;
		}else{
			xCoord += xLength;
		}
		if(yCoord + yLength > 20){
			yCoord = 20;
		}else{
			yCoord += yLength;
		}
		int type;
		if(tallCount < 3){
			type = 1;
			tallCount++;
		}else if(plainCount < 3){
			type = 0;
			plainCount++;
		}else{
			type = rand() % 20;
			if(type >-1 && type < 5){
				type = 0;
			}else if(type > 4 && type < 12){
				type = 1;
			}else if(type > 11 && type < 16){
				type = 2;
			}else if(type > 15 && type < 20){
				type = 3;
			}
		}
		for(k = k; k < yCoord; k++){
			int reset = j;
			for(j = j; j < xCoord; j++){
				if(newMap->tiles[k][j] != NULL){
					free(newMap->tiles[k][j]);
				}
				newMap->tiles[k][j] = tileInit(type, j, k);
			}
			j = reset;
		}
	}
	for(i = 0; i < 80; i++){
		newMap->tiles[0][i] = tileInit(-1, i, 0);
		newMap->tiles[20][i] = tileInit(-1, i, 20);
	}
	for(i =0; i < 21; i++){
		newMap->tiles[i][0] = tileInit(-1, 0, i);
		newMap->tiles[i][79] = tileInit(-1, 79, i);
	}
	for(i = 0; i < 21; i++){
		for(j = 0; j < 80; j++){
			if(newMap->tiles[i][j] == NULL){
				newMap->tiles[i][j] = tileInit(0, j, i);
			}
		}
	}
	createPath(newMap);
	return newMap;
}
//TYPES KEY
//-1 Impassable(Borders)
//0 plains
//1 Tall grass
//2 Trees(impassable)
//3 Mountains(Passable by hikers only)
//4 Path
//5 Center
//6 Mart
void printMap(map_t m){
	int i, j;
	for(i = 0; i < 21; i++){
		for(j = 0; j < 80; j++){
			if(m.tiles[i][j]->type == -1){
				printf("%%");
			}else if(m.tiles[i][j]->type == 0){
				printf(".");
			}else if(m.tiles[i][j]->type == 1){
				printf(":");
			}else if(m.tiles[i][j]->type == 2){
				printf("^");
			}else if(m.tiles[i][j]->type == 3){
				printf("%%");
			}else if(m.tiles[i][j]->type == 4){
				printf("#");
			}
		}
		printf("\n");
	}
}
void createPath(map_t* m){
	srand(time(NULL));
	int i, j;
	int leftExit, rightExit, upExit, downExit;
	leftExit = rand() % 18 + 2;
	rightExit = rand() % 18 + 2;
	int EWturndistance = rand() % 65 + 2;
	int upTurn = rand() % 15;
	for(i = 0; i < EWturndistance; i++){
		free(m->tiles[leftExit][i]);
		m->tiles[leftExit][i] = tileInit(4, i, leftExit);
	}
	i = EWturndistance;
	if(upTurn - leftExit < 2){
		upTurn = 1;
	}else{
		upTurn = upTurn - leftExit;
	}
	for(j = leftExit; j > upTurn; j--){
		free(m->tiles[j][i]);
	     	m->tiles[j][i] = tileInit(4, i, j);
	}
	for(i = i; i < rand() % 15 + i; i++){
		free(m->tiles[j][i]);
		m->tiles[j][i] = tileInit(4, i, j);
	}	
	if(j < rightExit){
		for(j = j; j < rightExit; j++){
			free(m->tiles[j][i]);
			m->tiles[j][i] = tileInit(4, i, j);
		}
	}else{
		for(j = j; j < rightExit; j++){
			free(m->tiles[j][i]);
			m->tiles[j][i] = tileInit(4, i, j);
		}
	}
	for(i = i; i < 80; i++){
	       free(m->tiles[j][i]);
		m->tiles[j][i] = tileInit(4,i,j);
 	}
	upExit = rand() % 75 + 2;
	downExit = rand() % 75 + 2;
	int NSturndistance = rand() % 12 + 1;

	for(i = 0; i < NSturndistance; i++){
		free(m->tiles[i][upExit]);
		m->tiles[i][upExit] = tileInit(4, upExit, i);
	}
	i = NSturndistance;
	int rightTurn = rand() % 30;
	if(rightTurn + upExit > 79){
		upTurn = 79;
	}else{
		rightTurn += upExit;
	}
	for(j = upExit; j < upExit; j++){
		free(m->tiles[i][j]);
		m->tiles[i][j] = tileInit(4, j, i);
	}
	for(i = i; i > i - rand() % 6; i--){
		free(m->tiles[i][j]);
		m->tiles[i][j] = tileInit(4, j, i);
	}
	if(j > downExit){
		for(j = j; j > downExit; j--){
			free(m->tiles[i][j]);
			m->tiles[i][j] = tileInit(4, j, i);
		}
	}else{
		for(j = j; j < downExit; j++){
			free(m->tiles[i][j]);
			m->tiles[i][j] = tileInit(4, j, i);
		}
	}
	for(i = i; i < 21; i++){
		free(m->tiles[i][j]);
		m->tiles[i][j] = tileInit(4, j, i);
	}

}	
