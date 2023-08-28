// superTicTacToeEngine.cpp : Defines the entry point for the application.
//

#include "superTicTacToeEngine.h"
#include "game.h"
#include "engine.h"

using namespace std;

int main(){
	//printSubBoard(0b001010100, 'X');
	//printOverlayedSubBoard(0b111000000, 0b000000111, 'X', 'O');
	Game game;
	MOVELIST moveList;
	Move move;
	int moveIndex;
	while (!(gameWon(&game, X) || gameWon(&game, O)) && checkSquaresOver(&game) && checkMovesOver(&game)) {
		moveList.count = 0;
		printBoard(&game, true);
		//Move result = minimaxRoot(&game, 1, true);
		//printMove(&result);
		genLegalMoves(&game, &moveList);
		printMoveList(&moveList);
		cout << "what move do you want to play" << endl;
		cin >> moveIndex;
		makeMove(&game, &moveList.moves[moveIndex]);
	}
	if (gameWon(&game, X)) cout << "X won the game" << endl;
	else if (gameWon(&game, O)) cout << "O won the game" << endl;
	else cout << "game drawn" << endl;
	printBoard(&game, true);
	//cout << "Size of a player: " << sizeof(Player) << endl;
	//cout << "size of a game: " << sizeof(Game) << endl;
	return 0;
}
