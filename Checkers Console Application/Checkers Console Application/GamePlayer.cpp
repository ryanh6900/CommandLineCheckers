#include "GamePlayer.h"

void GamePlayer::SetPieces(int start, int end)
{
}

int GamePlayer::GetPieceCount() {
	pieceCount = 0;
	for (int i = 0; i < 32; i++) {
		if (toupper(gameBoard->boardSquares[i].GetOccupiedPiece()->GetPieceColor()) == toupper(playerColor))
			pieceCount++;
	}
	return pieceCount;
}

string GamePlayer::GetName()
{
	return name;
}
