// Checkers Console Application.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <vector>
using namespace std;
//Remember to model abstractions after real-world concepts within the game of checkers.
class PlayTile; //forward reference for PlayTile

class Player {
public:
    char playerColor;
    Board gameBoard;
    vector<PlayTile*> movablePieces;
    Player() {
        playerColor = ' ';
    }
    Player(char _playerColor) {
        playerColor = _playerColor;
    }

    void SetBoard(Board board) {
        gameBoard = board;
    }
    void SetPieces() {

    }
    void FindMove() {
       //loops through all playtiles in possession.
    }
    

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

class PlayTile {
    
public:
    Player* possessingPlayer = nullptr;
    int rowNum, columnNum;
    bool isOccupied,isKing;
    char occupiedPieceColor = ' ';
    char emptySymbol = '+';

    vector<PlayTile*> adjacentPlayTiles;

   PlayTile(){
        rowNum = -1;
        columnNum = -1;
        isOccupied = false;
        isKing = false;
    }

   PlayTile(int _row, int _column,bool _isOccupied, bool _isKing) {
       rowNum = _row;
       columnNum = _column;
       isOccupied = _isOccupied;
       isKing = _isKing;
    }

   void SetOccupied(bool _isOccupied, Player* _possessingPlayer) {
       isOccupied = _isOccupied;
       possessingPlayer = _possessingPlayer;
       occupiedPieceColor = _possessingPlayer->playerColor;
   }

   void AddAdjacentTile(PlayTile* adjacentPlayTile) {
       adjacentPlayTiles.push_back(adjacentPlayTile);
   }

    void DrawTile() {
        if (isOccupied) {
            if (isKing) occupiedPieceColor = toupper(occupiedPieceColor);
            cout << " " << occupiedPieceColor << " ";
        }
        else cout << " " << emptySymbol << " ";
    }
    
    int GetRowNumber() {
        return rowNum;
    }
    int GetColumnNumber() {
        return columnNum;
    }
    
    char GetColor() {
        return occupiedPieceColor;
    }
};

class Board { 
    PlayTile playableTiles[32]; //taking advantage of the fact that arrays are static.
public:
    void SetupBoardPlaytiles(int size, Player playerOne, Player playerTwo) { //follow the model, view, controller pattern
        PlayTile newPlayTile;
        int playtileIndex = 0;
        for (int i = 1; i <= size; i++) { //i is the row number, j is the column number
            for (int j = 1; j <= size; j++) {
                if (i % 2 == 0) {
                    if (j % 2 != 0) {
                        newPlayTile = PlayTile(i, j, false,false);
                        if (i <= 3) {
                            newPlayTile.SetOccupied(true,&playerTwo);
                        }
                        else if (i >= 6) {
                            newPlayTile.SetOccupied(true, &playerOne);
                        }
                        playableTiles[playtileIndex] = newPlayTile;
                        playtileIndex++;
                    }
                }
                else {
                    if (j % 2 == 0) {
                        newPlayTile = PlayTile(i, j, false,false);
                        if (i <= 3) {
                            newPlayTile.SetOccupied(true,&playerTwo); 
                        }
                        else if (i >= 6) {
                            newPlayTile.SetOccupied(true,&playerOne);
                        }
                        playableTiles[playtileIndex] = newPlayTile;
                        playtileIndex++;
                    }
                }
            }
        }
    }

    void FindAdjacentPlayTiles(int row, int column) {
        //playableTiles[index]
        for (int i = row - 1; i <= row + 1; i++) {
            for (int j = column - 1; j <= column + 1; j++) {
                
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

        
    }

    void MovePiece(int fromIndex, int toIndex) {
        PlayTile* fromTile = &playableTiles[fromIndex]; //pointing to our playtile at index. If this variable changes our array at index changes.
        PlayTile* toTile = &playableTiles[toIndex];

        if (!toTile->isOccupied && fromTile->isOccupied) {
          toTile->SetOccupied(fromTile->isOccupied, fromTile->possessingPlayer);
          fromTile->SetOccupied(false,nullptr);
        }
    }

    void DrawBoardWithoutPieces(int size) {
        int counter = 1;
        for (int i = 1; i <= size; i++) {
            for (int j = 1; j <= size; j++) {
                if (i % 2 == 0) {
                    if (j % 2 != 0) cout << counter++ << "\t";
                    else cout << "--\t";
                }
                else {
                    if (j % 2 == 0) cout << counter++ << "\t";
                    else cout << "--\t";
                }
            }
            cout << endl << endl;
           
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


int main()
{
    cout << "Welcome to the Game of Checkers!" << "\n\n";
    int boardSize = 8;
    char playerOneColor;
    char playerTwoColor;
    Board gameBoard;
    Player playerOne, playerTwo;
    cout << "What color is Player One?" << endl;
    cin >> playerOneColor;
    playerOne = Player(tolower(playerOneColor));
    cout << "What color is Player Two?" << endl;
    cin >> playerTwoColor;
    playerTwo = Player(tolower(playerTwoColor));



    gameBoard.DrawBoardWithoutPieces(8);
    gameBoard.SetupBoardPlaytiles(8, playerOne, playerTwo);
   
    string input;
    int from, to;
    while (true) {
        gameBoard.DrawBoard();
        cin >> from;
    
        if (from == 0) break;
        cin >> to;
        gameBoard.MovePiece(from - 1, to - 1);
    }
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
