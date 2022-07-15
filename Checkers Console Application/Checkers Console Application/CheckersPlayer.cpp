#include "CheckersPlayer.h"

CheckersPlayer::CheckersPlayer()
{
	playerColor = ' ';
	upDirection = 0;
	gameBoard = nullptr;
	name = "";
}

CheckersPlayer::CheckersPlayer(char _playerColor, int direction, CheckersBoard* board, string _name)
{
	playerColor = _playerColor;
	upDirection = direction;
	gameBoard = board;
	name = _name;
}

void CheckersPlayer::SetPieces(int start, int end) //heap vs stack. Heap is seperate part of memory where you use new and delete. Stack is memory that is push and pop. call by value creates copy on stack where values only exist when called. Pointer (by-value) stores data in the heap.Memory leak means pointer went away but pointer didn't get deleted from heap.
{
	for (int i = start; i <= end; i++) {
		  BoardSquare targetSquare = gameBoard->boardSquares[i]; //doesn't need to be pointer because we are copying an object that already exists in an array.
		  CheckersPiece* newPlayerPiece = new CheckersPiece(targetSquare,playerColor); //we use new to create a normal checkerspiece object but it stays allocated on the heap until delete is used.
		  targetSquare.SetOccupiedPiece(newPlayerPiece);
	}
}



