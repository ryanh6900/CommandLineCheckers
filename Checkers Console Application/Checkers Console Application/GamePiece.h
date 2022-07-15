#pragma once
#include <string>
using namespace std;
class GamePiece
{
private:
	int rowNum, columnNum;

public:
	GamePiece();
	GamePiece(int row, int column);
	int GetRowNumber();
	int GetColumnNumber();
	virtual string GetPieceDesign();
	virtual char GetPieceColor();
};

