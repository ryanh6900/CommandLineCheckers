#pragma once
#include <vector>
#include <iostream>
#include "GamePiece.h"
using namespace std;
class BoardSquare
{
private:
	GamePiece* occupiedPiece = nullptr;
	int rowNum, columnNum;
	int boardIndex; //might not be needed
	string squareColor;
public:
	BoardSquare();
	BoardSquare(int row, int col, int boardIndex, string squareColor);
	~BoardSquare();
	GamePiece* GetOccupiedPiece();
	string GetSquareColor();
	void SetOccupiedPiece(GamePiece* piece);
	bool isEmpty();
	int GetRowNumber();
	int GetColumnNumber();
	
};

//class PlayTile {
//private:
//    int rowNum, columnNum;
//    bool isOccupied, isKing;
//    char occupiedPieceColor = ' ';
//
//public:
//    vector<PlayTile*> moveTiles; //These are tiles that one diagonal away.
//    vector<pair<PlayTile*, PlayTile*>> jumpTiles; //These are tiles that are exactly two diagonals away. This pair structure I talked about briefly in the interview.
//
//    PlayTile() {
//        rowNum = -1;
//        columnNum = -1;
//        isOccupied = false;
//        isKing = false;
//    }
//
//    PlayTile(int _row, int _column, bool _isOccupied, bool _isKing) {
//        rowNum = _row;
//        columnNum = _column;
//        isOccupied = _isOccupied;
//        isKing = _isKing;
//    }
//
//    void SetOccupied(bool _isOccupied, char _occupiedPieceColor = ' ', bool _isKing = false) {
//        isOccupied = _isOccupied;
//        occupiedPieceColor = _occupiedPieceColor;
//        isKing = _isKing;
//    }
//
//    void AddAdjacent(PlayTile* adjacentPlayTile) {
//        if (adjacentPlayTile) moveTiles.push_back(adjacentPlayTile);
//    }
//
//    void AddJumpPair(PlayTile* adjTile, PlayTile* jumpTo) {
//        if (adjTile && jumpTo) jumpTiles.emplace_back(adjTile, jumpTo);
//    }
//
//    void Draw() {
//        if (isKing && isOccupied) occupiedPieceColor = toupper(occupiedPieceColor);
//        cout << " (" << occupiedPieceColor << ") ";
//    }
//
//    int GetRowNumber() {
//        return rowNum;
//    }
//    int GetColumnNumber() {
//        return columnNum;
//    }
//    char GetOccupiedColor() {
//        return occupiedPieceColor;
//    }
//    bool GetOccupance() {
//        return isOccupied;
//    }
//    bool GetPower() {
//        return isKing;
//    }
//};

