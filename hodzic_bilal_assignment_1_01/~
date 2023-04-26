#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void printTerrain(char terrain[21][80]);

void generate(char terrain[21][80]);

int main(int argc, char *argv[]){
	char terrain[21][80];
	generate(terrain);
	printTerrain(terrain);
}

void printTerrain(char terrain[21][80]){
	int i, j;
	for(i = 0; i < 21; i++){
		for(j = 0; j < 80; j++){
			printf("%c", terrain[i][j]);
		}
		printf("\n");
	}
}

void generate(char terrain[21][80]){
	srand(time(NULL));
	int i, j, k;
	for(i = 0; i < 21; i++){
		for(j = 0; j < 80; j++){
			terrain[i][j] = '%';
		}
	}
	for(i = 1;i < 20; i++){
		for(j = 1; j < 79; j++){
			terrain[i][j] = '%';
		}
	}
	int tallCount = 0;
	int clearCount = 0;
	for(k = 0; k < 20; k++){
		int xVal = (rand() % 78) + 1;
		int yVal = (rand() % 19) + 1;
		int type = (rand() % 5) + 1;
	       	int xSize = (rand() % 4) + 17;
		int ySize = (rand() % 2) + 7;
		int xLeft = xVal - (xSize / 2);
		int xRight = xVal + (xSize  /2);
		int yUp = yVal - (ySize / 2);
	        int yDown = yVal + (ySize / 2);
		if (xLeft < 1){
			xLeft = 1;
		}
		if(xRight > 78){
			xRight = 78;
		}
		if(yUp < 1){
			yUp = 1;
		}
		if(yDown > 19){
			yDown = 19;
		}
		if(k > 17){
			if(tallCount < 2){
				type = 1;
			}
			if(clearCount < 2){
				type = 3;
			}
		}	
		for(i = yUp; i <= yDown; i++){
			for(j = xLeft; j <= xRight; j++){
				if(type == 1 || type == 4 || type == 5){
					terrain[i][j] = ':';
					tallCount++;
				}else if(type == 2){
					terrain[i][j] = '^';
				}else{
					terrain[i][j] = '.';
				}
			}
		}
	}
	int xPath = (rand() % 19) + 1;
	int yPath = (rand() % 78) + 1;
	for(i = 0; i < 80; i++){
		terrain[xPath][i] = '#';
	}
	for(i = 0; i < 21; i++){
		terrain[i][yPath] = '#';
	}
	int martLoc = (rand() % 74) + 2;
	int centerLoc = (rand() & 74) +2;
	if (xPath - 2 < 1){
		terrain[xPath+1][martLoc] = 'M';
		terrain[xPath+1][martLoc + 1] = 'M';
		terrain[xPath+2][martLoc] = 'M';
		terrain[xPath+2][martLoc + 1] = 'M';
	
		terrain[xPath+1][centerLoc] = 'C';
		terrain[xPath+1][centerLoc + 1] = 'C';
		terrain[xPath+2][centerLoc] = 'C';
		terrain[xPath+2][centerLoc + 1] = 'C';
	}else{
		terrain[xPath-1][martLoc] = 'M';
		terrain[xPath-1][martLoc + 1] = 'M';
		terrain[xPath-2][martLoc] = 'M';
		terrain[xPath-2][martLoc + 1] = 'M';
	
		terrain[xPath-1][centerLoc] = 'C';
		terrain[xPath-1][centerLoc + 1] = 'C';
		terrain[xPath-2][centerLoc] = 'C';
		terrain[xPath-2][centerLoc + 1] = 'C';
	}
}
