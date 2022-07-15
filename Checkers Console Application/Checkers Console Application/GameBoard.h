#pragma once
#include "BoardSquare.h"
#include <vector>
using namespace std;
class GameBoard
{
public:
	BoardSquare boardSquares[64];
	//vector<BoardSquare*> boardSquares;
	virtual void BoardSetup(int boardSize);
	virtual void DrawBoard();
};

