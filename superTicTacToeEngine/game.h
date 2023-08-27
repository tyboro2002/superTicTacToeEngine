// game.h : Include file for standard system include files,
// or project specific include files.

#pragma once

#include <iostream>

#define MAXMOVES 81

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
	Player X;
	Player O;
	short lastSubSquare;
};

enum Square {
	A9 = 0, B9, C9, D9, E9, F9, G9, H9, I9,
	A8, B8, C8, D8, E8, F8, G8, H8, I8,
	A7, B7, C7, D7, E7, F7, G7, H7, I7,
	A6, B6, C6, D6, E6, F6, G6, H6, I6,
	A5, B5, C5, D5, E5, F5, G5, H5, I5,
	A4, B4, C4, D4, E4, F4, G4, H4, I4,
	A3, B3, C3, D3, E3, F3, G3, H3, I3,
	A2, B2, C2, D2, E2, F2, G2, H2, I2,
	A1, B1, C1, D1, E1, F1, G1, H1, I1
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

void printSubBoard(subBoard sub, char c);
void printOverlayedSubBoard(subBoard subP1, subBoard subP2, char p1, char p2);