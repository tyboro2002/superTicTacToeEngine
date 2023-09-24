#define OLC_PGE_APPLICATION
#include "olcPixelGameEngine.h"
#include <vector>

#define SYMBOL_SIZE 2

enum SymbolOpt {
	XOpt=0,
	OOpt,
	_
};

class SuperTicTacToeGame : public olc::PixelGameEngine{
	std::vector<olc::vi2d> gridPointsA;
	std::vector<olc::vi2d> gridPointsB;
	std::vector<olc::vi2d> gridPointsC;

	std::vector<olc::vi2d> gridPointsD;
	std::vector<olc::vi2d> gridPointsE;
	std::vector<olc::vi2d> gridPointsF;

	std::vector<olc::vi2d> gridPointsG;
	std::vector<olc::vi2d> gridPointsH;
	std::vector<olc::vi2d> gridPointsI;

	std::vector<olc::vi2d> gridPointsSuper;

	std::vector<std::vector<olc::vi2d>> gridPositions;

	int lastSubSquare = -1;

	bool gameWon = false;

	SymbolOpt PlayingPlayer = XOpt;
	SymbolOpt gameState[10][9];
public:
	SuperTicTacToeGame(){
		sAppName = "SuperTicTacToeGame";
		for (int i = 0; i < 10; ++i) {
			for (int j = 0; j < 9; ++j) {
				gameState[i][j] = SymbolOpt::_;
			}
		}
	}

public:
	bool OnUserCreate() override{
		// Called once at the start, so create things here
		drawGrids(18,18);
		// update the gridpositions
		gridPositions.clear();
		gridPositions.push_back(gridPointsA);
		gridPositions.push_back(gridPointsB);
		gridPositions.push_back(gridPointsC);
		gridPositions.push_back(gridPointsD);
		gridPositions.push_back(gridPointsE);
		gridPositions.push_back(gridPointsF);
		gridPositions.push_back(gridPointsG);
		gridPositions.push_back(gridPointsH);
		gridPositions.push_back(gridPointsI);
		//gridPositions.push_back(gridPointsSuper);
		return true;
	}

	bool OnUserUpdate(float fElapsedTime) override{
		int mouseX = GetMouseX();
		int mouseY = GetMouseY();
		olc::vi2d closestPoint;
		float closestDistance = std::numeric_limits<float>::max(); // Initialize to a large value

		// Check if the left mouse button is pressed
		if (GetMouse(olc::Mouse::LEFT).bPressed) {
			// Left mouse button is pressed
			// Do something when the left mouse button is clicked
			// Find the closest point using range-based for loops
			olc::vi2d targetPosition = olc::vi2d(mouseX, mouseY);
			for (int rowIndex = 0; rowIndex < gridPositions.size(); ++rowIndex) {
				const auto& row = gridPositions[rowIndex];
				for (int pointIndex = 0; pointIndex < row.size(); ++pointIndex) {
					const olc::vi2d& point = row[pointIndex];
					float distance = calculateDistance(targetPosition, point);
					if (distance < closestDistance) {
						closestDistance = distance;
						closestPoint = olc::vi2d(rowIndex, pointIndex);
					}
				}
			}
			// Print the closest point
			std::cout << "Closest Point: (" << closestPoint.x << ", " << closestPoint.y << ")" << std::endl;
			if (closestPoint.x != 9 && gameState[closestPoint.x][closestPoint.y] == _ && gameState[9][closestPoint.x] == _ && gameWon == false) {
				// Use std::find to check if the targetPoint is in the vector
				std::vector<olc::vi2d> points = getPosibleMoves();
				auto it = std::find(points.begin(), points.end(), closestPoint);
				if (it != points.end()) {
					placeSymbol(closestPoint.x, closestPoint.y, PlayingPlayer);
					swapPlayingPlayer();
					fillSuperGame();
					lastSubSquare = closestPoint.y;
					drawPosibleMoves();
					drawGrids(18, 18);
					checkGameOver();
				}
			}
		}
		return true;
	}

	void placeSymbol(int square, int subSquare, SymbolOpt symbool) {
		gameState[square][subSquare] = symbool;
	}
private:
	std::vector<olc::vi2d> drawGrid(int upperLeftX, int upperLeftY, int height, int width) {
		std::vector<olc::vi2d> gridPoints;

		for (int j = 0; j < 3; ++j) {
			for (int i = 0; i < 3; ++i) {
				int startX = upperLeftX + (width / 3) * i;
				int startY = upperLeftY + (height / 3) * j;

				int endX = startX + width / 3;
				int endY = startY + height / 3;

				// Draw the lines to form the grid
				DrawLine(startX, startY, startX, endY); // left line
				DrawLine(startX, startY, endX, startY); // top line
				DrawLine(endX, startY, endX, endY); // right line
				DrawLine(startX, endY, endX, endY); // bottom line

				// Calculate and store the center point
				int centerX = (startX + endX) / 2;
				int centerY = (startY + endY) / 2;
				gridPoints.push_back({ centerX, centerY });
			}
		}

		return gridPoints;
	}

	void drawGrids(int oneGridWidth, int oneGridHeight ) {
		gridPointsA = drawGrid(0, 2, oneGridWidth, oneGridHeight); // grid A
		gridPointsB = drawGrid(0+oneGridWidth, 2, oneGridWidth, oneGridHeight); // grid B
		gridPointsC = drawGrid(0+oneGridWidth*2, 2, oneGridWidth, oneGridHeight); // grid C

		gridPointsD = drawGrid(0, 2+oneGridHeight, oneGridWidth, oneGridHeight); // grid D
		gridPointsE = drawGrid(0 + oneGridWidth, 2 + oneGridHeight, oneGridWidth, oneGridHeight); // grid E
		gridPointsF = drawGrid(0 + oneGridWidth * 2, 2 + oneGridHeight, oneGridWidth, oneGridHeight); // grid F

		gridPointsG = drawGrid(0, 2 + oneGridHeight*2, oneGridWidth, oneGridHeight); // grid G
		gridPointsH = drawGrid(0 + oneGridWidth, 2 + oneGridHeight*2, oneGridWidth, oneGridHeight); // grid H
		gridPointsI = drawGrid(0 + oneGridWidth * 2, 2 + oneGridHeight * 2, oneGridWidth, oneGridHeight); // grid I
		
		gridPointsSuper = drawGrid(0 + oneGridWidth * 4, 2 + oneGridHeight, oneGridWidth, oneGridHeight); // grid super
		// Loop through the grid points and draw the correct symbol
		for (int i = 0; i < gridPointsA.size(); i++) {
			const olc::vi2d& center = gridPointsA[i];
			if (gameState[0][i] == XOpt) DrawCrossCenterd(center.x, center.y,SYMBOL_SIZE , olc::BLUE);
			else if (gameState[0][i] == OOpt) DrawCircleCenterd(center.x, center.y, SYMBOL_SIZE, olc::GREEN);
		}
		for (int i = 0; i < gridPointsB.size(); i++) {
			const olc::vi2d& center = gridPointsB[i];
			if (gameState[1][i] == XOpt) DrawCrossCenterd(center.x, center.y, SYMBOL_SIZE, olc::BLUE);
			else if (gameState[1][i] == OOpt) DrawCircleCenterd(center.x, center.y, SYMBOL_SIZE, olc::GREEN);
		}
		for (int i = 0; i < gridPointsC.size(); i++) {
			const olc::vi2d& center = gridPointsC[i];
			if (gameState[2][i] == XOpt) DrawCrossCenterd(center.x, center.y, SYMBOL_SIZE, olc::BLUE);
			else if (gameState[2][i] == OOpt) DrawCircleCenterd(center.x, center.y, SYMBOL_SIZE, olc::GREEN);
		}

		for (int i = 0; i < gridPointsD.size(); i++) {
			const olc::vi2d& center = gridPointsD[i];
			if (gameState[3][i] == XOpt) DrawCrossCenterd(center.x, center.y, SYMBOL_SIZE, olc::BLUE);
			else if (gameState[3][i] == OOpt) DrawCircleCenterd(center.x, center.y, SYMBOL_SIZE, olc::GREEN);
		}
		for (int i = 0; i < gridPointsE.size(); i++) {
			const olc::vi2d& center = gridPointsE[i];
			if (gameState[4][i] == XOpt) DrawCrossCenterd(center.x, center.y, SYMBOL_SIZE, olc::BLUE);
			else if (gameState[4][i] == OOpt) DrawCircleCenterd(center.x, center.y, SYMBOL_SIZE, olc::GREEN);
		}
		for (int i = 0; i < gridPointsF.size(); i++) {
			const olc::vi2d& center = gridPointsF[i];
			if (gameState[5][i] == XOpt) DrawCrossCenterd(center.x, center.y, SYMBOL_SIZE, olc::BLUE);
			else if (gameState[5][i] == OOpt) DrawCircleCenterd(center.x, center.y, SYMBOL_SIZE, olc::GREEN);
		}

		for (int i = 0; i < gridPointsG.size(); i++) {
			const olc::vi2d& center = gridPointsG[i];
			if (gameState[6][i] == XOpt) DrawCrossCenterd(center.x, center.y, SYMBOL_SIZE, olc::BLUE);
			else if (gameState[6][i] == OOpt) DrawCircleCenterd(center.x, center.y, SYMBOL_SIZE, olc::GREEN);
		}
		for (int i = 0; i < gridPointsH.size(); i++) {
			const olc::vi2d& center = gridPointsH[i];
			if (gameState[7][i] == XOpt) DrawCrossCenterd(center.x, center.y, SYMBOL_SIZE, olc::BLUE);
			else if (gameState[7][i] == OOpt) DrawCircleCenterd(center.x, center.y, SYMBOL_SIZE, olc::GREEN);
		}
		for (int i = 0; i < gridPointsI.size(); i++) {
			const olc::vi2d& center = gridPointsI[i];
			if (gameState[8][i] == XOpt) DrawCrossCenterd(center.x, center.y, SYMBOL_SIZE, olc::BLUE);
			else if (gameState[8][i] == OOpt) DrawCircleCenterd(center.x, center.y, SYMBOL_SIZE, olc::GREEN);
		}

		for (int i = 0; i < gridPointsSuper.size(); i++) {
			const olc::vi2d& center = gridPointsSuper[i];
			if (gameState[9][i] == XOpt) DrawCrossCenterd(center.x, center.y, SYMBOL_SIZE, olc::BLUE);
			else if (gameState[9][i] == OOpt) DrawCircleCenterd(center.x, center.y, SYMBOL_SIZE, olc::GREEN);
		}
	}

	void DrawCrossCenterd(int x, int y, int size, olc::Pixel color){
		// Calculate the starting and ending points for the diagonal arms
		int x1 = x - size;
		int x2 = x + size;
		int y1 = y - size;
		int y2 = y + size;

		// Draw the diagonal lines (cross arms)
		DrawLine(x1, y1, x2, y2, color);
		DrawLine(x1, y2, x2, y1, color);
	}

	void DrawCircleCenterd(int x, int y, int radius, olc::Pixel color) {
		DrawCircle(x, y, radius, color);
	}

	float calculateDistance(const olc::vi2d& point1, const olc::vi2d& point2) {
		float dx = point1.x - point2.x;
		float dy = point1.y - point2.y;

		return std::sqrt(dx * dx + dy * dy);
	}

	void swapPlayingPlayer() {
		if (PlayingPlayer == XOpt) PlayingPlayer = OOpt;
		else PlayingPlayer = XOpt;
	}

	SymbolOpt checkWonSquare(SymbolOpt gameState[9]) {
		// horizontal lines
		if (gameState[0] != _ && gameState[0] == gameState[1] && gameState[1] == gameState[2]) return gameState[0]; //top line
		if (gameState[3] != _ && gameState[3] == gameState[4] && gameState[4] == gameState[5]) return gameState[3]; // middle line
		if (gameState[6] != _ && gameState[6] == gameState[7] && gameState[7] == gameState[8]) return gameState[6]; // bottom line
		// vertical lines
		if (gameState[0] != _ && gameState[0] == gameState[3] && gameState[3] == gameState[6]) return gameState[0]; // top line
		if (gameState[1] != _ && gameState[1] == gameState[4] && gameState[4] == gameState[7]) return gameState[1]; // middle line
		if (gameState[2] != _ && gameState[2] == gameState[5] && gameState[5] == gameState[8]) return gameState[2]; // bottom line

		// diagonal lines
		if (gameState[0] != _ && gameState[0] == gameState[4] && gameState[4] == gameState[8]) return gameState[0]; // top left to right bottom line
		if (gameState[2] != _ && gameState[2] == gameState[4] && gameState[4] == gameState[6]) return gameState[2]; // top right to left bottom line
		return _;
	}

	void checkGameOver() {
		int firstIndex = -1;
		int secondIndex = -1;
		// horizontal lines
		if (gameState[9][0] != _ && gameState[9][0] == gameState[9][1] && gameState[9][1] == gameState[9][2]) { firstIndex = 0; secondIndex = 2; } //top line
		else if (gameState[9][3] != _ && gameState[9][3] == gameState[9][4] && gameState[9][4] == gameState[9][5]) { firstIndex = 3; secondIndex = 5; } // middle line
		else if (gameState[9][6] != _ && gameState[9][6] == gameState[9][7] && gameState[9][7] == gameState[9][8]) { firstIndex = 6; secondIndex = 8; } // bottom line
		// vertical lines
		else if (gameState[9][0] != _ && gameState[9][0] == gameState[9][3] && gameState[9][3] == gameState[9][6]) { firstIndex = 0; secondIndex = 6; } // top line
		else if (gameState[9][1] != _ && gameState[9][1] == gameState[9][4] && gameState[9][4] == gameState[9][7]) { firstIndex = 1; secondIndex = 7; } // middle line
		else if (gameState[9][2] != _ && gameState[9][2] == gameState[9][5] && gameState[9][5] == gameState[9][8]) { firstIndex = 2; secondIndex = 8; } // bottom line
		// diagonal lines
		else if (gameState[9][0] != _ && gameState[9][0] == gameState[9][4] && gameState[9][4] == gameState[9][8]) { firstIndex = 0; secondIndex = 8; } // top left to right bottom line
		else if (gameState[9][2] != _ && gameState[9][2] == gameState[9][4] && gameState[9][4] == gameState[9][6]) { firstIndex = 2; secondIndex = 6; } // top right to left bottom line
		if (firstIndex != -1 && secondIndex != -1) {
			DrawLine(gridPointsSuper.at(firstIndex).x, gridPointsSuper.at(firstIndex).y, gridPointsSuper.at(secondIndex).x, gridPointsSuper.at(secondIndex).y, olc::MAGENTA);
			gameWon = true;
		}
	}


	void fillSuperGame() {
		for (int i = 0; i < 9; i++) {
			placeSymbol(9, i, checkWonSquare(gameState[i]));
		}
	}

	std::vector<olc::vi2d> getPosibleMoves() {
		std::vector<olc::vi2d> posMoves;
		for (int i = 0; i < 9; i++) {
			if (lastSubSquare == i && (checkWonSquare(gameState[i]) == _)) {
				for (int j = 0; j < 9; j++) {
					if (gameState[i][j] == _) posMoves.push_back(olc::vi2d(i, j));
				}
			}
		}
		if (posMoves.size() == 0) {
			for (int i = 0; i < 9; i++) {
				if (checkWonSquare(gameState[i]) == _) {
					for (int j = 0; j < 9; j++) {
						if (gameState[i][j] == _) posMoves.push_back(olc::vi2d(i, j));
					}
				}
			}
		}
		return posMoves;
	}

	void drawGridPoint(int square, int subsquare, olc::Pixel color) {
		if (square == 0) {
			Draw(gridPointsA.at(subsquare), color);
		}else if (square == 1) {
			Draw(gridPointsB.at(subsquare), color);
		}else if (square == 2) {
			Draw(gridPointsC.at(subsquare), color);
		}else if (square == 3) {
			Draw(gridPointsD.at(subsquare), color);
		}else if (square == 4) {
			Draw(gridPointsE.at(subsquare), color);
		}else if (square == 5) {
			Draw(gridPointsF.at(subsquare), color);
		}else if (square == 6) {
			Draw(gridPointsG.at(subsquare), color);
		}else if (square == 7) {
			Draw(gridPointsH.at(subsquare), color);
		}else if (square == 8) {
			Draw(gridPointsI.at(subsquare), color);
		}

	}

	void drawPosibleMoves() {
		// reset all moves to a black square
		for (const std::vector<olc::vi2d>& row : gridPositions){
			for (const olc::vi2d& point : row) {
				Draw(point, olc::BLACK);
			}
		}

		std::vector<olc::vi2d> moves = getPosibleMoves();
		for (olc::vi2d& point : moves) {
			drawGridPoint(point.x, point.y, olc::RED);
		}
	}
};