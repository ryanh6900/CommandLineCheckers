// Checkers Console Application.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <vector>
using namespace std;
//Remember to model abstractions after real-world concepts within the game of checkers.
class PlayTile {
private:
    int rowNum, columnNum;
    bool isOccupied, isKing;
    char occupiedPieceColor = ' ';
    char emptySymbol = '+';

public:
    vector<PlayTile*> adjacentPlayTiles;

    PlayTile() {
        rowNum = -1;
        columnNum = -1;
        isOccupied = false;
        isKing = false;
    }

    PlayTile(int _row, int _column, bool _isOccupied, bool _isKing) {
        rowNum = _row;
        columnNum = _column;
        isOccupied = _isOccupied;
        isKing = _isKing;
    }

    void SetOccupied(bool _isOccupied, char color) {
        isOccupied = _isOccupied;
        occupiedPieceColor = color;
    }

    void AddAdjacentTile(PlayTile* adjacentPlayTile) {
        if(adjacentPlayTile) adjacentPlayTiles.push_back(adjacentPlayTile);
    }

    void DrawTile() {
        if (isOccupied) {
            if (isKing) occupiedPieceColor = toupper(occupiedPieceColor);
            cout << " (" << occupiedPieceColor << ") ";
        }
        else cout << " (" << emptySymbol << ") ";
    }

    int GetRowNumber() {
        return rowNum;
    }
    int GetColumnNumber() {
        return columnNum;
    }

    char GetOccupiedColor() {
        return occupiedPieceColor;
    }
    bool GetOccupance() {
        return isOccupied;
    }
};

class Board {
    
public:
    PlayTile playableTiles[32]; //taking advantage of the fact that arrays are static.

    /*void setupboardplaytiles(int size, player playerone, player playertwo) { //follow the model, view, controller pattern
        playtile newplaytile;
        int playtileindex = 0;
        for (int i = 1; i <= size; i++) { //i is the row number, j is the column number
            for (int j = 1; j <= size; j++) {
                if (i % 2 == 0) {
                    if (j % 2 != 0) {
                        newplaytile = playtile(i, j, false,false);
                        if (i <= 3) {
                            newplaytile.setoccupied(true,&playertwo);
                        }
                        else if (i >= 6) {
                            newplaytile.setoccupied(true, &playerone);
                        }
                        playabletiles[playtileindex] = newplaytile;
                        playtileindex++;
                    }
                }
                else {
                    if (j % 2 == 0) {
                        newplaytile = playtile(i, j, false,false);
                        if (i <= 3) {
                            newplaytile.setoccupied(true,&playertwo); 
                        }
                        else if (i >= 6) {
                            newplaytile.setoccupied(true,&playerone);
                        }
                        playabletiles[playtileindex] = newplaytile;
                        playtileindex++;
                    }
                }
            }
        }
    }*/

    void BoardSetup(int size) {
        PlayTile newPlayTile;
        int playtileIndex = 0;
        for (int i = 1; i <= size; i++) { //i is the row number, j is the column number
            for (int j = 1; j <= size; j++) {
                if (i % 2 == 0) {
                    if (j % 2 != 0) {
                        newPlayTile = PlayTile(i, j, false, false);
                        playableTiles[playtileIndex] = newPlayTile;
                        playtileIndex++;
                    }
                }
                else {
                    if (j % 2 == 0) {
                        newPlayTile = PlayTile(i, j, false, false);
                        playableTiles[playtileIndex] = newPlayTile;
                        playtileIndex++;
                    }
                }
            }
        }
        FindAdjacentPlayTiles();
    }

    void DrawBoard() {
        int counter = 1;
        for (int index = 0; index < 32; index++) {
            int i = playableTiles[index].GetRowNumber();
            int j = playableTiles[index].GetColumnNumber();

            if (index % 4 == 0) cout << endl<<endl;

            if (i % 2 == 0) {
                if (j % 2 != 0) {
                    playableTiles[index].DrawTile();
                    cout << counter++;
                    cout << "\t ----\t";
                }
            }
            else {
                if (j % 2 == 0) {
                    cout << " ----\t";
                    playableTiles[index].DrawTile();
                    cout <<counter++;
                    cout << "\t";
                }
            }
        }
        cout << endl;
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

    void FindAdjacentPlayTiles() {
        //playableTiles[index]
        PlayTile* currTile;
        PlayTile* adjTile;
        for (int i = 0; i < 32; i++) {
            currTile = &playableTiles[i];
            int row = currTile->GetRowNumber();
            int column = currTile->GetColumnNumber();
            currTile->AddAdjacentTile(GetPlayTile(row - 1, column - 1)); //diagonal up to left
            currTile->AddAdjacentTile(GetPlayTile(row - 1, column + 1)); //diagonal up to right
            currTile->AddAdjacentTile(GetPlayTile(row + 1, column - 1)); //diagonal down to left
            currTile->AddAdjacentTile(GetPlayTile(row + 1, column + 1)); //diagonal down to right
        }
    }

    PlayTile* GetPlayTile(int i, int j) {
        for (int index = 0; index < 32; index++) {
            if (i == playableTiles[index].GetRowNumber() && j == playableTiles[index].GetColumnNumber()) return &playableTiles[index];
        }
        return nullptr;
    }
   
    PlayTile* GetPlayTile(int playTileIndex) {
        return &playableTiles[playTileIndex];
    }

    int GetPlayTileNumber(PlayTile* playTile) {
        int i = playTile->GetRowNumber();
        int j = playTile->GetColumnNumber();
        for (int index = 0; index < 32; index++) {
            if (i == playableTiles[index].GetRowNumber() && j == playableTiles[index].GetColumnNumber()) return index+1;
        }
        return 0;
    }
    /*void MovePiece(int fromIndex, int toIndex) {
        PlayTile* fromTile = &playableTiles[fromIndex]; //pointing to our playtile at index. If this variable changes our object in array at index changes.
        PlayTile* toTile = &playableTiles[toIndex];

        if (!toTile->GetOccupance() && fromTile->GetOccupance()) {
            toTile->SetOccupied(fromTile->GetOccupance(), fromTile->GetOccupiedColor());
            fromTile->SetOccupied(false,' ');
        }
    }*/

   
};

class Player {
public:
    char playerColor;
    Board* gameBoard = nullptr;
    vector<PlayTile*> movablePieces;

    Player() {
        playerColor = ' ';
    }
    Player(char _playerColor,Board* board) {
        playerColor = _playerColor;
        gameBoard = board;
    }

    /*void SetBoard(Board board) {
        gameBoard = board;
    }*/
    bool isMyPiece(PlayTile* playTile) {
        if (playTile && playTile->GetOccupiedColor() == playerColor) return true;
        return false;
    }
    void SetPieces(int start, int end) { //this needs to be called once. movablepieces does not change even when player makes moves, only the position of tiles changes.
        for(int i = start; i <= end; i++) {
            PlayTile* playerPiece = &gameBoard->playableTiles[i];
            playerPiece->SetOccupied(true, playerColor);
            movablePieces.push_back(playerPiece);
        }
    }
 
    void FindMoves(PlayTile* currPlayTile) {
        if (isMyPiece(currPlayTile)) {
            PlayTile* adjTile;
            cout << "Available squares to move are: "<< endl;
            for (int i = 0; i < currPlayTile->adjacentPlayTiles.size(); i++) {
                adjTile = currPlayTile->adjacentPlayTiles[i];
                if(!adjTile->GetOccupance()) cout << gameBoard->GetPlayTileNumber(adjTile) << " ";
            } 
            cout << endl;
        }
    }

    void MovePiece(int fromIndex, int toIndex) {
        PlayTile* fromTile = &gameBoard->playableTiles[fromIndex]; //pointing to our playtile at index. If this variable changes our object in array at index changes.
        PlayTile* toTile = &gameBoard->playableTiles[toIndex];

        if (isMyPiece(fromTile) && !toTile->GetOccupance() && fromTile->GetOccupance()) {
            toTile->SetOccupied(fromTile->GetOccupance(), fromTile->GetOccupiedColor());
            fromTile->SetOccupied(false, ' ');
        }
    }


    /* void MakeMove() {
         cin >> from;
         cin >> to;
         &gameBoard.MovePiece(from, to);
     }*/
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
    cout << "Welcome to the Game of Checkers!" << "\n\n";
    int boardSize = 8;
    char playerOneColor;
    char playerTwoColor;
    Board gameBoard;
    gameBoard.BoardSetup(8);

    Player playerOne, playerTwo;
    cout << "What color is Player One?" << endl;
    cin >> playerOneColor;
    playerOne = Player(tolower(playerOneColor),&gameBoard);
    playerOne.SetPieces(20, 31);
    cout << "What color is Player Two?" << endl;
    cin >> playerTwoColor;
    playerTwo = Player(tolower(playerTwoColor),&gameBoard);
    playerTwo.SetPieces(0, 11);
    
    //gameBoard.SetupBoardPlaytiles(8, playerOne, playerTwo);
    bool playerOneTurn = true;
    
    int input;
    int from, to;
    while (true) {

        gameBoard.DrawBoard();
        //gameBoard.DrawBoardWithoutPieces(8);
        //playerOne.MakeMove();
        cin >> from;
        playerOne.FindMoves(gameBoard.GetPlayTile(from-1));
        cin >> to;
        if (playerOneTurn) playerOne.MovePiece(from-1, to-1);
        else playerTwo.MovePiece(from-1, to-1);
        playerOneTurn = !playerOneTurn;

        //cout << "It is now Player 2's turn" << endl;
        //gameBoard.MovePiece(from, to);

        //cin >> input;
        /*switch (input) {
        

        }*/
        
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
