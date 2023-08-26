// game.h : Include file for standard system include files,
// or project specific include files.

#pragma once

#include <iostream>

typedef unsigned int subBoard; //short is shorter than unsigned but alignements make the total size larger

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
};

void printSubBoard(subBoard sub, char c);
void printOverlayedSubBoard(subBoard subP1, subBoard subP2, char p1, char p2);