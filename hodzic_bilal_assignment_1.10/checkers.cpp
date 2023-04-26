#include <stdlib.h>
#include "checkers.h"
#include <stdio.h>
#include <iostream>
#include <ncurses/ncurses.h>
using namespace std;
int main(){
	selector* s = (selector*)malloc(sizeof(selector));
	piece* p = (piece*)malloc(sizeof(piece)); 
	*p = piece(-2, 0, 20,20);
	*s = selector(0, p);
	selector* sm = (selector*)malloc(sizeof(selector));
	moves* m = (moves*)malloc(sizeof(moves));
	*m = moves(20, 20, -1);
	*sm = selector(1, m);
	board* b = (board*)malloc(sizeof(board));
	*b  = board(12,12);
	int turn = 0;
	int i, j, k, l,checkercount;
	char user;
	piece* bps[12];
	piece* rps[12];
	for(i = 0; i < 12; i++){
		bps[i] = (piece*)malloc(sizeof(piece));
		rps[i] = (piece*)malloc(sizeof(piece));
	}
	for(i = 0; i < 16; i++){
		for(j = 0; j < 16; j++){
			if(b->b[i][j]->isEmpty == 0){
				if(b->b[i][j]->currPiece->type == 1){
					*bps[k] = piece(b->b[i][j]->currPiece->type, 0, j, i);
					k++;
				}else{	
					*rps[l] = piece(b->b[i][j]->currPiece->type, 0, j, i);
					l++;
				}
			}
		}
	}
	moves* md[4];
	for(i = 0; i < 4; i++){
		md[i] = (moves*)malloc(sizeof(moves));
	}
		printBoard(b, turn, s, sm);
		refresh();
		while(1){
			k = 0;
			if(turn == 0){
				*s =  selector(0, rps[k]);
				i = k;
			}else{
				*s = selector(0,bps[k]);
				i = k;
			}
			if(b->blackCount == 0){
				cout << "RED WINS" << endl;
				break;
			}else if(b->redCount == 0){
				cout << "BLACK WINS" << endl;
				break;
			}
			*sm = selector(1,m);
			while(turn == 0){
				endwin();
				printBoard(b,turn,s,sm);
				refresh();
				user = getch();
				if(user == 'q'){
					break;
				}
				if(user == 'd'){
					
					if(k + 1 > 11){
						k = i;
					}else{
						k++;
							}
					*s = selector(0, rps[k]);
					user = 'l';
				}
				while(user == 'c'){
					checkMoves(b, s->p, turn, md);
					j = 0;
					l = 0;
					*sm =  selector(0,md[0]); 
					while(user != 'x'){
						user = getch();
						if(user == 'd'){
							if(j + 1 > 3){
								j = l;
							}else{
								j++;
							}
							*sm = selector(1, md[j]);
							user = 'l';
						}
						if(user == 'f'){
							if(sm->m->type == 2 || sm->m->type == 3){
								for(checkercount = 0; checkercount < 12; checkercount++){
									if(bps[checkercount]->x == b->b[sm->m->y+2][sm->m->x-2]->x && bps[checkercount]->y == b->b[sm->m->y+2][sm->m->x-2]->y){
										cout << "HERE" << endl;
										*bps[k] = piece(-2, 0, 20,20);
										break;
									}
								}
							}
							checkermove(sm->m, s->p, b, turn);
							user = 'x';
							endwin();
							printBoard(b,turn,s,sm);
							refresh();
							if(turn == 0){
								turn++;
							}else{
								turn = 0;
							}
						}
						printBoard(b,turn,s,sm);
						refresh();
					}
				}

				if (user == 'q'){
					endwin();
					break;
				}
				endwin();
				printBoard(b,turn,s, sm);
				refresh();
				
			}
			while(turn == 1){
				user = getch();
				if(user == 'd'){
						if(k + 1 > 11){
							k = i;
						}else{
							k++;
						}
						*s = selector(0,bps[k]);
						user = 'l';
						
				}
				endwin();
				printBoard(b,turn,s, sm);
				refresh();
				while(user == 'c'){
					checkMoves(b, s->p, turn, md);
					j = 0;
					l = 0;
					*sm = selector(1,md[j]); 
					while(user != 'x'){
						user = getch();
						if(user == 'd'){
								if(j + 1 > 3){
									j = l;
								}else{
									j++;
								}
								*sm = selector(1,md[j]);
							user = 'l';
						}
						if(user == 'f'){
							checkermove(sm->m, s->p, b, turn);
							if(sm->m->type == 2 || sm->m->type == 3){
								if(rps[checkercount]->x == sm->p->x && rps[checkercount]->y == sm->p->y){
										*rps[k] = piece(-2, 0, 20,20);
										break;
									}
							}
							user = 'x';
							if(turn == 0){
								turn++;
							}else{
								turn = 0;
							}
						}
						printBoard(b,turn,s,sm);
						refresh();
					}
				}
				if (user == 'q'){
					endwin();
					break;
				}
				endwin();
				printBoard(b,turn,s, sm);
				refresh();
				
			}
			if(user == 'q'){
				break;
			}
		}
		if (user == 'q'){
			endwin();
		}
	
}
void printBoard(board* b, int turn, selector* s, selector* sm){
	int i = 0;
	int j = 0;
	int multi = 0;
	initscr();
	while(i < 16){
		j = 0;
		while(j < 16){
			if(i - 1 > -1){
				if(b->b[i-1][j]->isEmpty ==  0){
					if(b->b[i-1][j]->currPiece->type == 1){
						mvaddch(i,j,'B');
						multi = 1;
					}else{
						mvaddch(i,j,'R');
						multi = 1;
					}
				}
			}
			if(j-1 > -1){
				if(b->b[i][j-1]->isEmpty == 0){
					if(b->b[i][j-1]->currPiece->type == 1){
						mvaddch(i,j,'B');
						multi = 1;
					}else{
						mvaddch(i,j,'R');
						multi = 1;
					}
				}
			}
			if(j-1 > -1 && i - 1 > -1){		
				if(b->b[i-1][j-1]->isEmpty == 0){
					if(b->b[i-1][j-1]->currPiece->type == 1){
						mvaddch(i,j,'B');
						multi = 1;
					}else{
						mvaddch(i,j,'R');
						multi = 1;
					}
				}
			}
			if(b->b[i][j]->isEmpty == 0){
				if(b->b[i][j]->currPiece->type == 1){
					mvaddch(i,j,'B');
				}else{
					mvaddch(i,j,'R');
				}
			}else if(b->b[i][j]->color == 1 && multi == 0){
				mvaddch(i, j, '_');
			}else if(b->b[i][j]->color == 0 && multi == 0){
				mvaddch(i,j, '_');
			}
			if(s->x == j && s->y == i){
				mvaddch(i,j,'O');
			}
			if(sm->x == j && sm->y == i){
				mvaddch(i,j,'X');
			}
			multi = 0;
			j++;
		}
		i++;
	}
}

int checkwin(board* b){
	if(b->redCount == 0){
		return 1;
	}else if(b->blackCount == 0){
		return 2;
	}else{
		return 0;
	}
}
void checkMoves(board* b, piece* p, int turn, moves* m[4]){
	if(turn == 0){
		if(p->x - 2 > -1){
			if(p->y -2 > -1){
				if(b->b[p->y-2][p->x-2]->isEmpty == 1){
					*m[0] = moves(p->x-2, p->y-2, 1);
				}else if(b->b[p->y-2][p->x-2]->isEmpty == 0){
					if(b->b[p->y-2][p->x-2]->currPiece->type == 1){
						if(p->x -4 > -1){
							if(p->y - 4 > -1){
								if(b->b[p->y -4][p->x -4]->isEmpty == 1){
									*m[0] = moves(p->x-4, p->y-4, 2);
								}else{
									*m[0] = moves(p->x, p->y, 0);
								}
							}else{
								*m[0] = moves(p->x, p->y, 0);
							}
						}else{
							*m[0] = moves(p->x, p->y, 0);
						}
					}else{
						*m[0] = moves(p->x, p->y, 0);
					}
				}
			}else{
				*m[0] = moves(p->x, p->y, 0);
			}
		}else{
			*m[0] = moves(p->x, p->y, 0);
		}
		if(p->x + 2 < 16){
			if(p->y -2 > -1){
				if(b->b[p->y-2][p->x+2]->isEmpty == 1){
					*m[1] = moves(p->x+2, p->y-2, 1);
				}else if(b->b[p->y-2][p->x+2]->isEmpty == 0){
					if(b->b[p->y-2][p->x+2]->currPiece->type == 1){
						if(p->x +4 <16){
							if(p->y - 4 > -1){
								if(b->b[p->y -4][p->x +4]->isEmpty == 1){
									*m[1] = moves(p->x+4, p->y-4, 3);
								}else{
									*m[1] = moves(p->x, p->y, 0);
								}
							}else{
								*m[1] = moves(p->x+4, p->y-2, 0);
							}
						}else{
							*m[1] = moves(p->x+2, p->y-2, 0);
						}
					}else{
						*m[1] = moves(p->x+2, p->y-2, 0);
					}
				}
			}else{
				*m[1] = moves(p->x+2, p->y, 0);
			}
		}else{
			*m[1] = moves(p->x, p->y, 0);
		}
		if(p->isKing == 1){
	
		}else{
			*m[2] = moves(p->x, p->y, 0);  
			*m[3] = moves(p->x, p->y, 0); 
		}
	}else{	
		if(p->x - 2 > -1){
			if(p->y +2 < 16){
				if(b->b[p->y+2][p->x-2]->isEmpty == 1){
					*m[0] = moves(p->x-2, p->y+2, 1);
				}else if(b->b[p->y+2][p->x-2]->isEmpty == 0){
					if(b->b[p->y+2][p->x-2]->currPiece->type == 0){
						if(p->x -4 > -1){
							if(p->y + 4 < 16){
								if(b->b[p->y + 4][p->x -4]->isEmpty == 1){
									*m[0] = moves(p->x-4, p->y+4, 2);
								}else{
									*m[0] = moves(p->x, p->y, 0);
								}
							}else{
								*m[0] = moves(p->x, p->y, 0);
							}
						}else{
							*m[0] = moves(p->x, p->y, 0);
						}
					}else{
						*m[0] = moves(p->x, p->y, 0);
					}
				}
			}else{
				*m[0] = moves(p->x, p->y, 0);
			}
		}else{
			*m[0] = moves(p->x, p->y, 0);
		}
		if(p->x + 2 < 16){
			if(p->y +2 <16){
				if(b->b[p->y+2][p->x+2]->isEmpty == 1){
					*m[1] = moves(p->x+2, p->y+2, 1);
				}else if(b->b[p->y+2][p->x+2]->isEmpty == 0){
					if(b->b[p->y+2][p->x+2]->currPiece->type == 0){
						if(p->x +4 <16){
							if(p->y + 4 < 16){
								if(b->b[p->y +4][p->x +4]->isEmpty == 1){
									*m[1] = moves(p->x+4, p->y+4, 3);
								}else{
									*m[1] = moves(p->x, p->y, 0);
								}
							}else{
								*m[1] = moves(p->x, p->y, 0);
							}
						}else{
							*m[1] = moves(p->x, p->y, 0);
						}
					}else{
						*m[1] = moves(p->x, p->y, 0);
					}
				}
			}else{
				*m[1] = moves(p->x, p->y, 0);
			}
		}else{
			*m[1] = moves(p->x, p->y, 0);

		}
		if(p->isKing == 1){
	
		}else{
			*m[2] = moves(p->x, p->y, 0);  
			*m[3] = moves(p->x, p->y, 0); 
		}
	}
}
void checkermove(moves* m, piece* p, board* b,int turn){
	if(turn == 0){
		if(m->type == 1){
			b->b[p->y][p->x]->isEmpty = 1;
			*b->b[p->y][p->x]->currPiece = piece(-1, 0, p->x, p->y);
			p->x = m->x;
			p->y = m->y;
			b->b[m->y][m->x]->isEmpty = 0;
			*b->b[m->y][m->x] = space(b->b[m->y][m->x]->color, b->b[m->y][m->x]->isEmpty, b->b[m->y][m->x]->x, b->b[m->y][m->x]->y,p);
		}else if(m->type == 2){	
			b->b[p->y][p->x]->isEmpty = 1;
			*b->b[p->y][p->x]->currPiece = piece(-1, 0, p->x, p->y);
            b->b[m->y+2][m->x+2]->isEmpty = 1;
			*b->b[m->y+2][m->x+2]->currPiece = piece(-1,0,m->x + 2, m->y + 2);
			p->x = m->x;
			p->x = m->x;
			p->y = m->y;
			b->b[p->y][p->x]->isEmpty = 0;
			*b->b[m->y][m->x] = space(b->b[m->y][m->x]->color, b->b[m->y][m->x]->isEmpty, b->b[m->y][m->x]->x, b->b[m->y][m->x]->y,p);
			b->blackCount--;
		}else if(m->type == 3){
			b->b[p->y][p->x]->isEmpty = 1;
			*b->b[p->y][p->x]->currPiece = piece(-1, 0, p->x, p->y);
       b->b[m->y+2][m->x-2]->isEmpty = 1;
			*b->b[m->y+2][m->x-2]->currPiece = piece(-1,0,m->x + 2, m->y + 2);
			p->x = m->x;
			p->y = m->y;
			b->b[m->y][m->x]->isEmpty = 0;
			*b->b[m->y][m->x] = space(b->b[m->y][m->x]->color, b->b[m->y][m->x]->isEmpty, b->b[m->y][m->x]->x, b->b[m->y][m->x]->y,p);
			b->blackCount--;
		}
	}else{
		if(m->type == 1){
			b->b[p->y][p->x]->isEmpty = 1;
			*b->b[p->y][p->x]->currPiece = piece(-1, 0, p->x, p->y);
			p->x = m->x;
			p->y = m->y;
			b->b[m->y][m->x]->isEmpty = 0;
			*b->b[m->y][m->x] = space(b->b[m->y][m->x]->color, b->b[m->y][m->x]->isEmpty, b->b[m->y][m->x]->x, b->b[m->y][m->x]->y,p);
		}else if(m->type == 2){
            b->b[p->y][p->x]->isEmpty = 1;
			*b->b[p->y][p->x]->currPiece = piece(-1, 0, p->x, p->y);
			b->b[m->y-2][m->x+2]->isEmpty = 1;
			*b->b[m->y-2][m->x+2]->currPiece = piece(-1,0,m->x + 2, m->y + 2);
			p->x = m->x;
			p->y = m->y;
			b->b[m->y][m->x]->isEmpty = 0;
			*b->b[m->y][m->x] = space(b->b[m->y][m->x]->color, b->b[m->y][m->x]->isEmpty, b->b[m->y][m->x]->x, b->b[m->y][m->x]->y,p);
			b->redCount--;
		}else if(m->type == 3){
            b->b[p->y][p->x]->isEmpty = 1;
			*b->b[p->y][p->x]->currPiece = piece(-1, 0, p->x, p->y);
			b->b[m->y-2][m->x-2]->isEmpty = 1;
			*b->b[m->y-2][m->x-2]->currPiece = piece(-1,0,m->x + 2, m->y - 2);
			p->x = m->x;
			p->y = m->y;
			b->b[m->y][m->x]->isEmpty = 0;
			*b->b[m->y][m->x] = space(b->b[m->y][m->x]->color, b->b[m->y][m->x]->isEmpty, b->b[m->y][m->x]->x, b->b[m->y][m->x]->y,p);
			b->redCount--;
		}
	}
}
