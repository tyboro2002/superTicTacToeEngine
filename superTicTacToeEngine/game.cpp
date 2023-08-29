#include <bitset>
#include "game.h"
#include <locale>
#include <Windows.h>
#include <stdio.h>
#include <sstream>

using namespace std;

#define row1 0b111000000
#define row2 0b000111000
#define row3 0b000000111

#define column1 0b100100100
#define column2 0b010010010
#define column3 0b001001001

#define diagonal1 0b100010001
#define diagonal2 0b001010100

#define ENTER cout << endl

#define RED FOREGROUND_RED
#define GREEN FOREGROUND_GREEN
#define BLUE FOREGROUND_BLUE
#define YELLOW FOREGROUND_RED | FOREGROUND_GREEN
#define PURPLE FOREGROUND_RED | FOREGROUND_BLUE
#define CYAN FOREGROUND_GREEN | FOREGROUND_BLUE
#define WHITE FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE

void copyGame(Game* gameIn, Game* gameOut) {
	// Al gedacht aan *gameOut = *gameIn? Of *(char *)gameIn en dan voor iedere byte overlopen en kopiëren
	gameOut->lastSubSquare = gameIn->lastSubSquare;
	gameOut->playerToPlay = gameIn->playerToPlay;
	gameOut->playerX.bord1 = gameIn->playerX.bord1;
	gameOut->playerX.bord2 = gameIn->playerX.bord2;
	gameOut->playerX.bord3 = gameIn->playerX.bord3;
	gameOut->playerX.bord4 = gameIn->playerX.bord4;
	gameOut->playerX.bord5 = gameIn->playerX.bord5;
	gameOut->playerX.bord6 = gameIn->playerX.bord6;
	gameOut->playerX.bord7 = gameIn->playerX.bord7;
	gameOut->playerX.bord8 = gameIn->playerX.bord8;
	gameOut->playerX.bord9 = gameIn->playerX.bord9;
	gameOut->playerX.superBord = gameIn->playerX.superBord;
	gameOut->playerO.bord1 = gameIn->playerO.bord1;
	gameOut->playerO.bord2 = gameIn->playerO.bord2;
	gameOut->playerO.bord3 = gameIn->playerO.bord3;
	gameOut->playerO.bord4 = gameIn->playerO.bord4;
	gameOut->playerO.bord5 = gameIn->playerO.bord5;
	gameOut->playerO.bord6 = gameIn->playerO.bord6;
	gameOut->playerO.bord7 = gameIn->playerO.bord7;
	gameOut->playerO.bord8 = gameIn->playerO.bord8;
	gameOut->playerO.bord9 = gameIn->playerO.bord9;
	gameOut->playerO.superBord = gameIn->playerO.superBord;
}

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

int countLeadingZeros(short number) {
	if (number == 0) {
		return 9; // All zeros in the input number
	}

	// Right-shift by the count of trailing zeros in the least significant 9 bits
	number >>= _tzcnt_u32(number & 0x1FF); // 0x1FF masks the least significant 9 bits

	// Count trailing zeros in the modified number
	unsigned long index;
	if (_BitScanForward(&index, number)) {
		return static_cast<int>(index);
	}

	return 9; // All bits in the least significant 9 bits are zeros
}

char bitToChar(bool b, char c) { return b ? c : ' ';}

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
	else return "INVALID";
}

Square stringToSquare(std::string s) {
	if (s == "A1") return A1;
	else if (s == "A2") return A2;
	else if (s == "A3") return A3;
	else if (s == "A4") return A4;
	else if (s == "A5") return A5;
	else if (s == "A6") return A6;
	else if (s == "A7") return A7;
	else if (s == "A8") return A8;
	else if (s == "A9") return A9;

	else if (s == "B1") return B1;
	else if (s == "B2") return B2;
	else if (s == "B3") return B3;
	else if (s == "B4") return B4;
	else if (s == "B5") return B5;
	else if (s == "B6") return B6;
	else if (s == "B7") return B7;
	else if (s == "B8") return B8;
	else if (s == "B9") return B9;

	else if (s == "C1") return C1;
	else if (s == "C2") return C2;
	else if (s == "C3") return C3;
	else if (s == "C4") return C4;
	else if (s == "C5") return C5;
	else if (s == "C6") return C6;
	else if (s == "C7") return C7;
	else if (s == "C8") return C8;
	else if (s == "C9") return C9;

	else if (s == "D1") return D1;
	else if (s == "D2") return D2;
	else if (s == "D3") return D3;
	else if (s == "D4") return D4;
	else if (s == "D5") return D5;
	else if (s == "D6") return D6;
	else if (s == "D7") return D7;
	else if (s == "D8") return D8;
	else if (s == "D9") return D9;

	else if (s == "E1") return E1;
	else if (s == "E2") return E2;
	else if (s == "E3") return E3;
	else if (s == "E4") return E4;
	else if (s == "E5") return E5;
	else if (s == "E6") return E6;
	else if (s == "E7") return E7;
	else if (s == "E8") return E8;
	else if (s == "E9") return E9;

	else if (s == "F1") return F1;
	else if (s == "F2") return F2;
	else if (s == "F3") return F3;
	else if (s == "F4") return F4;
	else if (s == "F5") return F5;
	else if (s == "F6") return F6;
	else if (s == "F7") return F7;
	else if (s == "F8") return F8;
	else if (s == "F9") return F9;

	else if (s == "G1") return G1;
	else if (s == "G2") return G2;
	else if (s == "G3") return G3;
	else if (s == "G4") return G4;
	else if (s == "G5") return G5;
	else if (s == "G6") return G6;
	else if (s == "G7") return G7;
	else if (s == "G8") return G8;
	else if (s == "G9") return G9;

	else if (s == "H1") return H1;
	else if (s == "H2") return H2;
	else if (s == "H3") return H3;
	else if (s == "H4") return H4;
	else if (s == "H5") return H5;
	else if (s == "H6") return H6;
	else if (s == "H7") return H7;
	else if (s == "H8") return H8;
	else if (s == "H9") return H9;

	else if (s == "I1") return I1;
	else if (s == "I2") return I2;
	else if (s == "I3") return I3;
	else if (s == "I4") return I4;
	else if (s == "I5") return I5;
	else if (s == "I6") return I6;
	else if (s == "I7") return I7;
	else if (s == "I8") return I8;
	else if (s == "I9") return I9;
	return INVALID;
}

/*
* convert a int to the subboard with the coresponding bit to 1
*/
subBoard intToSubBoard(int ind) {
	if (ind == 0) return 0b000000000;
	if (ind == 1) return 0b100000000;
	if (ind == 2) return 0b010000000;
	if (ind == 3) return 0b001000000;
	if (ind == 4) return 0b000100000;
	if (ind == 5) return 0b000010000;
	if (ind == 6) return 0b000001000;
	if (ind == 7) return 0b000000100;
	if (ind == 8) return 0b000000010;
	if (ind == 9) return 0b000000001;
}

std::string writeOutSPTTTstring(Game* game) {
	std::stringstream ss;
	subBoard pX[9] = {game->playerX.bord1,game->playerX.bord2, game->playerX.bord3 , game->playerX.bord4 ,game->playerX.bord5 ,game->playerX.bord6 ,game->playerX.bord7 ,game->playerX.bord8 ,game->playerX.bord9 };
	subBoard pO[9] = { game->playerO.bord1,game->playerO.bord2, game->playerO.bord3 , game->playerO.bord4 ,game->playerO.bord5 ,game->playerO.bord6 ,game->playerO.bord7 ,game->playerO.bord8 ,game->playerO.bord9 };

	for (int p = 0; p < 9; p++) {
		//put arbitrary formatted data into the stream
		for (int i = 8; i >= 0; --i) {
			bool bitNumber1 = (pX[p] >> i) & 1;
			bool bitNumber2 = (pO[p] >> i) & 1;

			if (bitNumber1) {
				// Action when the i-th bit in number1 is set
				ss << "X";
			}
			else if (bitNumber2) {
				// Action when the i-th bit in number2 is set 
				ss << "O";
			}
			else {
				// Action when both bits are either both set or both not set
				ss << "-";
			}
		}
	}
	ss << " ";
	if (game->playerToPlay == X) ss << "X";
	else ss << "O";
	ss << " ";
	if (game->lastSubSquare == -1) ss << "-";
	else if (game->lastSubSquare == A) ss << "A";
	else if (game->lastSubSquare == B) ss << "B";
	else if (game->lastSubSquare == C) ss << "C";
	else if (game->lastSubSquare == D) ss << "D";
	else if (game->lastSubSquare == E) ss << "E";
	else if (game->lastSubSquare == F) ss << "F";
	else if (game->lastSubSquare == G) ss << "G";
	else if (game->lastSubSquare == H) ss << "H";
	else if (game->lastSubSquare == I) ss << "I";
	//convert the stream buffer into a string
	std::string str = ss.str();
	return str;
}

bool subSqWon(Game* game, SuperSquare sup); //abstract to use in following function declared later
void fillSuperBoardGame(Game* game); //abstract to use in following function declared later
bool gameWon(Game* game); //abstract to use in following function declared later

/*
* A SPTTT string is short for SuPerTicTacToe string
* it concists of 3 parts divided by " "
* the first part is 81 times a X or O or - this symbols represent the filling of the squares (left to right top to bottom per square and squares in the same order)
* the second part is a O or a X indicating wich player to play
* the third part is a -, A, B, C, D, E, F, G, H or I indicating wich subsquare was last played (- indicates no square or last square blocked (the code will check for this to))
*/
void readInSPTTTString(Game* game, std::string* SPTTT, bool extraInfo) {
	std::string squares = SPTTT->substr(0, SPTTT->find(" "));
	std::string rest = SPTTT->substr(SPTTT->find(" ")+1); // take of the squares part
	std::string playerToPlay = rest.substr(0, rest.find(" "));
	std::string lastPlayedSquare = rest.substr(rest.find(" ") + 1);
	if (playerToPlay == "O") game->playerToPlay = O;
	else game->playerToPlay = X;
	if (lastPlayedSquare == "-") game->lastSubSquare = -1;
	else if (lastPlayedSquare == "A") game->lastSubSquare = A;
	else if (lastPlayedSquare == "B") game->lastSubSquare = B;
	else if (lastPlayedSquare == "C") game->lastSubSquare = C;
	else if (lastPlayedSquare == "D") game->lastSubSquare = D;
	else if (lastPlayedSquare == "E") game->lastSubSquare = E;
	else if (lastPlayedSquare == "F") game->lastSubSquare = F;
	else if (lastPlayedSquare == "G") game->lastSubSquare = G;
	else if (lastPlayedSquare == "H") game->lastSubSquare = H;
	else if (lastPlayedSquare == "I") game->lastSubSquare = I;
	else game->lastSubSquare = -1;
	int ind = 0;
	for (char c : SPTTT->substr(0, 9)) {
		ind++;
		if (c == 'X') game->playerX.bord1 |= intToSubBoard(ind);
		else if (c == 'O') game->playerO.bord1 |= intToSubBoard(ind);
	}
	ind = 0;
	for (char c : SPTTT->substr(9, 9)) {
		ind++;
		if (c == 'X') game->playerX.bord2 |= intToSubBoard(ind);
		else if (c == 'O') game->playerO.bord2 |= intToSubBoard(ind);
	}
	ind = 0;
	for (char c : SPTTT->substr(18, 9)) {
		ind++;
		if (c == 'X') game->playerX.bord3 |= intToSubBoard(ind);
		else if (c == 'O') game->playerO.bord3 |= intToSubBoard(ind);
	}
	ind = 0;
	for (char c : SPTTT->substr(27, 9)) {
		ind++;
		if (c == 'X') game->playerX.bord4 |= intToSubBoard(ind);
		else if (c == 'O') game->playerO.bord4 |= intToSubBoard(ind);
	}
	ind = 0;
	for (char c : SPTTT->substr(36, 9)) {
		ind++;
		if (c == 'X') game->playerX.bord5 |= intToSubBoard(ind);
		else if (c == 'O') game->playerO.bord5 |= intToSubBoard(ind);
	}
	ind = 0;
	for (char c : SPTTT->substr(45, 9)) {
		ind++;
		if (c == 'X') game->playerX.bord6 |= intToSubBoard(ind);
		else if (c == 'O') game->playerO.bord6 |= intToSubBoard(ind);
	}
	ind = 0;
	for (char c : SPTTT->substr(54, 9)) {
		ind++;
		if (c == 'X') game->playerX.bord7 |= intToSubBoard(ind);
		else if (c == 'O') game->playerO.bord7 |= intToSubBoard(ind);
	}
	ind = 0;
	for (char c : SPTTT->substr(63, 9)) {
		ind++;
		if (c == 'X') game->playerX.bord8 |= intToSubBoard(ind);
		else if (c == 'O') game->playerO.bord8 |= intToSubBoard(ind);
	}
	ind = 0;
	for (char c : SPTTT->substr(72, 9)) {
		ind++;
		if (c == 'X') game->playerX.bord9 |= intToSubBoard(ind);
		else if (c == 'O') game->playerO.bord9 |= intToSubBoard(ind);
	}
	if (!(game->lastSubSquare == -1)) {
		if (extraInfo) cout << "check happening" << endl;
		if (subSqWon(game, (SuperSquare)game->lastSubSquare)) {
			if (extraInfo) cout << "subsquare fixed" << endl;
			game->lastSubSquare = -1;
		}
	}
	fillSuperBoardGame(game);
	if (extraInfo) { if (gameWon(game)) cout << "game already won" << endl; }
	if (extraInfo) printBoard(game, true);
}

bool checkPlayerEmpty(Player* player) {
	if (player->bord1 != 0) return false;
	if (player->bord2 != 0) return false;
	if (player->bord3 != 0) return false;
	if (player->bord4 != 0) return false;
	if (player->bord5 != 0) return false;
	if (player->bord6 != 0) return false;
	if (player->bord7 != 0) return false;
	if (player->bord8 != 0) return false;
	if (player->bord9 != 0) return false;
}

bool checkSquaresOver(Game* game) {
	Player empty;
	empty.bord1 = (~(game->playerX.bord1 | game->playerO.bord1)) & 0b111111111;
	empty.bord2 = (~(game->playerX.bord2 | game->playerO.bord2)) & 0b111111111;
	empty.bord3 = (~(game->playerX.bord3 | game->playerO.bord3)) & 0b111111111;
	empty.bord4 = (~(game->playerX.bord4 | game->playerO.bord4)) & 0b111111111;
	empty.bord5 = (~(game->playerX.bord5 | game->playerO.bord5)) & 0b111111111;
	empty.bord6 = (~(game->playerX.bord6 | game->playerO.bord6)) & 0b111111111;
	empty.bord7 = (~(game->playerX.bord7 | game->playerO.bord7)) & 0b111111111;
	empty.bord8 = (~(game->playerX.bord8 | game->playerO.bord8)) & 0b111111111;
	empty.bord9 = (~(game->playerX.bord9 | game->playerO.bord9)) & 0b111111111;
	return !checkPlayerEmpty(&empty);
}

void genLegalMoves(Game* game, MOVELIST* moveList); // abstract to use it in the next function defined later in this file

bool checkMovesOver(Game* game) {
	MOVELIST moveList;
	moveList.count = 0;
	genLegalMoves(game, &moveList);
	return !(moveList.count == 0);
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

bool subSqGameOver(subBoard subp1, subBoard subp2) { return checkWon(subp1, subp2, X) || checkWon(subp1, subp2, O);}

bool subSqWon(Game* game, SuperSquare sup) {
	if (sup == A) return subSqGameOver(game->playerX.bord1, game->playerO.bord1);
	if (sup == B) return subSqGameOver(game->playerX.bord2, game->playerO.bord2);
	if (sup == C) return subSqGameOver(game->playerX.bord3, game->playerO.bord3);
	if (sup == D) return subSqGameOver(game->playerX.bord4, game->playerO.bord4);
	if (sup == E) return subSqGameOver(game->playerX.bord5, game->playerO.bord5);
	if (sup == F) return subSqGameOver(game->playerX.bord6, game->playerO.bord6);
	if (sup == G) return subSqGameOver(game->playerX.bord7, game->playerO.bord7);
	if (sup == H) return subSqGameOver(game->playerX.bord8, game->playerO.bord8);
	if (sup == I) return subSqGameOver(game->playerX.bord9, game->playerO.bord9);
}

bool gameWon(Game* game, Symbol s) {
	if (s == X) return checkWon(game->playerX.superBord, game->playerO.superBord, X);
	else return checkWon(game->playerX.superBord, game->playerO.superBord, O);
}

bool gameWon(Game* game) {
	return checkWon(game->playerX.superBord, game->playerO.superBord, X) || checkWon(game->playerX.superBord, game->playerO.superBord, O);
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

void genLegalMovesSubBoard(subBoard p1, subBoard p2, Symbol s, MOVELIST* movelist, SuperSquare sup) { //TODO reverse the order of the moves to be correct
	if (checkWon(p1, p2, X) || checkWon(p1, p2, O)) return;
	subBoard empty = (~(p1 | p2)) &0b111111111;
	Move* m = &movelist->moves[movelist->count];
	while (empty) {
		m->dst = supIndToSquare(sup, 9-countTrailingZeros(empty));
		m->s = s;
		m++;
		movelist->count++;
		empty &= (empty - 1); // Clear the least significant set bit
	}
}

void genLegalMoves(Game* game, Symbol s, MOVELIST* moveList) {
	if (game->lastSubSquare == -1 || subSqWon(game,(SuperSquare)game->lastSubSquare)) {
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

	if (game->lastSubSquare == A) { genLegalMovesSubBoard(game->playerO.bord1, game->playerX.bord1, s, moveList, A); return; }
	if (game->lastSubSquare == B) { genLegalMovesSubBoard(game->playerO.bord2, game->playerX.bord2, s, moveList, B); return; }
	if (game->lastSubSquare == C) { genLegalMovesSubBoard(game->playerO.bord3, game->playerX.bord3, s, moveList, C); return; }
	if (game->lastSubSquare == D) { genLegalMovesSubBoard(game->playerO.bord4, game->playerX.bord4, s, moveList, D); return; }
	if (game->lastSubSquare == E) { genLegalMovesSubBoard(game->playerO.bord5, game->playerX.bord5, s, moveList, E); return; }
	if (game->lastSubSquare == F) { genLegalMovesSubBoard(game->playerO.bord6, game->playerX.bord6, s, moveList, F); return; }
	if (game->lastSubSquare == G) { genLegalMovesSubBoard(game->playerO.bord7, game->playerX.bord7, s, moveList, G); return; }
	if (game->lastSubSquare == H) { genLegalMovesSubBoard(game->playerO.bord8, game->playerX.bord8, s, moveList, H); return; }
	if (game->lastSubSquare == I) { genLegalMovesSubBoard(game->playerO.bord9, game->playerX.bord9, s, moveList, I); return; }

}

void genLegalMoves(Game* game, MOVELIST* moveList) {
	if (game->playerToPlay == X) genLegalMoves(game, X, moveList);
	else genLegalMoves(game, O, moveList);
}

void makeMove(Game* game, Move* m) {
	short ind;
	if (m->dst == A1 || m->dst == B1 || m->dst == C1 || m->dst == D1 || m->dst == E1 || m->dst == F1 || m->dst == G1 || m->dst == H1 || m->dst == I1) ind = 1;
	if (m->dst == A2 || m->dst == B2 || m->dst == C2 || m->dst == D2 || m->dst == E2 || m->dst == F2 || m->dst == G2 || m->dst == H2 || m->dst == I2) ind = 2;
	if (m->dst == A3 || m->dst == B3 || m->dst == C3 || m->dst == D3 || m->dst == E3 || m->dst == F3 || m->dst == G3 || m->dst == H3 || m->dst == I3) ind = 3;
	if (m->dst == A4 || m->dst == B4 || m->dst == C4 || m->dst == D4 || m->dst == E4 || m->dst == F4 || m->dst == G4 || m->dst == H4 || m->dst == I4) ind = 4;
	if (m->dst == A5 || m->dst == B5 || m->dst == C5 || m->dst == D5 || m->dst == E5 || m->dst == F5 || m->dst == G5 || m->dst == H5 || m->dst == I5) ind = 5;
	if (m->dst == A6 || m->dst == B6 || m->dst == C6 || m->dst == D6 || m->dst == E6 || m->dst == F6 || m->dst == G6 || m->dst == H6 || m->dst == I6) ind = 6;
	if (m->dst == A7 || m->dst == B7 || m->dst == C7 || m->dst == D7 || m->dst == E7 || m->dst == F7 || m->dst == G7 || m->dst == H7 || m->dst == I7) ind = 7;
	if (m->dst == A8 || m->dst == B8 || m->dst == C8 || m->dst == D8 || m->dst == E8 || m->dst == F8 || m->dst == G8 || m->dst == H8 || m->dst == I8) ind = 8;
	if (m->dst == A9 || m->dst == B9 || m->dst == C9 || m->dst == D9 || m->dst == E9 || m->dst == F9 || m->dst == G9 || m->dst == H9 || m->dst == I9) ind = 9;
	SuperSquare supSq;
	if (m->dst == A1 || m->dst == A2 || m->dst == A3 || m->dst == A4 || m->dst == A5 || m->dst == A6 || m->dst == A7 || m->dst == A8 || m->dst == A9) supSq = A;
	if (m->dst == B1 || m->dst == B2 || m->dst == B3 || m->dst == B4 || m->dst == B5 || m->dst == B6 || m->dst == B7 || m->dst == B8 || m->dst == B9) supSq = B;
	if (m->dst == C1 || m->dst == C2 || m->dst == C3 || m->dst == C4 || m->dst == C5 || m->dst == C6 || m->dst == C7 || m->dst == C8 || m->dst == C9) supSq = C;
	if (m->dst == D1 || m->dst == D2 || m->dst == D3 || m->dst == D4 || m->dst == D5 || m->dst == D6 || m->dst == D7 || m->dst == D8 || m->dst == D9) supSq = D;
	if (m->dst == E1 || m->dst == E2 || m->dst == E3 || m->dst == E4 || m->dst == E5 || m->dst == E6 || m->dst == E7 || m->dst == E8 || m->dst == E9) supSq = E;
	if (m->dst == F1 || m->dst == F2 || m->dst == F3 || m->dst == F4 || m->dst == F5 || m->dst == F6 || m->dst == F7 || m->dst == F8 || m->dst == F9) supSq = F;
	if (m->dst == G1 || m->dst == G2 || m->dst == G3 || m->dst == G4 || m->dst == G5 || m->dst == G6 || m->dst == G7 || m->dst == G8 || m->dst == G9) supSq = G;
	if (m->dst == H1 || m->dst == H2 || m->dst == H3 || m->dst == H4 || m->dst == H5 || m->dst == H6 || m->dst == H7 || m->dst == H8 || m->dst == H9) supSq = H;
	if (m->dst == I1 || m->dst == I2 || m->dst == I3 || m->dst == I4 || m->dst == I5 || m->dst == I6 || m->dst == I7 || m->dst == I8 || m->dst == I9) supSq = I;
	if (m->s == X) {
		if (supSq == A) { game->playerX.bord1 |= intToSubBoard(ind); game->playerToPlay = O; game->lastSubSquare = ind - 1; fillSuperBoardGame(game); return; }
		if (supSq == B) { game->playerX.bord2 |= intToSubBoard(ind); game->playerToPlay = O; game->lastSubSquare = ind - 1; fillSuperBoardGame(game); return; }
		if (supSq == C) { game->playerX.bord3 |= intToSubBoard(ind); game->playerToPlay = O; game->lastSubSquare = ind - 1; fillSuperBoardGame(game); return; }
		if (supSq == D) { game->playerX.bord4 |= intToSubBoard(ind); game->playerToPlay = O; game->lastSubSquare = ind - 1; fillSuperBoardGame(game); return; }
		if (supSq == E) { game->playerX.bord5 |= intToSubBoard(ind); game->playerToPlay = O; game->lastSubSquare = ind - 1; fillSuperBoardGame(game); return; }
		if (supSq == F) { game->playerX.bord6 |= intToSubBoard(ind); game->playerToPlay = O; game->lastSubSquare = ind - 1; fillSuperBoardGame(game); return; }
		if (supSq == G) { game->playerX.bord7 |= intToSubBoard(ind); game->playerToPlay = O; game->lastSubSquare = ind - 1; fillSuperBoardGame(game); return; }
		if (supSq == H) { game->playerX.bord8 |= intToSubBoard(ind); game->playerToPlay = O; game->lastSubSquare = ind - 1; fillSuperBoardGame(game); return; }
		if (supSq == I) { game->playerX.bord9 |= intToSubBoard(ind); game->playerToPlay = O; game->lastSubSquare = ind - 1; fillSuperBoardGame(game); return; }
	}
	if (m->s == O) {
		if (supSq == A) { game->playerO.bord1 |= intToSubBoard(ind); game->playerToPlay = X; game->lastSubSquare = ind - 1; fillSuperBoardGame(game); return; }
		if (supSq == B) { game->playerO.bord2 |= intToSubBoard(ind); game->playerToPlay = X; game->lastSubSquare = ind - 1; fillSuperBoardGame(game); return; }
		if (supSq == C) { game->playerO.bord3 |= intToSubBoard(ind); game->playerToPlay = X; game->lastSubSquare = ind - 1; fillSuperBoardGame(game); return; }
		if (supSq == D) { game->playerO.bord4 |= intToSubBoard(ind); game->playerToPlay = X; game->lastSubSquare = ind - 1; fillSuperBoardGame(game); return; }
		if (supSq == E) { game->playerO.bord5 |= intToSubBoard(ind); game->playerToPlay = X; game->lastSubSquare = ind - 1; fillSuperBoardGame(game); return; }
		if (supSq == F) { game->playerO.bord6 |= intToSubBoard(ind); game->playerToPlay = X; game->lastSubSquare = ind - 1; fillSuperBoardGame(game); return; }
		if (supSq == G) { game->playerO.bord7 |= intToSubBoard(ind); game->playerToPlay = X; game->lastSubSquare = ind - 1; fillSuperBoardGame(game); return; }
		if (supSq == H) { game->playerO.bord8 |= intToSubBoard(ind); game->playerToPlay = X; game->lastSubSquare = ind - 1; fillSuperBoardGame(game); return; }
		if (supSq == I) { game->playerO.bord9 |= intToSubBoard(ind); game->playerToPlay = X; game->lastSubSquare = ind - 1; fillSuperBoardGame(game); return; }
	}
}

void undoMove(Game* game, Move* m, int oldSquare) {
	short ind;
	if (m->dst == A1 || m->dst == B1 || m->dst == C1 || m->dst == D1 || m->dst == E1 || m->dst == F1 || m->dst == G1 || m->dst == H1 || m->dst == I1) ind = 1;
	if (m->dst == A2 || m->dst == B2 || m->dst == C2 || m->dst == D2 || m->dst == E2 || m->dst == F2 || m->dst == G2 || m->dst == H2 || m->dst == I2) ind = 2;
	if (m->dst == A3 || m->dst == B3 || m->dst == C3 || m->dst == D3 || m->dst == E3 || m->dst == F3 || m->dst == G3 || m->dst == H3 || m->dst == I3) ind = 3;
	if (m->dst == A4 || m->dst == B4 || m->dst == C4 || m->dst == D4 || m->dst == E4 || m->dst == F4 || m->dst == G4 || m->dst == H4 || m->dst == I4) ind = 4;
	if (m->dst == A5 || m->dst == B5 || m->dst == C5 || m->dst == D5 || m->dst == E5 || m->dst == F5 || m->dst == G5 || m->dst == H5 || m->dst == I5) ind = 5;
	if (m->dst == A6 || m->dst == B6 || m->dst == C6 || m->dst == D6 || m->dst == E6 || m->dst == F6 || m->dst == G6 || m->dst == H6 || m->dst == I6) ind = 6;
	if (m->dst == A7 || m->dst == B7 || m->dst == C7 || m->dst == D7 || m->dst == E7 || m->dst == F7 || m->dst == G7 || m->dst == H7 || m->dst == I7) ind = 7;
	if (m->dst == A8 || m->dst == B8 || m->dst == C8 || m->dst == D8 || m->dst == E8 || m->dst == F8 || m->dst == G8 || m->dst == H8 || m->dst == I8) ind = 8;
	if (m->dst == A9 || m->dst == B9 || m->dst == C9 || m->dst == D9 || m->dst == E9 || m->dst == F9 || m->dst == G9 || m->dst == H9 || m->dst == I9) ind = 9;
	SuperSquare supSq;
	if (m->dst == A1 || m->dst == A2 || m->dst == A3 || m->dst == A4 || m->dst == A5 || m->dst == A6 || m->dst == A7 || m->dst == A8 || m->dst == A9) supSq = A;
	if (m->dst == B1 || m->dst == B2 || m->dst == B3 || m->dst == B4 || m->dst == B5 || m->dst == B6 || m->dst == B7 || m->dst == B8 || m->dst == B9) supSq = B;
	if (m->dst == C1 || m->dst == C2 || m->dst == C3 || m->dst == C4 || m->dst == C5 || m->dst == C6 || m->dst == C7 || m->dst == C8 || m->dst == C9) supSq = C;
	if (m->dst == D1 || m->dst == D2 || m->dst == D3 || m->dst == D4 || m->dst == D5 || m->dst == D6 || m->dst == D7 || m->dst == D8 || m->dst == D9) supSq = D;
	if (m->dst == E1 || m->dst == E2 || m->dst == E3 || m->dst == E4 || m->dst == E5 || m->dst == E6 || m->dst == E7 || m->dst == E8 || m->dst == E9) supSq = E;
	if (m->dst == F1 || m->dst == F2 || m->dst == F3 || m->dst == F4 || m->dst == F5 || m->dst == F6 || m->dst == F7 || m->dst == F8 || m->dst == F9) supSq = F;
	if (m->dst == G1 || m->dst == G2 || m->dst == G3 || m->dst == G4 || m->dst == G5 || m->dst == G6 || m->dst == G7 || m->dst == G8 || m->dst == G9) supSq = G;
	if (m->dst == H1 || m->dst == H2 || m->dst == H3 || m->dst == H4 || m->dst == H5 || m->dst == H6 || m->dst == H7 || m->dst == H8 || m->dst == H9) supSq = H;
	if (m->dst == I1 || m->dst == I2 || m->dst == I3 || m->dst == I4 || m->dst == I5 || m->dst == I6 || m->dst == I7 || m->dst == I8 || m->dst == I9) supSq = I;
	if (m->s == X) {
		if (supSq == A) { game->playerX.bord1 &= ~intToSubBoard(ind); game->playerToPlay = O; game->lastSubSquare = oldSquare; fillSuperBoardGame(game); return;}
		if (supSq == B) { game->playerX.bord2 &= ~intToSubBoard(ind); game->playerToPlay = O; game->lastSubSquare = oldSquare; fillSuperBoardGame(game); return;}
		if (supSq == C) { game->playerX.bord3 &= ~intToSubBoard(ind); game->playerToPlay = O; game->lastSubSquare = oldSquare; fillSuperBoardGame(game); return; }
		if (supSq == D) { game->playerX.bord4 &= ~intToSubBoard(ind); game->playerToPlay = O; game->lastSubSquare = oldSquare; fillSuperBoardGame(game); return; }
		if (supSq == E) { game->playerX.bord5 &= ~intToSubBoard(ind); game->playerToPlay = O; game->lastSubSquare = oldSquare; fillSuperBoardGame(game); return; }
		if (supSq == F) { game->playerX.bord6 &= ~intToSubBoard(ind); game->playerToPlay = O; game->lastSubSquare = oldSquare; fillSuperBoardGame(game); return; }
		if (supSq == G) { game->playerX.bord7 &= ~intToSubBoard(ind); game->playerToPlay = O; game->lastSubSquare = oldSquare; fillSuperBoardGame(game); return; }
		if (supSq == H) { game->playerX.bord8 &= ~intToSubBoard(ind); game->playerToPlay = O; game->lastSubSquare = oldSquare; fillSuperBoardGame(game); return; }
		if (supSq == I) { game->playerX.bord9 &= ~intToSubBoard(ind); game->playerToPlay = O; game->lastSubSquare = oldSquare; fillSuperBoardGame(game); return; }
	}
	if (m->s == O) {
		if (supSq == A) { game->playerO.bord1 &= ~intToSubBoard(ind); game->playerToPlay = O; game->lastSubSquare = oldSquare; fillSuperBoardGame(game); return; }
		if (supSq == B) { game->playerO.bord2 &= ~intToSubBoard(ind); game->playerToPlay = O; game->lastSubSquare = oldSquare; fillSuperBoardGame(game); return; }
		if (supSq == C) { game->playerO.bord3 &= ~intToSubBoard(ind); game->playerToPlay = O; game->lastSubSquare = oldSquare; fillSuperBoardGame(game); return; }
		if (supSq == D) { game->playerO.bord4 &= ~intToSubBoard(ind); game->playerToPlay = O; game->lastSubSquare = oldSquare; fillSuperBoardGame(game); return; }
		if (supSq == E) { game->playerO.bord5 &= ~intToSubBoard(ind); game->playerToPlay = O; game->lastSubSquare = oldSquare; fillSuperBoardGame(game); return; }
		if (supSq == F) { game->playerO.bord6 &= ~intToSubBoard(ind); game->playerToPlay = O; game->lastSubSquare = oldSquare; fillSuperBoardGame(game); return; }
		if (supSq == G) { game->playerO.bord7 &= ~intToSubBoard(ind); game->playerToPlay = O; game->lastSubSquare = oldSquare; fillSuperBoardGame(game); return; }
		if (supSq == H) { game->playerO.bord8 &= ~intToSubBoard(ind); game->playerToPlay = O; game->lastSubSquare = oldSquare; fillSuperBoardGame(game); return; }
		if (supSq == I) { game->playerO.bord9 &= ~intToSubBoard(ind); game->playerToPlay = O; game->lastSubSquare = oldSquare; fillSuperBoardGame(game); return; }
	}
} //TODO a lot of testing

void printSubBoard(subBoard sub, char c) {
	cout << "-------" << endl;
	cout << "|" << bitToChar((sub >> 8) & 1, c) << "|" << bitToChar((sub >> 7) & 1, c) << "|" << bitToChar((sub >> 6) & 1, c) << "|" << endl;
	cout << "-------" << endl;
	cout << "|" << bitToChar((sub >> 5) & 1, c) << "|" << bitToChar((sub >> 4) & 1, c) << "|" << bitToChar((sub >> 3) & 1, c) << "|" << endl;
	cout << "-------" << endl;
	cout << "|" << bitToChar((sub >> 2) & 1, c) << "|" << bitToChar((sub >> 1) & 1, c) << "|" << bitToChar((sub >> 0) & 1, c) << "|" << endl;
	cout << "-------" << endl;
}

void printUnicode(int count = 1, int colour = FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE) {
	wchar_t unicodeChar = L'\x2588';
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(hConsole, colour);
	for (int i = 0; i < count; i++) {
		DWORD charsWritten;
		WriteConsoleW(hConsole, &unicodeChar, 1, &charsWritten, NULL);
	}
	SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
}

void printOverlayedSubBoard(subBoard subP1, subBoard subP2, char p1, char p2) {
	printUnicode(21, GREEN);
	cout << endl;
	printUnicode(3, GREEN);
	if ((subP1 >> 8) & 1) cout << " " << bitToChar(1, p1) << " ";
	else if ((subP2 >> 8) & 1) cout << " " << bitToChar(1, p2) << " ";
	else cout << "   ";
	printUnicode(3, GREEN);
	if ((subP1 >> 7) & 1) cout << " " << bitToChar(1, p1) << " ";
	else if ((subP2 >> 7) & 1) cout << " " << bitToChar(1, p2) << " ";
	else cout << "   ";
	printUnicode(3, GREEN);
	if ((subP1 >> 6) & 1) cout << " " << bitToChar(1, p1) << " ";
	else if ((subP2 >> 6) & 1) cout << " " << bitToChar(1, p2) << " ";
	else cout << "   ";
	printUnicode(3, GREEN);
	cout << endl;
	printUnicode(21, GREEN);
	cout << endl;
	printUnicode(3, GREEN);
	if ((subP1 >> 5) & 1) cout << " " << bitToChar(1, p1) << " ";
	else if ((subP2 >> 5) & 1) cout << " " << bitToChar(1, p2) << " ";
	else cout << "   ";
	printUnicode(3, GREEN);
	if ((subP1 >> 4) & 1) cout << " " << bitToChar(1, p1) << " ";
	else if ((subP2 >> 4) & 1) cout << " " << bitToChar(1, p2) << " ";
	else cout << "   ";
	printUnicode(3, GREEN);
	if ((subP1 >> 3) & 1) cout << " " << bitToChar(1, p1) << " ";
	else if ((subP2 >> 3) & 1) cout << " " << bitToChar(1, p2) << " ";
	else cout << "   ";
	printUnicode(3, GREEN);
	cout << endl;
	printUnicode(21, GREEN);
	cout << endl;
	printUnicode(3, GREEN);
	if ((subP1 >> 2) & 1) cout << " " << bitToChar(1, p1) << " ";
	else if ((subP2 >> 2) & 1) cout << " " << bitToChar(1, p2) << " ";
	else cout << "   ";
	printUnicode(3, GREEN);
	if ((subP1 >> 1) & 1) cout << " " << bitToChar(1, p1) << " ";
	else if ((subP2 >> 1) & 1) cout << " " << bitToChar(1, p2) << " ";
	else cout << "   ";
	printUnicode(3, GREEN);
	if (subP1 & 1) cout << " " << bitToChar(1, p1) << " ";
	else if (subP2 & 1) cout << " " << bitToChar(1, p2) << " ";
	else cout << "   ";
	printUnicode(3, GREEN);
	cout << endl;
	printUnicode(21, GREEN);
	cout << endl;
}

void printBoard(Game* game, bool drawSuperGame) {
	char p1 = 'X';
	char p2 = 'O';
	// first 3 blocks
	printUnicode(57, BLUE);
	ENTER;
	printUnicode(3, BLUE);
	if ((game->playerX.bord1 >> 8) & 1) cout << " " << bitToChar(1, p1) << " ";
	else if ((game->playerO.bord1 >> 8) & 1) cout << " " << bitToChar(1, p2) << " ";
	else cout << "   ";
	printUnicode(3, RED);
	if ((game->playerX.bord1 >> 7) & 1) cout << " " << bitToChar(1, p1) << " ";
	else if ((game->playerO.bord1 >> 7) & 1) cout << " " << bitToChar(1, p2) << " ";
	else cout << "   ";
	printUnicode(3, RED);
	if ((game->playerX.bord1 >> 6) & 1) cout << " " << bitToChar(1, p1) << " ";
	else if ((game->playerO.bord1 >> 6) & 1) cout << " " << bitToChar(1, p2) << " ";
	else cout << "   ";
	printUnicode(3, BLUE);
	if ((game->playerX.bord2 >> 8) & 1) cout << " " << bitToChar(1, p1) << " ";
	else if ((game->playerO.bord2 >> 8) & 1) cout << " " << bitToChar(1, p2) << " ";
	else cout << "   ";
	printUnicode(3, RED);
	if ((game->playerX.bord2 >> 7) & 1) cout << " " << bitToChar(1, p1) << " ";
	else if ((game->playerO.bord2 >> 7) & 1) cout << " " << bitToChar(1, p2) << " ";
	else cout << "   ";
	printUnicode(3, RED);
	if ((game->playerX.bord2 >> 6) & 1) cout << " " << bitToChar(1, p1) << " ";
	else if ((game->playerO.bord2 >> 6) & 1) cout << " " << bitToChar(1, p2) << " ";
	else cout << "   ";
	printUnicode(3, BLUE);
	if ((game->playerX.bord3 >> 8) & 1) cout << " " << bitToChar(1, p1) << " ";
	else if ((game->playerO.bord3 >> 8) & 1) cout << " " << bitToChar(1, p2) << " ";
	else cout << "   ";
	printUnicode(3, RED);
	if ((game->playerX.bord3 >> 7) & 1) cout << " " << bitToChar(1, p1) << " ";
	else if ((game->playerO.bord3 >> 7) & 1) cout << " " << bitToChar(1, p2) << " ";
	else cout << "   ";
	printUnicode(3, RED);
	if ((game->playerX.bord3 >> 6) & 1) cout << " " << bitToChar(1, p1) << " ";
	else if ((game->playerO.bord3 >> 6) & 1) cout << " " << bitToChar(1, p2) << " ";
	else cout << "   ";
	printUnicode(3, BLUE);
	ENTER;

	printUnicode(3, BLUE);
	printUnicode(15, RED);
	printUnicode(3, BLUE);
	printUnicode(15, RED);
	printUnicode(3, BLUE);
	printUnicode(15, RED);
	printUnicode(3, BLUE);
	ENTER;

	printUnicode(3, BLUE);
	if ((game->playerX.bord1 >> 5) & 1) cout << " " << bitToChar(1, p1) << " ";
	else if ((game->playerO.bord1 >> 5) & 1) cout << " " << bitToChar(1, p2) << " ";
	else cout << "   ";
	printUnicode(3, RED);
	if ((game->playerX.bord1 >> 4) & 1) cout << " " << bitToChar(1, p1) << " ";
	else if ((game->playerO.bord1 >> 4) & 1) cout << " " << bitToChar(1, p2) << " ";
	else cout << "   ";
	printUnicode(3, RED);
	if ((game->playerX.bord1 >> 3) & 1) cout << " " << bitToChar(1, p1) << " ";
	else if ((game->playerO.bord1 >> 3) & 1) cout << " " << bitToChar(1, p2) << " ";
	else cout << "   ";
	printUnicode(3, BLUE);
	if ((game->playerX.bord2 >> 5) & 1) cout << " " << bitToChar(1, p1) << " ";
	else if ((game->playerO.bord2 >> 5) & 1) cout << " " << bitToChar(1, p2) << " ";
	else cout << "   ";
	printUnicode(3, RED);
	if ((game->playerX.bord2 >> 4) & 1) cout << " " << bitToChar(1, p1) << " ";
	else if ((game->playerO.bord2 >> 4) & 1) cout << " " << bitToChar(1, p2) << " ";
	else cout << "   ";
	printUnicode(3, RED);
	if ((game->playerX.bord2 >> 3) & 1) cout << " " << bitToChar(1, p1) << " ";
	else if ((game->playerO.bord2 >> 3) & 1) cout << " " << bitToChar(1, p2) << " ";
	else cout << "   ";
	printUnicode(3, BLUE);
	if ((game->playerX.bord3 >> 5) & 1) cout << " " << bitToChar(1, p1) << " ";
	else if ((game->playerO.bord3 >> 5) & 1) cout << " " << bitToChar(1, p2) << " ";
	else cout << "   ";
	printUnicode(3, RED);
	if ((game->playerX.bord3 >> 4) & 1) cout << " " << bitToChar(1, p1) << " ";
	else if ((game->playerO.bord3 >> 4) & 1) cout << " " << bitToChar(1, p2) << " ";
	else cout << "   ";
	printUnicode(3, RED);
	if ((game->playerX.bord3 >> 3) & 1) cout << " " << bitToChar(1, p1) << " ";
	else if ((game->playerO.bord3 >> 3) & 1) cout << " " << bitToChar(1, p2) << " ";
	else cout << "   ";
	printUnicode(3, BLUE);
	ENTER;

	printUnicode(3, BLUE);
	printUnicode(15, RED);
	printUnicode(3, BLUE);
	printUnicode(15, RED);
	printUnicode(3, BLUE);
	printUnicode(15, RED);
	printUnicode(3, BLUE);
	ENTER;

	printUnicode(3, BLUE);
	if ((game->playerX.bord1 >> 2) & 1) cout << " " << bitToChar(1, p1) << " ";
	else if ((game->playerO.bord1 >> 2) & 1) cout << " " << bitToChar(1, p2) << " ";
	else cout << "   ";
	printUnicode(3, RED);
	if ((game->playerX.bord1 >> 1) & 1) cout << " " << bitToChar(1, p1) << " ";
	else if ((game->playerO.bord1 >> 1) & 1) cout << " " << bitToChar(1, p2) << " ";
	else cout << "   ";
	printUnicode(3, RED);
	if (game->playerX.bord1 & 1) cout << " " << bitToChar(1, p1) << " ";
	else if (game->playerO.bord1 & 1) cout << " " << bitToChar(1, p2) << " ";
	else cout << "   ";
	printUnicode(3, BLUE);
	if ((game->playerX.bord2 >> 2) & 1) cout << " " << bitToChar(1, p1) << " ";
	else if ((game->playerO.bord2 >> 2) & 1) cout << " " << bitToChar(1, p2) << " ";
	else cout << "   ";
	printUnicode(3, RED);
	if ((game->playerX.bord2 >> 1) & 1) cout << " " << bitToChar(1, p1) << " ";
	else if ((game->playerO.bord2 >> 1) & 1) cout << " " << bitToChar(1, p2) << " ";
	else cout << "   ";
	printUnicode(3, RED);
	if (game->playerX.bord2 & 1) cout << " " << bitToChar(1, p1) << " ";
	else if (game->playerO.bord2 & 1) cout << " " << bitToChar(1, p2) << " ";
	else cout << "   ";
	printUnicode(3, BLUE);
	if ((game->playerX.bord3 >> 2) & 1) cout << " " << bitToChar(1, p1) << " ";
	else if ((game->playerO.bord3 >> 2) & 1) cout << " " << bitToChar(1, p2) << " ";
	else cout << "   ";
	printUnicode(3, RED);
	if ((game->playerX.bord3 >> 1) & 1) cout << " " << bitToChar(1, p1) << " ";
	else if ((game->playerO.bord3 >> 1) & 1) cout << " " << bitToChar(1, p2) << " ";
	else cout << "   ";
	printUnicode(3, RED);
	if (game->playerX.bord3 & 1) cout << " " << bitToChar(1, p1) << " ";
	else if (game->playerO.bord3 & 1) cout << " " << bitToChar(1, p2) << " ";
	else cout << "   ";
	printUnicode(3, BLUE); ENTER;
	printUnicode(57, BLUE); ENTER;
	// midle 3 blocks
	printUnicode(3, BLUE);
	if ((game->playerX.bord4 >> 8) & 1) cout << " " << bitToChar(1, p1) << " ";
	else if ((game->playerO.bord4 >> 8) & 1) cout << " " << bitToChar(1, p2) << " ";
	else cout << "   ";
	printUnicode(3, RED);
	if ((game->playerX.bord4 >> 7) & 1) cout << " " << bitToChar(1, p1) << " ";
	else if ((game->playerO.bord4 >> 7) & 1) cout << " " << bitToChar(1, p2) << " ";
	else cout << "   ";
	printUnicode(3, RED);
	if ((game->playerX.bord4 >> 6) & 1) cout << " " << bitToChar(1, p1) << " ";
	else if ((game->playerO.bord4 >> 6) & 1) cout << " " << bitToChar(1, p2) << " ";
	else cout << "   ";
	printUnicode(3, BLUE);
	if ((game->playerX.bord5 >> 8) & 1) cout << " " << bitToChar(1, p1) << " ";
	else if ((game->playerO.bord5 >> 8) & 1) cout << " " << bitToChar(1, p2) << " ";
	else cout << "   ";
	printUnicode(3, RED);
	if ((game->playerX.bord5 >> 7) & 1) cout << " " << bitToChar(1, p1) << " ";
	else if ((game->playerO.bord5 >> 7) & 1) cout << " " << bitToChar(1, p2) << " ";
	else cout << "   ";
	printUnicode(3, RED);
	if ((game->playerX.bord5 >> 6) & 1) cout << " " << bitToChar(1, p1) << " ";
	else if ((game->playerO.bord5 >> 6) & 1) cout << " " << bitToChar(1, p2) << " ";
	else cout << "   ";
	printUnicode(3, BLUE);
	if ((game->playerX.bord6 >> 8) & 1) cout << " " << bitToChar(1, p1) << " ";
	else if ((game->playerO.bord6 >> 8) & 1) cout << " " << bitToChar(1, p2) << " ";
	else cout << "   ";
	printUnicode(3, RED);
	if ((game->playerX.bord6 >> 7) & 1) cout << " " << bitToChar(1, p1) << " ";
	else if ((game->playerO.bord6 >> 7) & 1) cout << " " << bitToChar(1, p2) << " ";
	else cout << "   ";
	printUnicode(3, RED);
	if ((game->playerX.bord6 >> 6) & 1) cout << " " << bitToChar(1, p1) << " ";
	else if ((game->playerO.bord6 >> 6) & 1) cout << " " << bitToChar(1, p2) << " ";
	else cout << "   ";
	printUnicode(3, BLUE); ENTER;
	printUnicode(3, BLUE);
	printUnicode(15, RED);
	printUnicode(3, BLUE);
	printUnicode(15, RED);
	printUnicode(3, BLUE);
	printUnicode(15, RED);
	printUnicode(3, BLUE);
	ENTER;
	printUnicode(3, BLUE);
	if ((game->playerX.bord4 >> 5) & 1) cout << " " << bitToChar(1, p1) << " ";
	else if ((game->playerO.bord4 >> 5) & 1) cout << " " << bitToChar(1, p2) << " ";
	else cout << "   ";
	printUnicode(3, RED);
	if ((game->playerX.bord4 >> 4) & 1) cout << " " << bitToChar(1, p1) << " ";
	else if ((game->playerO.bord4 >> 4) & 1) cout << " " << bitToChar(1, p2) << " ";
	else cout << "   ";
	printUnicode(3, RED);
	if ((game->playerX.bord4 >> 3) & 1) cout << " " << bitToChar(1, p1) << " ";
	else if ((game->playerO.bord4 >> 3) & 1) cout << " " << bitToChar(1, p2) << " ";
	else cout << "   ";
	printUnicode(3, BLUE);
	if ((game->playerX.bord5 >> 5) & 1) cout << " " << bitToChar(1, p1) << " ";
	else if ((game->playerO.bord5 >> 5) & 1) cout << " " << bitToChar(1, p2) << " ";
	else cout << "   ";
	printUnicode(3, RED);
	if ((game->playerX.bord5 >> 4) & 1) cout << " " << bitToChar(1, p1) << " ";
	else if ((game->playerO.bord5 >> 4) & 1) cout << " " << bitToChar(1, p2) << " ";
	else cout << "   ";
	printUnicode(3, RED);
	if ((game->playerX.bord5 >> 3) & 1) cout << " " << bitToChar(1, p1) << " ";
	else if ((game->playerO.bord5 >> 3) & 1) cout << " " << bitToChar(1, p2) << " ";
	else cout << "   ";
	printUnicode(3, BLUE);
	if ((game->playerX.bord6 >> 5) & 1) cout << " " << bitToChar(1, p1) << " ";
	else if ((game->playerO.bord6 >> 5) & 1) cout << " " << bitToChar(1, p2) << " ";
	else cout << "   ";
	printUnicode(3, RED);
	if ((game->playerX.bord6 >> 4) & 1) cout << " " << bitToChar(1, p1) << " ";
	else if ((game->playerO.bord6 >> 4) & 1) cout << " " << bitToChar(1, p2) << " ";
	else cout << "   ";
	printUnicode(3, RED);
	if ((game->playerX.bord6 >> 3) & 1) cout << " " << bitToChar(1, p1) << " ";
	else if ((game->playerO.bord6 >> 3) & 1) cout << " " << bitToChar(1, p2) << " ";
	else cout << "   ";
	printUnicode(3, BLUE); ENTER;
	printUnicode(3, BLUE);
	printUnicode(15, RED);
	printUnicode(3, BLUE);
	printUnicode(15, RED);
	printUnicode(3, BLUE);
	printUnicode(15, RED);
	printUnicode(3, BLUE);
	ENTER;
	printUnicode(3, BLUE);
	if ((game->playerX.bord4 >> 2) & 1) cout << " " << bitToChar(1, p1) << " ";
	else if ((game->playerO.bord4 >> 2) & 1) cout << " " << bitToChar(1, p2) << " ";
	else cout << "   ";
	printUnicode(3, RED);
	if ((game->playerX.bord4 >> 1) & 1) cout << " " << bitToChar(1, p1) << " ";
	else if ((game->playerO.bord4 >> 1) & 1) cout << " " << bitToChar(1, p2) << " ";
	else cout << "   ";
	printUnicode(3, RED);
	if (game->playerX.bord4 & 1) cout << " " << bitToChar(1, p1) << " ";
	else if (game->playerO.bord4 & 1) cout << " " << bitToChar(1, p2) << " ";
	else cout << "   ";
	printUnicode(3, BLUE);
	if ((game->playerX.bord5 >> 2) & 1) cout << " " << bitToChar(1, p1) << " ";
	else if ((game->playerO.bord5 >> 2) & 1) cout << " " << bitToChar(1, p2) << " ";
	else cout << "   ";
	printUnicode(3, RED);
	if ((game->playerX.bord5 >> 1) & 1) cout << " " << bitToChar(1, p1) << " ";
	else if ((game->playerO.bord5 >> 1) & 1) cout << " " << bitToChar(1, p2) << " ";
	else cout << "   ";
	printUnicode(3, RED);
	if (game->playerX.bord5 & 1) cout << " " << bitToChar(1, p1) << " ";
	else if (game->playerO.bord5 & 1) cout << " " << bitToChar(1, p2) << " ";
	else cout << "   ";
	printUnicode(3, BLUE);
	if ((game->playerX.bord6 >> 2) & 1) cout << " " << bitToChar(1, p1) << " ";
	else if ((game->playerO.bord6 >> 2) & 1) cout << " " << bitToChar(1, p2) << " ";
	else cout << "   ";
	printUnicode(3, RED);
	if ((game->playerX.bord6 >> 1) & 1) cout << " " << bitToChar(1, p1) << " ";
	else if ((game->playerO.bord6 >> 1) & 1) cout << " " << bitToChar(1, p2) << " ";
	else cout << "   ";
	printUnicode(3, RED);
	if (game->playerX.bord6 & 1) cout << " " << bitToChar(1, p1) << " ";
	else if (game->playerO.bord6 & 1) cout << " " << bitToChar(1, p2) << " ";
	else cout << "   ";
	printUnicode(3, BLUE); ENTER;
	printUnicode(57, BLUE); ENTER;
	// last 3 blocks
	printUnicode(3, BLUE);
	if ((game->playerX.bord7 >> 8) & 1) cout << " " << bitToChar(1, p1) << " ";
	else if ((game->playerO.bord7 >> 8) & 1) cout << " " << bitToChar(1, p2) << " ";
	else cout << "   ";
	printUnicode(3, RED);
	if ((game->playerX.bord7 >> 7) & 1) cout << " " << bitToChar(1, p1) << " ";
	else if ((game->playerO.bord7 >> 7) & 1) cout << " " << bitToChar(1, p2) << " ";
	else cout << "   ";
	printUnicode(3, RED);
	if ((game->playerX.bord7 >> 6) & 1) cout << " " << bitToChar(1, p1) << " ";
	else if ((game->playerO.bord7 >> 6) & 1) cout << " " << bitToChar(1, p2) << " ";
	else cout << "   ";
	printUnicode(3, BLUE);
	if ((game->playerX.bord8 >> 8) & 1) cout << " " << bitToChar(1, p1) << " ";
	else if ((game->playerO.bord8 >> 8) & 1) cout << " " << bitToChar(1, p2) << " ";
	else cout << "   ";
	printUnicode(3, RED);
	if ((game->playerX.bord8 >> 7) & 1) cout << " " << bitToChar(1, p1) << " ";
	else if ((game->playerO.bord8 >> 7) & 1) cout << " " << bitToChar(1, p2) << " ";
	else cout << "   ";
	printUnicode(3, RED);
	if ((game->playerX.bord8 >> 6) & 1) cout << " " << bitToChar(1, p1) << " ";
	else if ((game->playerO.bord8 >> 6) & 1) cout << " " << bitToChar(1, p2) << " ";
	else cout << "   ";
	printUnicode(3, BLUE);
	if ((game->playerX.bord9 >> 8) & 1) cout << " " << bitToChar(1, p1) << " ";
	else if ((game->playerO.bord9 >> 8) & 1) cout << " " << bitToChar(1, p2) << " ";
	else cout << "   ";
	printUnicode(3, RED);
	if ((game->playerX.bord9 >> 7) & 1) cout << " " << bitToChar(1, p1) << " ";
	else if ((game->playerO.bord9 >> 7) & 1) cout << " " << bitToChar(1, p2) << " ";
	else cout << "   ";
	printUnicode(3, RED);
	if ((game->playerX.bord9 >> 6) & 1) cout << " " << bitToChar(1, p1) << " ";
	else if ((game->playerO.bord9 >> 6) & 1) cout << " " << bitToChar(1, p2) << " ";
	else cout << "   ";
	printUnicode(3, BLUE); ENTER;
	printUnicode(3, BLUE);
	printUnicode(15, RED);
	printUnicode(3, BLUE);
	printUnicode(15, RED);
	printUnicode(3, BLUE);
	printUnicode(15, RED);
	printUnicode(3, BLUE);
	ENTER;
	printUnicode(3, BLUE);
	if ((game->playerX.bord7 >> 5) & 1) cout << " " << bitToChar(1, p1) << " ";
	else if ((game->playerO.bord7 >> 5) & 1) cout << " " << bitToChar(1, p2) << " ";
	else cout << "   ";
	printUnicode(3, RED);
	if ((game->playerX.bord7 >> 4) & 1) cout << " " << bitToChar(1, p1) << " ";
	else if ((game->playerO.bord7 >> 4) & 1) cout << " " << bitToChar(1, p2) << " ";
	else cout << "   ";
	printUnicode(3, RED);
	if ((game->playerX.bord7 >> 3) & 1) cout << " " << bitToChar(1, p1) << " ";
	else if ((game->playerO.bord7 >> 3) & 1) cout << " " << bitToChar(1, p2) << " ";
	else cout << "   ";
	printUnicode(3, BLUE);
	if ((game->playerX.bord8 >> 5) & 1) cout << " " << bitToChar(1, p1) << " ";
	else if ((game->playerO.bord8 >> 5) & 1) cout << " " << bitToChar(1, p2) << " ";
	else cout << "   ";
	printUnicode(3, RED);
	if ((game->playerX.bord8 >> 4) & 1) cout << " " << bitToChar(1, p1) << " ";
	else if ((game->playerO.bord8 >> 4) & 1) cout << " " << bitToChar(1, p2) << " ";
	else cout << "   ";
	printUnicode(3, RED);
	if ((game->playerX.bord8 >> 3) & 1) cout << " " << bitToChar(1, p1) << " ";
	else if ((game->playerO.bord8 >> 3) & 1) cout << " " << bitToChar(1, p2) << " ";
	else cout << "   ";
	printUnicode(3, BLUE);
	if ((game->playerX.bord9 >> 5) & 1) cout << " " << bitToChar(1, p1) << " ";
	else if ((game->playerO.bord9 >> 5) & 1) cout << " " << bitToChar(1, p2) << " ";
	else cout << "   ";
	printUnicode(3, RED);
	if ((game->playerX.bord9 >> 4) & 1) cout << " " << bitToChar(1, p1) << " ";
	else if ((game->playerO.bord9 >> 4) & 1) cout << " " << bitToChar(1, p2) << " ";
	else cout << "   ";
	printUnicode(3, RED);
	if ((game->playerX.bord9 >> 3) & 1) cout << " " << bitToChar(1, p1) << " ";
	else if ((game->playerO.bord9 >> 3) & 1) cout << " " << bitToChar(1, p2) << " ";
	else cout << "   ";
	printUnicode(3, BLUE); ENTER;
	printUnicode(3, BLUE);
	printUnicode(15, RED);
	printUnicode(3, BLUE);
	printUnicode(15, RED);
	printUnicode(3, BLUE);
	printUnicode(15, RED);
	printUnicode(3, BLUE);
	ENTER;
	printUnicode(3, BLUE);
	if ((game->playerX.bord7 >> 2) & 1) cout << " " << bitToChar(1, p1) << " ";
	else if ((game->playerO.bord7 >> 2) & 1) cout << " " << bitToChar(1, p2) << " ";
	else cout << "   ";
	printUnicode(3, RED);
	if ((game->playerX.bord7 >> 1) & 1) cout << " " << bitToChar(1, p1) << " ";
	else if ((game->playerO.bord7 >> 1) & 1) cout << " " << bitToChar(1, p2) << " ";
	else cout << "   ";
	printUnicode(3, RED);
	if (game->playerX.bord7 & 1) cout << " " << bitToChar(1, p1) << " ";
	else if (game->playerO.bord7 & 1) cout << " " << bitToChar(1, p2) << " ";
	else cout << "   ";
	printUnicode(3, BLUE);
	if ((game->playerX.bord8 >> 2) & 1) cout << " " << bitToChar(1, p1) << " ";
	else if ((game->playerO.bord8 >> 2) & 1) cout << " " << bitToChar(1, p2) << " ";
	else cout << "   ";
	printUnicode(3, RED);
	if ((game->playerX.bord8 >> 1) & 1) cout << " " << bitToChar(1, p1) << " ";
	else if ((game->playerO.bord8 >> 1) & 1) cout << " " << bitToChar(1, p2) << " ";
	else cout << "   ";
	printUnicode(3, RED);
	if (game->playerX.bord8 & 1) cout << " " << bitToChar(1, p1) << " ";
	else if (game->playerO.bord8 & 1) cout << " " << bitToChar(1, p2) << " ";
	else cout << "   ";
	printUnicode(3, BLUE);
	if ((game->playerX.bord9 >> 2) & 1) cout << " " << bitToChar(1, p1) << " ";
	else if ((game->playerO.bord9 >> 2) & 1) cout << " " << bitToChar(1, p2) << " ";
	else cout << "   ";
	printUnicode(3, RED);
	if ((game->playerX.bord9 >> 1) & 1) cout << " " << bitToChar(1, p1) << " ";
	else if ((game->playerO.bord9 >> 1) & 1) cout << " " << bitToChar(1, p2) << " ";
	else cout << "   ";
	printUnicode(3, RED);
	if (game->playerX.bord9 & 1) cout << " " << bitToChar(1, p1) << " ";
	else if (game->playerO.bord9 & 1) cout << " " << bitToChar(1, p2) << " ";
	else cout << "   ";
	printUnicode(3, BLUE); ENTER;
	printUnicode(57, BLUE); ENTER;
	if (drawSuperGame) {
		cout << endl;
		printOverlayedSubBoard(game->playerX.superBord, game->playerO.superBord, 'X', 'O');
	}
}

void printMoveList(MOVELIST* moveList) {
	if (moveList->count == 0) {
		cout << "no moves found!" << endl;
		return;
	}
	for (int i = 0; i < moveList->count; i++) {
		cout << i << ") plays a: " << symbolToString((moveList->moves[i]).s) << " at: " << squareToString((moveList->moves[i]).dst) << endl;
	}
}

void printMove(Move* move) {
	cout << "a: " << symbolToString(move->s) << " at : " << squareToString(move->dst) << endl;;
}