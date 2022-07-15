#include "BoardSquare.h"

BoardSquare::BoardSquare()
{
    rowNum = -1;
    columnNum = -1;
    boardIndex = -1;
    squareColor = "";
}

BoardSquare::BoardSquare(int row, int col, int index, string sqrColor)
{
    rowNum = row;
    columnNum = col;
    boardIndex = index;
    squareColor = sqrColor;
    occupiedPiece = nullptr;
}

BoardSquare::~BoardSquare()
{
    delete occupiedPiece;
}

GamePiece* BoardSquare::GetOccupiedPiece()
{
    return occupiedPiece;
}

string BoardSquare::GetSquareColor()
{
    return squareColor;
}

void BoardSquare::SetOccupiedPiece(GamePiece* piece)
{
    occupiedPiece = piece;
}

bool BoardSquare::isEmpty()
{
   return occupiedPiece == nullptr;
}

int BoardSquare::GetRowNumber()
{
    return rowNum;
}

int BoardSquare::GetColumnNumber()
{
    return columnNum;
}


