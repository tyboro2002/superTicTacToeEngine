#define OLC_PGE_APPLICATION
#include "olcPixelGameEngine.h"

class SuperTicTacToeGame : public olc::PixelGameEngine
{
public:
	SuperTicTacToeGame(){
		sAppName = "SuperTicTacToeGame";
	}

public:
	bool OnUserCreate() override{
		// Called once at the start, so create things here
		for (int y = 2; y < ScreenHeight()-2; y++) {
			Draw(0, y, olc::Pixel(255,255,255));
		}
		/*
		for (int x = 0; x < ScreenWidth(); x++)
			for (int y = 0; y < ScreenHeight(); y++)
				Draw(x, y, olc::Pixel(rand() % 255, rand() % 255, rand() % 255));
		*/
		return true;
	}

	bool OnUserUpdate(float fElapsedTime) override
	{
		/*
		// called once per frame
		for (int x = 0; x < ScreenWidth(); x++)
			for (int y = 0; y < ScreenHeight(); y++)
				Draw(x, y, olc::Pixel(rand() % 255, rand() % 255, rand() % 255));
		*/
		return true;
	}
};