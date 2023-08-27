#include <bitset>
#include "game.h"
using namespace std;

#define row1 0b111000000
#define row2 0b000111000
#define row3 0b000000111

#define column1 0b100100100
#define column2 0b010010010
#define column3 0b001001001

#define diagonal1 0b100010001
#define diagonal2 0b001010100

int countSetBits(subBoard sub) {
	int count = 0;
	while (sub) {
		count += sub & 1;
		sub >>= 1;
	}
	return count;
}

int countTrailingZeros(short number) {
	unsigned long index;
	if (_BitScanForward64(&index, number)) {
		return static_cast<int>(index);
	}
	return -1; // Return -1 if the input number is 0
}

char bitToChar(bool b, char c) {
	if (b) return c;
	else return ' ';
}

std::string symbolToString(Symbol s) {
	if (s == X) return "X";
	else return "O";
}

std::string squareToString(Square s) {
	if (s == A1) return "A1";
	else if (s == A2) return "A2";
	else if (s == A3) return "A3";
	else if (s == A4) return "A4";
	else if (s == A5) return "A5";
	else if (s == A6) return "A6";
	else if (s == A7) return "A7";
	else if (s == A8) return "A8";
	else if (s == A9) return "A9";

	else if (s == B1) return "B1";
	else if (s == B2) return "B2";
	else if (s == B3) return "B3";
	else if (s == B4) return "B4";
	else if (s == B5) return "B5";
	else if (s == B6) return "B6";
	else if (s == B7) return "B7";
	else if (s == B8) return "B8";
	else if (s == B9) return "B9";

	else if (s == C1) return "C1";
	else if (s == C2) return "C2";
	else if (s == C3) return "C3";
	else if (s == C4) return "C4";
	else if (s == C5) return "C5";
	else if (s == C6) return "C6";
	else if (s == C7) return "C7";
	else if (s == C8) return "C8";
	else if (s == C9) return "C9";

	else if (s == D1) return "D1";
	else if (s == D2) return "D2";
	else if (s == D3) return "D3";
	else if (s == D4) return "D4";
	else if (s == D5) return "D5";
	else if (s == D6) return "D6";
	else if (s == D7) return "D7";
	else if (s == D8) return "D8";
	else if (s == D9) return "D9";

	else if (s == E1) return "E1";
	else if (s == E2) return "E2";
	else if (s == E3) return "E3";
	else if (s == E4) return "E4";
	else if (s == E5) return "E5";
	else if (s == E6) return "E6";
	else if (s == E7) return "E7";
	else if (s == E8) return "E8";
	else if (s == E9) return "E9";

	else if (s == F1) return "F1";
	else if (s == F2) return "F2";
	else if (s == F3) return "F3";
	else if (s == F4) return "F4";
	else if (s == F5) return "F5";
	else if (s == F6) return "F6";
	else if (s == F7) return "F7";
	else if (s == F8) return "F8";
	else if (s == F9) return "F9";

	else if (s == G1) return "G1";
	else if (s == G2) return "G2";
	else if (s == G3) return "G3";
	else if (s == G4) return "G4";
	else if (s == G5) return "G5";
	else if (s == G6) return "G6";
	else if (s == G7) return "G7";
	else if (s == G8) return "G8";
	else if (s == G9) return "G9";

	else if (s == H1) return "H1";
	else if (s == H2) return "H2";
	else if (s == H3) return "H3";
	else if (s == H4) return "H4";
	else if (s == H5) return "H5";
	else if (s == H6) return "H6";
	else if (s == H7) return "H7";
	else if (s == H8) return "H8";
	else if (s == H9) return "H9";

	else if (s == I1) return "I1";
	else if (s == I2) return "I2";
	else if (s == I3) return "I3";
	else if (s == I4) return "I4";
	else if (s == I5) return "I5";
	else if (s == I6) return "I6";
	else if (s == I7) return "I7";
	else if (s == I8) return "I8";
	else if (s == I9) return "I9";
}

bool checkWon(subBoard subp1, subBoard subp2, Symbol s) {
	if (s == X) {
		if (countSetBits(subp1 & row1) == 3) return true;
		if (countSetBits(subp1 & row2) == 3) return true;
		if (countSetBits(subp1 & row3) == 3)  return true;
		if (countSetBits(subp1 & column1) == 3)  return true;
		if (countSetBits(subp1 & column2) == 3)  return true;
		if (countSetBits(subp1 & column3) == 3)  return true;
		if (countSetBits(subp1 & diagonal1) == 3)  return true;
		if (countSetBits(subp1 & diagonal2) == 3)  return true;
		return false;
	}
	else {
		if (countSetBits(subp2 & row1) == 3) return true;
		if (countSetBits(subp2 & row2) == 3) return true;
		if (countSetBits(subp2 & row3) == 3)  return true;
		if (countSetBits(subp2 & column1) == 3)  return true;
		if (countSetBits(subp2 & column2) == 3)  return true;
		if (countSetBits(subp2 & column3) == 3)  return true;
		if (countSetBits(subp2 & diagonal1) == 3)  return true;
		if (countSetBits(subp2 & diagonal2) == 3)  return true;
		return false;
	}
}

void fillSuperBoard(Player* player) {
	player->superBord = 0b000000000;

	if (countSetBits(player->bord1 & row1) == 3) player->superBord |= 0b100000000;
	if (countSetBits(player->bord1 & row2) == 3) player->superBord |= 0b100000000;
	if (countSetBits(player->bord1 & row3) == 3) player->superBord |= 0b100000000;
	if (countSetBits(player->bord1 & column1) == 3) player->superBord |= 0b100000000;
	if (countSetBits(player->bord1 & column2) == 3) player->superBord |= 0b100000000;
	if (countSetBits(player->bord1 & column3) == 3) player->superBord |= 0b100000000;
	if (countSetBits(player->bord1 & diagonal1) == 3) player->superBord |= 0b100000000;
	if (countSetBits(player->bord1 & diagonal2) == 3) player->superBord |= 0b100000000;

	if (countSetBits(player->bord2 & row1) == 3) player->superBord |= 0b010000000;
	if (countSetBits(player->bord2 & row2) == 3) player->superBord |= 0b010000000;
	if (countSetBits(player->bord2 & row3) == 3) player->superBord |= 0b010000000;
	if (countSetBits(player->bord2 & column1) == 3) player->superBord |= 0b010000000;
	if (countSetBits(player->bord2 & column2) == 3) player->superBord |= 0b010000000;
	if (countSetBits(player->bord2 & column3) == 3) player->superBord |= 0b010000000;
	if (countSetBits(player->bord2 & diagonal1) == 3) player->superBord |= 0b010000000;
	if (countSetBits(player->bord2 & diagonal2) == 3) player->superBord |= 0b010000000;

	if (countSetBits(player->bord3 & row1) == 3) player->superBord |= 0b001000000;
	if (countSetBits(player->bord3 & row2) == 3) player->superBord |= 0b001000000;
	if (countSetBits(player->bord3 & row3) == 3) player->superBord |= 0b001000000;
	if (countSetBits(player->bord3 & column1) == 3) player->superBord |= 0b001000000;
	if (countSetBits(player->bord3 & column2) == 3) player->superBord |= 0b001000000;
	if (countSetBits(player->bord3 & column3) == 3) player->superBord |= 0b001000000;
	if (countSetBits(player->bord3 & diagonal1) == 3) player->superBord |= 0b001000000;
	if (countSetBits(player->bord3 & diagonal2) == 3) player->superBord |= 0b001000000;

	if (countSetBits(player->bord4 & row1) == 3) player->superBord |= 0b000100000;
	if (countSetBits(player->bord4 & row2) == 3) player->superBord |= 0b000100000;
	if (countSetBits(player->bord4 & row3) == 3) player->superBord |= 0b000100000;
	if (countSetBits(player->bord4 & column1) == 3) player->superBord |= 0b000100000;
	if (countSetBits(player->bord4 & column2) == 3) player->superBord |= 0b000100000;
	if (countSetBits(player->bord4 & column3) == 3) player->superBord |= 0b000100000;
	if (countSetBits(player->bord4 & diagonal1) == 3) player->superBord |= 0b000100000;
	if (countSetBits(player->bord4 & diagonal2) == 3) player->superBord |= 0b000100000;

	if (countSetBits(player->bord5 & row1) == 3) player->superBord |= 0b000010000;
	if (countSetBits(player->bord5 & row2) == 3) player->superBord |= 0b000010000;
	if (countSetBits(player->bord5 & row3) == 3) player->superBord |= 0b000010000;
	if (countSetBits(player->bord5 & column1) == 3) player->superBord |= 0b000010000;
	if (countSetBits(player->bord5 & column2) == 3) player->superBord |= 0b000010000;
	if (countSetBits(player->bord5 & column3) == 3) player->superBord |= 0b000010000;
	if (countSetBits(player->bord5 & diagonal1) == 3) player->superBord |= 0b000010000;
	if (countSetBits(player->bord5 & diagonal2) == 3) player->superBord |= 0b000010000;

	if (countSetBits(player->bord6 & row1) == 3) player->superBord |= 0b000001000;
	if (countSetBits(player->bord6 & row2) == 3) player->superBord |= 0b000001000;
	if (countSetBits(player->bord6 & row3) == 3) player->superBord |= 0b000001000;
	if (countSetBits(player->bord6 & column1) == 3) player->superBord |= 0b000001000;
	if (countSetBits(player->bord6 & column2) == 3) player->superBord |= 0b000001000;
	if (countSetBits(player->bord6 & column3) == 3) player->superBord |= 0b000001000;
	if (countSetBits(player->bord6 & diagonal1) == 3) player->superBord |= 0b000001000;
	if (countSetBits(player->bord6 & diagonal2) == 3) player->superBord |= 0b000001000;

	if (countSetBits(player->bord7 & row1) == 3) player->superBord |= 0b000000100;
	if (countSetBits(player->bord7 & row2) == 3) player->superBord |= 0b000000100;
	if (countSetBits(player->bord7 & row3) == 3) player->superBord |= 0b000000100;
	if (countSetBits(player->bord7 & column1) == 3) player->superBord |= 0b000000100;
	if (countSetBits(player->bord7 & column2) == 3) player->superBord |= 0b000000100;
	if (countSetBits(player->bord7 & column3) == 3) player->superBord |= 0b000000100;
	if (countSetBits(player->bord7 & diagonal1) == 3) player->superBord |= 0b000000100;
	if (countSetBits(player->bord7 & diagonal2) == 3) player->superBord |= 0b000000100;

	if (countSetBits(player->bord8 & row1) == 3) player->superBord |= 0b000000010;
	if (countSetBits(player->bord8 & row2) == 3) player->superBord |= 0b000000010;
	if (countSetBits(player->bord8 & row3) == 3) player->superBord |= 0b000000010;
	if (countSetBits(player->bord8 & column1) == 3) player->superBord |= 0b000000010;
	if (countSetBits(player->bord8 & column2) == 3) player->superBord |= 0b000000010;
	if (countSetBits(player->bord8 & column3) == 3) player->superBord |= 0b000000010;
	if (countSetBits(player->bord8 & diagonal1) == 3) player->superBord |= 0b000000010;
	if (countSetBits(player->bord8 & diagonal2) == 3) player->superBord |= 0b000000010;

	if (countSetBits(player->bord9 & row1) == 3) player->superBord |= 0b000000001;
	if (countSetBits(player->bord9 & row2) == 3) player->superBord |= 0b000000001;
	if (countSetBits(player->bord9 & row3) == 3) player->superBord |= 0b000000001;
	if (countSetBits(player->bord9 & column1) == 3) player->superBord |= 0b000000001;
	if (countSetBits(player->bord9 & column2) == 3) player->superBord |= 0b000000001;
	if (countSetBits(player->bord9 & column3) == 3) player->superBord |= 0b000000001;
	if (countSetBits(player->bord9 & diagonal1) == 3) player->superBord |= 0b000000001;
	if (countSetBits(player->bord9 & diagonal2) == 3) player->superBord |= 0b000000001;
}

void fillSuperBoardGame(Game* game) {
	fillSuperBoard(&game->playerO);
	fillSuperBoard(&game->playerX);
}

Square supIndToSquare(SuperSquare sup, short ind) {
	if (sup == A) {
		if (ind == 1) return A1;
		if (ind == 2) return A2;
		if (ind == 3) return A3;
		if (ind == 4) return A4;
		if (ind == 5) return A5;
		if (ind == 6) return A6;
		if (ind == 7) return A7;
		if (ind == 8) return A8;
		if (ind == 9) return A9;
	}
	if (sup == B) {
		if (ind == 1) return B1;
		if (ind == 2) return B2;
		if (ind == 3) return B3;
		if (ind == 4) return B4;
		if (ind == 5) return B5;
		if (ind == 6) return B6;
		if (ind == 7) return B7;
		if (ind == 8) return B8;
		if (ind == 9) return B9;
	}
	if (sup == C) {
		if (ind == 1) return C1;
		if (ind == 2) return C2;
		if (ind == 3) return C3;
		if (ind == 4) return C4;
		if (ind == 5) return C5;
		if (ind == 6) return C6;
		if (ind == 7) return C7;
		if (ind == 8) return C8;
		if (ind == 9) return C9;
	}
	if (sup == D) {
		if (ind == 1) return D1;
		if (ind == 2) return D2;
		if (ind == 3) return D3;
		if (ind == 4) return D4;
		if (ind == 5) return D5;
		if (ind == 6) return D6;
		if (ind == 7) return D7;
		if (ind == 8) return D8;
		if (ind == 9) return D9;
	}
	if (sup == E) {
		if (ind == 1) return E1;
		if (ind == 2) return E2;
		if (ind == 3) return E3;
		if (ind == 4) return E4;
		if (ind == 5) return E5;
		if (ind == 6) return E6;
		if (ind == 7) return E7;
		if (ind == 8) return E8;
		if (ind == 9) return E9;
	}
	if (sup == F) {
		if (ind == 1) return F1;
		if (ind == 2) return F2;
		if (ind == 3) return F3;
		if (ind == 4) return F4;
		if (ind == 5) return F5;
		if (ind == 6) return F6;
		if (ind == 7) return F7;
		if (ind == 8) return F8;
		if (ind == 9) return F9;
	}
	if (sup == G) {
		if (ind == 1) return G1;
		if (ind == 2) return G2;
		if (ind == 3) return G3;
		if (ind == 4) return G4;
		if (ind == 5) return G5;
		if (ind == 6) return G6;
		if (ind == 7) return G7;
		if (ind == 8) return G8;
		if (ind == 9) return G9;
	}
	if (sup == H) {
		if (ind == 1) return H1;
		if (ind == 2) return H2;
		if (ind == 3) return H3;
		if (ind == 4) return H4;
		if (ind == 5) return H5;
		if (ind == 6) return H6;
		if (ind == 7) return H7;
		if (ind == 8) return H8;
		if (ind == 9) return H9;
	}
	if (sup == I) {
		if (ind == 1) return I1;
		if (ind == 2) return I2;
		if (ind == 3) return I3;
		if (ind == 4) return I4;
		if (ind == 5) return I5;
		if (ind == 6) return I6;
		if (ind == 7) return I7;
		if (ind == 8) return I8;
		if (ind == 9) return I9;
	}
}

void genLegalMovesSubBoard(subBoard p1, subBoard p2, Symbol s, MOVELIST* movelist, SuperSquare sup) {
	if (checkWon(p1, p2, X) || checkWon(p1, p2, O)) return;
	subBoard empty = (~(p1 | p2)) & 0b111111111;
	Move* m = &movelist->moves[movelist->count];
	while (empty) {
		m->dst = supIndToSquare(sup, countTrailingZeros(empty)+1);
		m->s = s;
		m++;
		movelist->count++;
		empty &= (empty - 1); // Clear the least significant set bit
	}
}

void genLegalMoves(Game* game, Symbol s, MOVELIST* moveList) {
	if (game->lastSubSquare == -1) {
		genLegalMovesSubBoard(game->playerO.bord1, game->playerX.bord1, s, moveList, A);
		genLegalMovesSubBoard(game->playerO.bord2, game->playerX.bord2, s, moveList, B);
		genLegalMovesSubBoard(game->playerO.bord3, game->playerX.bord3, s, moveList, C);
		genLegalMovesSubBoard(game->playerO.bord4, game->playerX.bord4, s, moveList, D);
		genLegalMovesSubBoard(game->playerO.bord5, game->playerX.bord5, s, moveList, E);
		genLegalMovesSubBoard(game->playerO.bord6, game->playerX.bord6, s, moveList, F);
		genLegalMovesSubBoard(game->playerO.bord7, game->playerX.bord7, s, moveList, G);
		genLegalMovesSubBoard(game->playerO.bord8, game->playerX.bord8, s, moveList, H);
		genLegalMovesSubBoard(game->playerO.bord9, game->playerX.bord9, s, moveList, I);
		return;
	}

	if (game->lastSubSquare == 1) { genLegalMovesSubBoard(game->playerO.bord1, game->playerX.bord1, s, moveList, A); return; }
	if (game->lastSubSquare == 2) { genLegalMovesSubBoard(game->playerO.bord2, game->playerX.bord2, s, moveList, B); return; }
	if (game->lastSubSquare == 3) { genLegalMovesSubBoard(game->playerO.bord3, game->playerX.bord3, s, moveList, C); return; }
	if (game->lastSubSquare == 4) { genLegalMovesSubBoard(game->playerO.bord4, game->playerX.bord4, s, moveList, D); return; }
	if (game->lastSubSquare == 5) { genLegalMovesSubBoard(game->playerO.bord5, game->playerX.bord5, s, moveList, E); return; }
	if (game->lastSubSquare == 6) { genLegalMovesSubBoard(game->playerO.bord6, game->playerX.bord6, s, moveList, F); return; }
	if (game->lastSubSquare == 7) { genLegalMovesSubBoard(game->playerO.bord7, game->playerX.bord7, s, moveList, G); return; }
	if (game->lastSubSquare == 8) { genLegalMovesSubBoard(game->playerO.bord8, game->playerX.bord8, s, moveList, H); return; }
	if (game->lastSubSquare == 9) { genLegalMovesSubBoard(game->playerO.bord9, game->playerX.bord9, s, moveList, I); return; }

}

void printSubBoard(subBoard sub, char c) {
	cout << "-------" << endl;
	cout << "|" << bitToChar((sub >> 8) & 1, c) << "|" << bitToChar((sub >> 7) & 1, c) << "|" << bitToChar((sub >> 6) & 1, c) << "|" << endl;
	cout << "-------" << endl;
	cout << "|" << bitToChar((sub >> 5) & 1, c) << "|" << bitToChar((sub >> 4) & 1, c) << "|" << bitToChar((sub >> 3) & 1, c) << "|" << endl;
	cout << "-------" << endl;
	cout << "|" << bitToChar((sub >> 2) & 1, c) << "|" << bitToChar((sub >> 1) & 1, c) << "|" << bitToChar((sub >> 0) & 1, c) << "|" << endl;
	cout << "-------" << endl;
}

void printOverlayedSubBoard(subBoard subP1, subBoard subP2, char p1, char p2) {
	cout << "-------" << endl;
	cout << "|";
	if ((subP1 >> 8) & 1) cout << bitToChar(1, p1);
	else if ((subP2 >> 8) & 1) cout << bitToChar(1, p2);
	else cout << " ";
	cout << "|";
	if ((subP1 >> 7) & 1) cout << bitToChar(1, p1);
	else if ((subP2 >> 7) & 1) cout << bitToChar(1, p2);
	else cout << " ";
	cout << "|";
	if ((subP1 >> 6) & 1) cout << bitToChar(1, p1);
	else if ((subP2 >> 6) & 1) cout << bitToChar(1, p2);
	else cout << " ";
	cout << "|" << endl;
	cout << "-------" << endl;
	cout << "|";
	if ((subP1 >> 5) & 1) cout << bitToChar(1, p1);
	else if ((subP2 >> 5) & 1) cout << bitToChar(1, p2);
	else cout << " ";
	cout << "|";
	if ((subP1 >> 4) & 1) cout << bitToChar(1, p1);
	else if ((subP2 >> 4) & 1) cout << bitToChar(1, p2);
	else cout << " ";
	cout << "|";
	if ((subP1 >> 3) & 1) cout << bitToChar(1, p1);
	else if ((subP2 >> 3) & 1) cout << bitToChar(1, p2);
	else cout << " ";
	cout << "|" << endl;
	cout << "-------" << endl;
	cout << "|";
	if ((subP1 >> 2) & 1) cout << bitToChar(1, p1);
	else if ((subP2 >> 2) & 1) cout << bitToChar(1, p2);
	else cout << " ";
	cout << "|";
	if ((subP1 >> 1) & 1) cout << bitToChar(1, p1);
	else if ((subP2 >> 1) & 1) cout << bitToChar(1, p2);
	else cout << " ";
	cout << "|";
	if (subP1 & 1) cout << bitToChar(1, p1);
	else if (subP2 & 1) cout << bitToChar(1, p2);
	else cout << " ";
	cout << "|" << endl;
	cout << "-------" << endl;
}

void printMoveList(MOVELIST* moveList) {
	if (moveList->count == 0) {
		cout << "no moves found!" << endl;
		return;
	}
	for (int i = 0; i < moveList->count; i++) {
		cout << i << ") plays a: " << symbolToString((moveList->moves[i]).s) << " at: " << squareToString((moveList->moves[i]).dst)  /* << " with value: " << move_value(bord, &moveList->moves[i], false)*/ << endl; //TODO for testing 
	}
}