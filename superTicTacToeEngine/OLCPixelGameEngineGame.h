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

	SymbolOpt PlayingPlayer = XOpt;
	SymbolOpt gameState[10][9];
public:
	SuperTicTacToeGame(){
		sAppName = "SuperTicTacToeGame";
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
		gridPositions.push_back(gridPointsSuper);
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
			placeSymbol(closestPoint.x, closestPoint.y, PlayingPlayer);
			swapPlayingPlayer();
		}
		drawGrids(18, 18);
		return true;
	}

	bool placeSymbol(int square, int subSquare, SymbolOpt symbool) {
		if (gameState[square][subSquare] == _) return false;
		gameState[square][subSquare] = symbool;
		return true;
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
};