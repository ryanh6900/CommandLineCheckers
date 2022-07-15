#include "CheckersBoard.h"
#include "CheckersPiece.h"
void CheckersBoard::BoardSetup(int size)
{
	BoardSquare newSquare;
    int index = 0;
	        for (int i = 1; i <= size; i++) { //i is the row number, j is the column number
	            for (int j = 1; j <= size; j++) {
	                if (i % 2 == 0) {
	                    if (j % 2 != 0) {
							newSquare = BoardSquare(i, j, index, "( )");
	                        boardSquares[index] = newSquare;
	                        index++;
	                    }
	                }
	                else {
	                    if (j % 2 == 0) {
							newSquare = BoardSquare(i, j, index, "( )");
							boardSquares[index] = newSquare;
							index++;
	                    }
	                }
	            }
	        }
	        //FindAdjacentPlayTiles();
}

void CheckersBoard::DrawBoard()
{
		string unusedTile = "|#######";
		int index;
		
		for (int i = 0; i < 8; i++) cout << "|-------";
		cout << "|" << endl;
		for (int row = 0; row < 8; row++) {
			for (int lineCnt = 1; lineCnt <= 3; lineCnt++) { // multiple lines drawn for each square
				for (int col = 0; col < 4; col++) {
					index = row * 4 + col;
					
					if (row % 2 == 0) {
						cout << unusedTile;
						DrawSquare(lineCnt, index);
					}
					else {
						DrawSquare(lineCnt,index);
						cout << unusedTile;
					}
				}
				cout << "|" << endl;
			}
		}
}

void CheckersBoard::DrawSquare(int whichLine, int index)
{
	int squareNum = index + 1;
	BoardSquare currSquare = boardSquares[index];
	string tempColor = currSquare.GetSquareColor();
	switch (whichLine) {
	case 1: // first line displays the tile number
		cout << "|     ";
		if (squareNum < 10) cout << " ";
		cout << squareNum;
		break;
	case 2: // second line displays the checker piece
		cout << "| ";
		if (currSquare.isEmpty()) {
			string tempSquareColor = currSquare.GetSquareColor();
			cout << tempSquareColor;
		}
		else {
			GamePiece* gamePiece = currSquare.GetOccupiedPiece();
			CheckersPiece* piece = (CheckersPiece*)gamePiece;
			string temp = piece->GetPieceDesign();
			cout << temp;
		}
		//currSquare.isEmpty() ? cout << currSquare.GetSquareColor() : cout << piece->GetPieceDesign(); // outputs exactly 5 chars
		cout << " ";
		break;
	case 3: // third line is the bottom of the square
		cout << "|-------";
	}
}


//class Board {
	//
	//public:
	//    PlayTile playableTiles[32]; //taking advantage of the fact that arrays are static.
	//
	//    void BoardSetup(int size) {
	//        PlayTile newPlayTile;
	//        int playtileIndex = 0;
	//        for (int i = 1; i <= size; i++) { //i is the row number, j is the column number
	//            for (int j = 1; j <= size; j++) {
	//                if (i % 2 == 0) {
	//                    if (j % 2 != 0) {
	//                        newPlayTile = PlayTile(i, j, false, false);
	//                        playableTiles[playtileIndex] = newPlayTile;
	//                        playtileIndex++;
	//                    }
	//                }
	//                else {
	//                    if (j % 2 == 0) {
	//                        newPlayTile = PlayTile(i, j, false, false);
	//                        playableTiles[playtileIndex] = newPlayTile;
	//                        playtileIndex++;
	//                    }
	//                }
	//            }
	//        }
	//        FindAdjacentPlayTiles();
	//    }
	//
	//    void DrawFormattedTile(int whichLine, int index) {
	//        int tileNum = index + 1;
	//        switch (whichLine) {
	//        case 1: // first line displays the tile number
	//            cout << "|     ";
	//            if (tileNum < 10) cout << " ";
	//            cout << tileNum;
	//            break;
	//        case 2: // second line displays the checker piece
	//            cout << "| ";
	//            playableTiles[index].Draw(); // outputs exactly 5 chars
	//            cout << " ";
	//            break;
	//        case 3: // third line is the bottom of the square
	//            cout << "|-------";
	//        }
	//    }
	    //void DrawFormattedBoard() {
	    //    string unusedTile = "|#######";
	    //    int index;
	    //    for (int i = 0; i < 8; i++) cout << "|-------";
	    //    cout << "|" << endl;
	    //    for (int row = 0; row < 8; row++) {
	    //        for (int lineCnt = 1; lineCnt <= 3; lineCnt++) { // multiple lines drawn for each tile
	    //            for (int col = 0; col < 4; col++) {
	    //                index = row * 4 + col;
	    //                if (row % 2 == 0) {
	    //                    cout << unusedTile;
	    //                    DrawFormattedTile(lineCnt, index);
	    //                }
	    //                else {
	    //                    DrawFormattedTile(lineCnt, index);
	    //                    cout << unusedTile;
	    //                }
	    //            }
	    //            cout << "|" << endl;
	    //        }
	    //    }
	    //}
	//
	//    void DrawBoard() {
	//        int counter = 1;
	//        for (int index = 0; index < 32; index++) {
	//            int i = playableTiles[index].GetRowNumber();
	//            int j = playableTiles[index].GetColumnNumber();
	//
	//            if (index % 4 == 0 && index > 0) cout << endl << endl;
	//
	//            if (i % 2 == 0) {
	//                if (j % 2 != 0) {
	//                    playableTiles[index].Draw();
	//                    cout << counter++;
	//                    cout << "\t ----\t";
	//                }
	//            }
	//            else {
	//                if (j % 2 == 0) {
	//                    cout << " ----\t";
	//                    playableTiles[index].Draw();
	//                    cout << counter++;
	//                    cout << "\t";
	//                }
	//            }
	//        }
	//        cout << endl;
	//    }
	//
	//    void DrawBoardWithoutPieces(int size) {
	//        int counter = 1;
	//        for (int i = 1; i <= size; i++) {
	//            for (int j = 1; j <= size; j++) {
	//                if (i % 2 == 0) {
	//                    if (j % 2 != 0) cout << counter++ << "\t";
	//                    else cout << "--\t";
	//                }
	//                else {
	//                    if (j % 2 == 0) cout << counter++ << "\t";
	//                    else cout << "--\t";
	//                }
	//            }
	//            cout << endl << endl;
	//
	//        }
	//        cout << endl;
	//    }
	//
	//    void FindAdjacentPlayTiles() {
	//        //playableTiles[index]
	//        PlayTile* currTile;
	//        PlayTile* adjTile;
	//        for (int i = 0; i < 32; i++) {
	//            currTile = &playableTiles[i];
	//            int row = currTile->GetRowNumber();
	//            int column = currTile->GetColumnNumber();
	//            currTile->AddAdjacent(GetPlayTile(row - 1, column - 1)); //diagonal up to left
	//            currTile->AddAdjacent(GetPlayTile(row - 1, column + 1)); //diagonal up to right
	//            currTile->AddAdjacent(GetPlayTile(row + 1, column - 1)); //diagonal down to left
	//            currTile->AddAdjacent(GetPlayTile(row + 1, column + 1)); //diagonal down to right
	//
	//            currTile->AddJumpPair(GetPlayTile(row - 1, column - 1), GetPlayTile(row - 2, column - 2));
	//            currTile->AddJumpPair(GetPlayTile(row - 1, column + 1), GetPlayTile(row - 2, column + 2));
	//            currTile->AddJumpPair(GetPlayTile(row + 1, column - 1), GetPlayTile(row + 2, column - 2));
	//            currTile->AddJumpPair(GetPlayTile(row + 1, column + 1), GetPlayTile(row + 2, column + 2));
	//        }
	//    }
	//
	//    PlayTile* GetPlayTile(int i, int j) { //very powerful function
	//        for (int index = 0; index < 32; index++) {
	//            if (i == playableTiles[index].GetRowNumber() &&
	//                j == playableTiles[index].GetColumnNumber()) return &playableTiles[index];
	//        }
	//        return nullptr;
	//    }
	//
	//    PlayTile* GetPlayTile(int playTileIndex) {
	//        return &playableTiles[playTileIndex];
	//    }
	//    PlayTile* GetPlayTile(string verifiedTileNumber) {
	//        int index = stoi(verifiedTileNumber) - 1;
	//        return GetPlayTile(index);
	//    }
	//    int GetPlayTileNumber(PlayTile* playTile) {
	//        int i = playTile->GetRowNumber();
	//        int j = playTile->GetColumnNumber();
	//        for (int index = 0; index < 32; index++) {
	//            if (i == playableTiles[index].GetRowNumber() &&
	//                j == playableTiles[index].GetColumnNumber()) return index + 1;
	//        }
	//        return 0;
	//    }
	//    
	//};