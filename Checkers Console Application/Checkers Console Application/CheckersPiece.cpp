#include "CheckersPiece.h"

CheckersPiece::CheckersPiece(BoardSquare square, char playerColor)
{
	CheckersPiece(square.GetRowNumber(), square.GetColumnNumber(), false, playerColor);
}

CheckersPiece::CheckersPiece(int row, int column, bool king, char color)
{
	GamePiece(row, column);
	isKing = king;
	pieceColor = color;
}

char CheckersPiece::GetPieceColor()
{
	return pieceColor;
}

string CheckersPiece::GetPieceDesign() {
	if(pieceColor) return "  " + to_string(pieceColor) + "  ";
	return " ";
}
