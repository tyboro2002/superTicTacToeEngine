#include "engine.h"
#define endScore 100

Move minimaxRoot(Game* game, int depth, bool isMaximizer) {
	MOVELIST moveList;
	Move bestMove;
	moveList.count = 0;
	genLegalMoves(game, &moveList);
	bestMove = moveList.moves[0];
	double maxEval = -INFINITY;
	for (int i = 0; i < moveList.count; i++) {
		Game gameCopy;
		copyGame(game, &gameCopy);
		makeMove(&gameCopy, &moveList.moves[i]);
		double eval = minimax(&gameCopy, depth - 1, !isMaximizer);
		if (eval > maxEval) {
			maxEval = eval;
			bestMove = moveList.moves[i];
		}
	}
	return bestMove;
}

double minimax(Game* game, int depth, bool isMaximizer) {
	if (gameWon(game, X)) {
		return -endScore + depth; //TODO check if works for both players
	}
	if (gameWon(game, O)) {
		return endScore - depth; //TODO check if works for both players
	}
	if (depth == 0) {
		return 0; //TODO make evaluation function
	}
	MOVELIST moveList;
	moveList.count = 0;
	genLegalMoves(game, &moveList);
	if (isMaximizer) {
		double maxEval = -INFINITY;
		for (int i = 0; i < moveList.count; i++) {
			Game gameCopy;
			copyGame(game, &gameCopy);
			makeMove(&gameCopy, &moveList.moves[i]);
			double eval = minimax(&gameCopy, depth - 1, !isMaximizer);
			if (eval > maxEval) {
				maxEval = eval;
			}
		}
		return maxEval;
	}
	else {
		double minEval = INFINITY;
		for (int i = 0; i < moveList.count; i++) {
			Game gameCopy;
			copyGame(game, &gameCopy);
			makeMove(&gameCopy, &moveList.moves[i]);
			double eval = minimax(&gameCopy, depth - 1, !isMaximizer);
			if (eval < minEval) {
				minEval = eval;
			}
		}
		return minEval;
	}
}