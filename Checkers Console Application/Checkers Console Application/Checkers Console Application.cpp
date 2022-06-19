// Checkers Console Application.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>

using namespace std;
//Remember to model abstractions after real-world concepts within the game of checkers.
struct PlayTile {
    //char color;
    int rowNum, columnNum;
    bool isOccupied;
    char occupiedPieceColor = ' ';
    char emptySymbol = '+';
  
   PlayTile(){
        rowNum = -1;
        columnNum = -1;
        isOccupied = false;
    }

   PlayTile(int _row, int _column,bool _isOccupied) {
       //color = _color;
       rowNum = _row;
       columnNum = _column;
       isOccupied = _isOccupied;
    }

   void SetOccupied(bool _isOccupied, char occupiedPiece) {
       isOccupied = _isOccupied;
       occupiedPieceColor = occupiedPiece;
   }

    void DrawTile() {
        if (isOccupied) cout << " " << occupiedPieceColor << " ";
        else cout << " " << emptySymbol << " ";
    }
   /* void DrawEmpty() {
        cout << emptySymbol;
    }*/
   /* int GetRowNumber() {
        return row;
    }
    int GetColumnNumber() {
        return column;
    }*/
    
    /*char GetColor() {
        return color;
    }*/
};

struct Board { 
    PlayTile playableTiles[32];

    void SetupBoardPlaytiles(int size, char playerOneColor, char playerTwoColor) { //follow the model, view, controller pattern
        PlayTile newPlayTile;
        int playtileIndex = 0;
        for (int i = 1; i <= size; i++) { //i is the row number, j is the column number
            for (int j = 1; j <= size; j++) {
                if (i % 2 == 0) {
                    if (j % 2 != 0) {
                        newPlayTile = PlayTile(i, j, false);
                        if (i <= 3) {
                            newPlayTile.SetOccupied(true,playerTwoColor);
                        }
                        else if (i >= 6) {
                            newPlayTile.SetOccupied(true, playerOneColor);
                        }
                        playableTiles[playtileIndex] = newPlayTile;
                        playtileIndex++;
                    }
                }
                else {
                    if (j % 2 == 0) {
                        newPlayTile = PlayTile(i, j, false);
                        if (i <= 3) {
                            newPlayTile.SetOccupied(true,playerTwoColor); 
                        }
                        else if (i >= 6) {
                            newPlayTile.SetOccupied(true,playerOneColor);
                        }
                        playableTiles[playtileIndex] = newPlayTile;
                        playtileIndex++;
                    }
                }
            }
        }
    }

    void DrawBoard() {
        for (int index = 0; index < 32; index++) {
            int i = playableTiles[index].rowNum;
            int j = playableTiles[index].columnNum;
            if (index % 4 == 0) cout << endl;
            if (i % 2 == 0) {
                if (j % 2 != 0) {
                    playableTiles[index].DrawTile();
                    cout << " - ";
                }
                
            }
            else {
                if (j % 2 == 0) {
                    cout << " - ";
                    playableTiles[index].DrawTile();
                }
            }
        }
        cout << endl;

        /*int playtileIndex = 0;
        for (int i = 1; i <=size; i++) {
            for (int j = 1; j <= size; j++) {
                if (i % 2 == 0) {
                    if (j % 2 != 0) {
                        if (i <= 3) {
                            playableTiles[i].DrawTile();
                            playtileIndex++;
                        }
                        else if (i >= 6) {
                            playableTiles[i].DrawTile();
                            playtileIndex++;
                        }
                        else {
                            playableTiles[i].DrawTile();
                            playtileIndex++;
                        }
                    }
                    else cout << " - ";
                }
                else {
                    if (j % 2 == 0) {
                        if (i <= 3) {
                            playableTiles[i].DrawTile();
                            playtileIndex++;
                        }
                        else if (i >= 6) {
                            playableTiles[i].DrawTile();
                            playtileIndex++;
                        }
                        else {
                            playableTiles[i].DrawTile();
                            playtileIndex++;
                        }
                    }
                    else cout << " - ";
                }
            }
            cout << endl;
        }*/
    }

    void MoveTile(int fromIndex, int toIndex) {

    }

    void DrawBoardWithoutPieces(int size) {
        for (int i = 1; i <= size; i++) {
            for (int j = 1; j <= size; j++) {
                if (i % 2 == 0) {
                    if (j % 2 != 0) cout << " + ";
                    else cout << " - ";
                }
                else {
                    if (j % 2 == 0) cout << " + ";
                    else cout << " - ";
                }
            }
            cout << endl;
        }
        cout << endl;
    }
    /*void DrawBoard(int size, char playerOneColor, char playerTwoColor) {
        PlayTile newPlayTile;
        for (int i = 0; i < size; i++) {
            for (int j = 0; j < size; j++) {
                if (i % 2 == 0) {
                    if (j % 2 != 0) {
                        newPlayTile = PlayTile(i, j, false);
                        if (i < 3) {
                            newPlayTile.SetOccupied(true);
                            newPlayTile.DrawTile(playerOneColor);
                        }
                        else if (i > 4) {
                            newPlayTile.SetOccupied(true);
                            newPlayTile.DrawTile(playerTwoColor);
                        }
                        else newPlayTile.DrawEmpty();
                    }
                    else cout << " - ";
                }
                else {
                    if (j % 2 == 0) {
                        if (i < 3) {
                            newPlayTile.SetOccupied(true);
                            newPlayTile.DrawTile(playerOneColor);
                        }
                        else if (i > 4) {
                            newPlayTile.SetOccupied(true);
                            newPlayTile.DrawTile(playerTwoColor);
                        }
                        else newPlayTile.DrawEmpty();
                    }
                    else cout << " - ";
                }
            }
            cout << endl;
        }
    }*/
};

struct Player {
    char playerColor;
    //vector<Piece> pieces;
    //void SetupPieces(char color, bool isPlayerOne){/*, int boardSize, int rowsOfPieces, bool isPlayerOne) {*/
    //    playerColor = color;
    //        for (int i = 0; i < 8; i++) {
    //            for (int j = 0; j < 3; j++) {
    //                if (i % 2 == 0) {
    //                    if (j % 2 != 0) {
    //                        Piece newPiece = isPlayerOne ? Piece(color, i+5, j, false) : Piece(color, i, j,false);
    //                        pieces.push_back(newPiece);
    //                    }
    //                }
    //                else {
    //                    if (j % 2 == 0) {
    //                        Piece newPiece = isPlayerOne ? Piece(color, i+5, j, false) : Piece(color,i,j, false);
    //                        pieces.push_back(newPiece);
    //                    }
    //                }
    //            }
    //        }
    //}
};

int main()
{
    cout << "Welcome to the Game of Checkers!" << "\n";
    int boardSize = 8;
    char playerOneColor = 'r';
    char PlayerTwoColor = 'b';
    Board gameBoard;
    //gameBoard.DrawBoardWithoutPieces(8);
    gameBoard.SetupBoardPlaytiles(8, playerOneColor, PlayerTwoColor);
    gameBoard.DrawBoard();
    return 0;
}

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
