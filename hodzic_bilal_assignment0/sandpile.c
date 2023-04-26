#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>
void pileSand(int x, int y, int sandpile[23][23], int sinks[23][23]);
void initialize(int sandpile[23][23], int argc, char *argv[], int *fps, int sinks[23][23]);
void printPile(int sandpile[23][23], int sinks[23][23]);
int main(int argc ,char *argv[]){
	int sandpile[23][23];
	int sinks[23][23];
	int fps = 20;
	initialize(sandpile, argc, argv, &fps, sinks);
	while(1){
		pileSand(11,11,sandpile, sinks);
		printPile(sandpile, sinks);
		usleep(1000000 / fps);
	}
}

void initialize(int sandpile[23][23], int argc, char *argv[], int *fps, int sinks[23][23]){
	int i, j;
	for(i = 0; i < 23; i++){
		for(j =0; j < 23; j++){
			sinks[i][j] = 0;
			sandpile[i][j] = 0;
		}
	}
	if (argc > 1){
		int x, y, h, i;
		int counter = 0;
		for(i =1; i < argc; i++){
			if(argv[i][1] == '-'){
				counter = 4;
			}else{
				int temp = atoi(argv[i]);
				if(counter == 0){
					x = temp;
					counter++;
				}else if (counter == 1){
					y = temp;
					counter++;
				}else if(counter == 4){
				        *fps = temp;
					counter = 0;	
				}else{
					h = temp;
					if (h == -1){
						sinks[x][y] = 1;
						counter = 0;
					}else{
						sandpile[x][y] = h;
						counter = 0;
					}
				}
			}

		}

	}
	if (sinks[11][11] == 1){
		sinks[11][11] = 0;
	}
}
void printPile(int sandpile[23][23], int sinks[23][23]){
	int i, j;
	for(i =0; i< 23; i++){
		for(j = 0; j < 23; j++){
			if (sinks[i][j] == 1){
				printf("%2c", '#');
			}else{
				printf("%2d", sandpile[i][j]);
			}
			
		}
		printf("\n");
	}
	printf("\n");
}
void pileSand(int x, int y, int sandpile[23][23], int sinks[23][23]){
	if(sinks[x][y] == 1){
		sandpile[x][y] = 0;
	}else{
		sandpile[x][y]++;
		if(sandpile[x][y] == 9){
			sandpile[x][y] = 1;
			if (x - 1 != -1){
				pileSand(x-1 , y , sandpile, sinks);
				if(x + 1 != 23){
					pileSand(x + 1, y, sandpile, sinks);
					if(y - 1 != -1){
						pileSand(x, y-1, sandpile, sinks);
						pileSand(x - 1, y - 1, sandpile, sinks);
						pileSand(x + 1, y - 1, sandpile, sinks);
						if(y + 1 != 23){
							pileSand(x, y + 1, sandpile, sinks);
							pileSand(x - 1, y + 1, sandpile, sinks);
							pileSand(x + 1, y + 1, sandpile, sinks);
						}
					}else{
						if(y + 1 != 23){
							pileSand(x, y + 1, sandpile, sinks);
							pileSand(x - 1, y + 1, sandpile, sinks);
						        pileSand(x + 1, y + 1, sandpile, sinks);
						}
					}
				}else{
					if(y - 1 != -1){
						pileSand(x, y-1, sandpile, sinks);
						pileSand(x-1, y-1, sandpile, sinks);
						if(y + 1 != 23){
							pileSand(x, y + 1, sandpile, sinks);
							pileSand(x - 1, y + 1, sandpile, sinks);
						}
					}else{
						if(y + 1 != 23){
							pileSand(x, y + 1, sandpile, sinks);
							pileSand(x - 1, y + 1, sandpile, sinks);
						}
					}
				}
			}else{
				if(x + 1 != 23){
					pileSand(x + 1, y, sandpile, sinks);
					if(y - 1 != -1){
						pileSand(x, y-1, sandpile, sinks);
						pileSand(x + 1, y-1, sandpile, sinks);
						if(y + 1 != 23){
							pileSand(x, y+1, sandpile, sinks);
							pileSand(x + 1 , y + 1, sandpile, sinks);	
						}
					}else{
						if(y + 1 != 23){
							pileSand(x, y + 1, sandpile, sinks);
							pileSand(x + 1, y + 1, sandpile, sinks);
						}
					}
				}
			}
		}
	}		
}
	

