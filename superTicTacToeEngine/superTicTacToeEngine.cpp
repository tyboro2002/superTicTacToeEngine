// superTicTacToeEngine.cpp : Defines the entry point for the application.
//

#include "superTicTacToeEngine.h"
#include "game.h"
#include "engine.h"
#include "OLCPixelGameEngineGame.h"

#define UI 1 // define if the nice UI is used 1 uses it 0 doesnt

using namespace std;

int main(){
#if UI
	SuperTicTacToeGame demo;
	if (demo.Construct(80, 75, 10, 10, true))
		demo.Start();

	return 0;
#else
	//printSubBoard(0b001010100, 'X');
	//printOverlayedSubBoard(0b111000000, 0b000000111, 'X', 'O');
	/*
	Game game;
	//std::string SPTTT = "-O--O--O-----X--------X--------------O--O--O-----------------------------O--O--OX X A"; // game already won
	std::string SPTTT = "----O--O-----X--------X--------------O--O--O-----------------------------O--O--OX X A";
	readInSPTTTString(&game, &SPTTT, false);
	cout << SPTTT << endl;
	cout << writeOutSPTTTstring(&game) << endl;
	*/
	/*
	cout << "Size of a player: " << sizeof(Player) << endl;
	cout << "size of a game: " << sizeof(Game) << endl;
	cout << "size of a move: " << sizeof(Move) << endl;
	cout << "size of a square: " << sizeof(Square) << endl;
	cout << "size of a superSquare: " << sizeof(SuperSquare) << endl;
	cout << "size of a symbol: " << sizeof(Symbol) << endl;
	*/
	
	Game game;
	//std::string SPTTT = "----O--O-----X--------X--------------O--O--O-----------------------------O--O--OX O -";
	//readInSPTTTString(&game, &SPTTT, false);
	MOVELIST moveList;
	Move move;
	int numberOfMove = 0;
	if (game.playerToPlay != X) numberOfMove++;
	int moveIndex;
	int inputMethod;
	std::string moveString;
	cout << "how do you want moves to be inputed?" << endl;
	cout << "0) output move list and input number of move" << endl;
	cout << "1) output move list and input move as (ex. A5)" << endl;
	cout << "2) only input move as (ex. A5)" << endl;
	cin >> inputMethod;
	while (!(gameWon(&game, X) || gameWon(&game, O)) && checkSquaresOver(&game) && checkMovesOver(&game)) {
		moveList.count = 0;
		printBoard(&game, true);
		//Move result = minimaxRoot(&game, 1, true);
		//printMove(&result);
		genLegalMoves(&game, &moveList);
		if(inputMethod == 0 ||inputMethod == 1) printMoveList(&moveList);
		cout << "what move do you want to play" << endl;
		if (inputMethod == 0) {
			cin >> moveIndex;
			makeMove(&game, &moveList.moves[moveIndex]);
		}
		else if (inputMethod == 1 || inputMethod == 2) {
			cin >> moveString;
			move.dst = stringToSquare(moveString);
			move.s = (Symbol)(numberOfMove%2);
			printMove(&move);
			bool moveInList = false;
			for (int i = 0; i < moveList.count; i++) {
				if (moveList.moves[i] == move) moveInList = true;
			}
			if (!moveInList) numberOfMove--;
			if (moveInList) makeMove(&game, &move);
		}
		numberOfMove++; //swap player (only for the input nothing changes at the game object)
	}
	if (gameWon(&game, X)) cout << "X won the game" << endl;
	else if (gameWon(&game, O)) cout << "O won the game" << endl;
	else cout << "game drawn" << endl;
	printBoard(&game, true);
	return 0;
#endif
}
