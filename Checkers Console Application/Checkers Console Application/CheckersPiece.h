#pragma once
#include "GamePiece.h"
#include "BoardSquare.h"
#include <vector>
using namespace std;
class CheckersPiece :
    public GamePiece
{
private:
    bool isKing;
    char pieceColor;
    string pieceDesign;
public:
    vector<BoardSquare*> captureSquares;
    vector<pair<BoardSquare*,BoardSquare*>> jumpCapturePieces;
    CheckersPiece();
    CheckersPiece(BoardSquare square, char playerColor); //doesnt need to be pointer, it can be just a copy of the object.
    CheckersPiece(int row, int column, bool king, char design);
    void AddAdjacent(BoardSquare* adjSquare);
    void AddJumpPair(BoardSquare* adjSquare, BoardSquare* jumpSquare);
    char GetPieceColor() override;
    string GetPieceDesign() override;
};

