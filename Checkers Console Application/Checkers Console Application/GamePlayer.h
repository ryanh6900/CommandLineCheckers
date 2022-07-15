#pragma once
#include <string>
#include "GameBoard.h"

using namespace std;
class GamePlayer
{
private:
	
public:
	string name;
	char playerColor;
	GameBoard* gameBoard = nullptr;
	int pieceCount;
	virtual void SetPieces(int start, int end);
	int GetPieceCount();
	string GetName();
};

