// game.h : Include file for standard system include files,
// or project specific include files.

#pragma once

#include <iostream>

#define MAXMOVES 162 // 81+81

typedef unsigned int subBoard; //short is shorter than unsigned but alignements make the total size larger

enum Symbol {
	X=0,
	O
};

struct Player {
	subBoard bord1 : 9 = 0b000000000;
	subBoard bord2 : 9 = 0b000000000;
	subBoard bord3 : 9 = 0b000000000;
	subBoard bord4 : 9 = 0b000000000;
	subBoard bord5 : 9 = 0b000000000;
	subBoard bord6 : 9 = 0b000000000;
	subBoard bord7 : 9 = 0b000000000;
	subBoard bord8 : 9 = 0b000000000;
	subBoard bord9 : 9 = 0b000000000;
	subBoard superBord : 9 = 0b000000000;
};

struct Game {
	Player playerX;
	Player playerO;
	short lastSubSquare = -1;
	Symbol playerToPlay = Symbol::X;
};

enum Square {
	A1 = 0, A2, A3, B1, B2, B3, C1, C2, C3,
	A4, A5, A6, B4, B5, B6, C4, C5, C6,
	A7, A8, A9, B7, B8, B9, C7, C8, C9,
	D1, D2, D3, E1, E2, E3, F1, F2, F3,
	D4, D5, D6, E4, E5, E6, F4, F5, F6,
	D7, D8, D9, E7, E8, E9, F7, F8, F9,
	G1, G2, G3, H1, H2, H3, I1, I2, I3,
	G4, G5, G6, H4, H5, H6, I4, I5, I6,
	G7, G8, G9, H7, H8, H9, I7, I8, I9
};

enum SuperSquare {
	A=0,B,C,
	D,E,F,
	G,H,I
};

struct Move {
	Square dst;
	Symbol s;
};

// List of moves
struct MOVELIST {
	int count;  // number of moves
	Move moves[MAXMOVES];
};

void copyGame(Game* gameIn, Game* gameOut);

void printSubBoard(subBoard sub, char c);
void printOverlayedSubBoard(subBoard subP1, subBoard subP2, char p1, char p2);
void printBoard(Game* game);
void printMove(Move* move);

void printMoveList(MOVELIST* moveList);
void genLegalMoves(Game* game, Symbol s, MOVELIST* moveList);
void genLegalMoves(Game* game, MOVELIST* moveList);
void makeMove(Game* game,Move* m);

bool gameWon(Game* game, Symbol s);