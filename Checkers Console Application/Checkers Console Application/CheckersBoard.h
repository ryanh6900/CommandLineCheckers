#pragma once
#include "GameBoard.h"
class CheckersBoard :
    public GameBoard
{
public:
    void BoardSetup(int boardSize);
    void DrawBoard();
    void DrawSquare(int whichLine, int index);

};




