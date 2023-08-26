// superTicTacToeEngine.cpp : Defines the entry point for the application.
//

#include "superTicTacToeEngine.h"
#include "game.h"

using namespace std;

int main(){
	printSubBoard(0b001010100, 'X');
	printOverlayedSubBoard(0b111000000, 0b000000111, 'X', 'O');
	cout << "Size of a player: " << sizeof(Player) << endl;
	cout << "size of a game: " << sizeof(Game) << endl;
	return 0;
}
