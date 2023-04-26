#include <iostream>
using namespace std;
class piece{
	public:
		int type, isKing, x, y;
		piece(int type, int isKing, int x, int y){
			this->type = type;
			this->isKing = isKing;
			this->x = x;
			this->y = y;
		}
};
class space{
	public:
		int color, isEmpty, x, y;
		piece* currPiece;
		space(int color, int isEmpty, int x, int y, piece* p){
			this->color = color;
			this->isEmpty = isEmpty;
			this->x = x;
			this->y = y;
			currPiece = (piece*) malloc(sizeof(piece));
			*this->currPiece = piece(p->type, p->isKing, p->x, p->y);
		}
		space(int color, int isEmpty, int x, int y){
			this->color = color;
			this->isEmpty = isEmpty;
			this->x = x;
			this->y = y;
		}
};
class board{
	public:
		int blackCount, redCount;
		space* b[16][16];
		board(int blackCount, int redCount){
			this->blackCount = blackCount; 
			this->redCount = redCount;
			int i, j, k;
			k = 0;
			i = 0;
			for(i = 0; i < 16; i++){
				for(j = 0; j < 16; j++){
						b[i][j] = (space*)malloc(sizeof(space));
						*b[i][j] = space(-1, 0, j, i);
				}
			}
			i = 0;
			while(i < 5){
				if(k == 0){
					j = 0;
					while(j < 16){
						piece* p = (piece*)malloc(sizeof(piece));
						*p = piece(1, 0, j, i);
						*b[i][j] = space(1, 0, j, i, p);
						j +=4;
					}
					k= 1;
				}else{
					j = 2;
			       		while(j < 15){
						piece* p = (piece*)malloc(sizeof(piece));
						*p = piece(1,0,j,i);
						*b[i][j] = space(1,0,j,i,p);
						j+=4;
					}
					k = 0;
				}
				i += 2;
			}
			k = 0;
			i = 10;
			while(i < 15){
				if(k == 0){
					j = 2;
					while(j < 15){
						piece* p = (piece*)malloc(sizeof(piece));
						*p = piece(0,0,j,i);
						*b[i][j] = space(1,0,j,i,p);
						j += 4;
					}
					k = 1;
				}
				else{
					j = 0;
					while(j < 16){
						piece* p = (piece*)malloc(sizeof(piece));
						*p = piece(0,0,j,i);
						*b[i][j] = space(1,0,j,i,p);
						j += 4;
					}
					k = 0;
				}
				i += 2;
			}
			int counter = 0;
			int yCount = 0;
			k = 0;
			for(i = 0; i < 16; i++){
				if(yCount > 1){
					if(k == 0){
						k = 1;
					}else{
						k = 0;
					}
					yCount = 0;
				}
				yCount++;
				for(j = 0; j < 16; j++){
					if(b[i][j]->color == -1){
						if(k == 0){
							*b[i][j] = space(1,1,j, i);
						}else{
							*b[i][j] = space(0,1,j,i);
						}
					}
					counter++;
					if(counter > 1){
						if(k == 0){
							k = 1;
						}else{
							k = 0;
						}
						counter = 0;
					}
				}
			}
		}
};
class moves{
	public:
		int x,y,type;
		moves(int x,int y,int type){
			this->x = x;
			this->y = y;
			this->type = type;
		}
};
class selector{
	public:
		int x,y,type;
		piece* p;
		moves* m;
		selector(int type, piece *p){
			this->x = p->x;
			this->y = p->y;
			this->type = type;
			this->p = (piece*)malloc(sizeof(piece));
			this->p = p;
		}
		selector(int type,moves* m){
			this->x = m->x;
			this->y = m->y;
			this->type = type;
			this->m = (moves*)malloc(sizeof(moves));
			this->m = m;
		}
};
void checkermove(moves* m, piece* p, board* b, int turn);
int checkWin(board* b);
void checkMoves(board* b, piece* p, int turn, moves* m[4]);
void printBoard(board *b, int turn, selector* s, selector* sm);

		

