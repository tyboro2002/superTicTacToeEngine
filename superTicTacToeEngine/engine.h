// game.h : Include file for standard system include files,
// or project specific include files.

#pragma once

#include <iostream>
#include "game.h"

Move minimaxRoot(Game* game, int depth, bool isMaximizer);
double minimax(Game* game, int depth, bool isMaximizer);