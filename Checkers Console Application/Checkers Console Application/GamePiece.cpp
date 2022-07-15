#include "GamePiece.h"
using namespace std;
GamePiece::GamePiece()
{
	rowNum = -1;
	columnNum = -1;
}

GamePiece::GamePiece(int row, int column)
{
	rowNum = row;
	columnNum = column;
}

int GamePiece::GetRowNumber()
{
	return rowNum;
}

int GamePiece::GetColumnNumber()
{
	return columnNum;
}

string GamePiece::GetPieceDesign()
{
	return " ";
}

char GamePiece::GetPieceColor()
{
	return ' ';
}


