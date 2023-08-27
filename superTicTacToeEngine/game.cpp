#include <bitset>
#include "game.h"
using namespace std;

int countSetBits(subBoard sub) {
	int count = 0;
	while (sub) {
		count += sub & 1;
		sub >>= 1;
	}
	return count;
}

char bitToChar(bool b, char c) {
	if (b) return c;
	else return ' ';
}

void fillSuperBoard(Player* player) {
	subBoard row1 = 0b111000000;
	subBoard row2 = 0b000111000;
	subBoard row3 = 0b000000111;

	subBoard column1 = 0b100100100;
	subBoard column2 = 0b010010010;
	subBoard column3 = 0b001001001;

	subBoard diagonal1 = 0b100010001;
	subBoard diagonal2 = 0b001010100;

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