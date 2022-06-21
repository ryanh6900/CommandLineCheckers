// Checkers Console Application.cpp : This file contains the 'main' function. Program execution begins and ends there.
//
/***************************************************************************************
*    Title: Command Line Checkers Program for EA 
*    Author: Ryan Houston
*    Date: 6/16/2022
*    Availability: https://github.com/ryanh6900
***************************************************************************************/
#include <iostream>
#include <vector>
#include <string>
using namespace std;

class PlayTile {//Remember to model abstractions after real-world concepts within the game of checkers.
private:
    int rowNum, columnNum;
    bool isOccupied, isKing;
    char occupiedPieceColor = ' ';
    //char emptySymbol = ' ';

public:
    vector<PlayTile*> moveTiles; //These are tiles that one diagonal away.
    vector<pair<PlayTile*, PlayTile*>> jumpTiles; //These are tiles that are exactly two diagonals away. I talked about this briefly in the interview.

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

    void SetOccupied(bool _isOccupied, char _occupiedPieceColor = ' ', bool _isKing = false) {
        isOccupied = _isOccupied;
        occupiedPieceColor = _occupiedPieceColor;
        isKing = _isKing;
    }

    void AddAdjacent(PlayTile* adjacentPlayTile) {
        if(adjacentPlayTile) moveTiles.push_back(adjacentPlayTile);
    }
    
    void AddJumpPair(PlayTile* adjTile, PlayTile* jumpTo) {
        if (adjTile && jumpTo) jumpTiles.emplace_back(adjTile,jumpTo);
    }

    void Draw() {
        if (isKing && isOccupied) occupiedPieceColor = toupper(occupiedPieceColor);
        cout << " (" << occupiedPieceColor << ") ";
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
    bool GetPower() {
        return isKing;
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
    void DrawFormattedTile(int whichLine, int index) {
        int tileNum = index + 1;
        switch (whichLine) {
        case 1: // first line displays the tile number
            cout << "|     ";
            if (tileNum < 10) cout << " ";
            cout << tileNum;
            break;
        case 2: // second line displays the checker piece
            cout << "| ";
            playableTiles[index].Draw(); // outputs exactly 5 chars
            cout << " ";
            break;
        case 3: // third line is the bottom of the square
            cout << "|-------";
        }
    }
    void DrawFormattedBoard() {
        string unusedTile = "|#######";
        int index;
        for (int i = 0; i < 8; i++) cout << "|-------";
        cout << "|" << endl;
        for (int row = 0; row < 8; row++) {
            for (int lineCnt = 1; lineCnt <= 3; lineCnt++) { // multiple lines drawn for each tile
                for (int col = 0; col < 4; col++) {
                    index = row * 4 + col;
                    if (row % 2 == 0) {
                        cout << unusedTile;
                        DrawFormattedTile(lineCnt, index);
                    }
                    else {
                        DrawFormattedTile(lineCnt, index);
                        cout << unusedTile;
                    }
                }
                cout << "|" << endl;
            }
        }
    }
    void DrawBoard() {
        int counter = 1;
        for (int index = 0; index < 32; index++) {
            int i = playableTiles[index].GetRowNumber();
            int j = playableTiles[index].GetColumnNumber();

            if (index % 4 == 0 && index >0) cout << endl<<endl;

            if (i % 2 == 0) {
                if (j % 2 != 0) {
                    playableTiles[index].Draw();
                    cout << counter++;
                    cout << "\t ----\t";
                }
            }
            else {
                if (j % 2 == 0) {
                    cout << " ----\t";
                    playableTiles[index].Draw();
                    cout <<counter++;
                    cout << "\t";
                }
            }
        }
        cout << endl;
    }

    void DrawBoardWithoutPieces(int size) { //just used to faciliate my understanding for the checkerboard pattern.
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
            currTile->AddAdjacent(GetPlayTile(row - 1, column - 1)); //diagonal up to left
            currTile->AddAdjacent(GetPlayTile(row - 1, column + 1)); //diagonal up to right
            currTile->AddAdjacent(GetPlayTile(row + 1, column - 1)); //diagonal down to left
            currTile->AddAdjacent(GetPlayTile(row + 1, column + 1)); //diagonal down to right
            
            currTile->AddJumpPair(GetPlayTile(row - 1, column - 1),GetPlayTile(row - 2, column - 2));
            currTile->AddJumpPair(GetPlayTile(row - 1, column + 1),GetPlayTile(row - 2, column + 2));
            currTile->AddJumpPair(GetPlayTile(row + 1, column - 1), GetPlayTile(row + 2, column - 2));
            currTile->AddJumpPair(GetPlayTile(row + 1, column + 1), GetPlayTile(row + 2, column + 2));
        }
    }

    PlayTile* GetPlayTile(int i, int j) { //very powerful function
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
private:
    string name;
    char playerColor;
    Board* gameBoard = nullptr;
    vector<PlayTile*> movablePieces;
    int upDirection = 0;
public:
    Player() {
        playerColor = ' ';
        upDirection = 0;
        gameBoard = nullptr;
        name = "";
    }
    Player(char _playerColor,Board* board,int direction, string _name = "Human") {
        playerColor = _playerColor;
        gameBoard = board;
        upDirection = direction;
        name = _name;
    }
    string GetName() {
        return name;
    }
    /*void SetBoard(Board board) {
        gameBoard = board;
    }*/
    bool isMyPiece(PlayTile* playTile) {
        if (playTile && toupper(playTile->GetOccupiedColor()) == toupper(playerColor)) return true;
        return false;
    }
    void SetPieces(int start, int end) { //this needs to be called once. movablepieces does not change even when player makes moves, only the position of tiles changes.
        for(int i = start; i <= end; i++) {
            PlayTile* playerPiece = &gameBoard->playableTiles[i];
            playerPiece->SetOccupied(true, playerColor);
        }
    }

    void DisplayPossibleMoves(PlayTile* currPlayTile) {
        vector <PlayTile*>::iterator it;
        vector<PlayTile*> possibleMoveTiles = FindPossibleMoves(currPlayTile);

        if (isMyPiece(currPlayTile) && possibleMoveTiles.size()) {
            PlayTile* adjTile;
            cout << "Available squares to move are: " << endl;
            for (int i = 0; i < possibleMoveTiles.size(); i++) {
                adjTile = possibleMoveTiles[i];
                if (!adjTile->GetOccupance()) cout << gameBoard->GetPlayTileNumber(adjTile) << " ";
            }
            cout << endl;
        }
        else cout << "There are no available moves!" << endl;
    }

    void DisplayPossibleJumps(PlayTile* currPlayTile) {
        vector <PlayTile*>::iterator it;
        vector<PlayTile*> jumpTiles = FindPossibleJumps(currPlayTile);
        
        if (isMyPiece(currPlayTile) && jumpTiles.size()) {
            cout << "There are jumps available! Available squares to jump are: " << endl;
            for (auto it = jumpTiles.begin(); it != jumpTiles.end(); it++) {
                // found nth element..print and break.
                auto& jumpTile = *it;
                cout << gameBoard->GetPlayTileNumber(jumpTile) << " ";
            }
            cout << endl;
        }
    }
   
    void UpdateMovablePieces() {
        movablePieces.clear();
        PlayTile* currTile;
        for (int i = 0; i < 32; i++) {
            currTile = gameBoard->GetPlayTile(i);
            if(FindPossibleMoves(currTile).size()) movablePieces.push_back(currTile);
            if (FindPossibleJumps(currTile).size()) movablePieces.push_back(currTile);
        }
    }

    vector<PlayTile*> FindPossibleMoves(PlayTile* currPlayTile) {
        PlayTile* possibleMoveTile;
        vector<PlayTile*> results;

        if (isMyPiece(currPlayTile)) {
            for (int i = 0; i < currPlayTile->moveTiles.size(); i++) {
                possibleMoveTile = currPlayTile->moveTiles[i];
                int rowDifference = currPlayTile->GetRowNumber() - possibleMoveTile->GetRowNumber();
                if (!possibleMoveTile->GetOccupance()) {
                        if (currPlayTile->GetPower()) results.insert(results.begin(), possibleMoveTile);
                        else if (rowDifference * upDirection > 0) results.push_back(possibleMoveTile);  
                }
                
            }
        }
        return results;
    }

    vector<PlayTile*> FindPossibleJumps(PlayTile* currPlayTile) {
        PlayTile* possibleJumpTile;
        PlayTile* jumpee;
        vector<PlayTile*> results;
        if (isMyPiece(currPlayTile)) {
            for (int i = 0; i < currPlayTile->jumpTiles.size(); i++) {
                jumpee = currPlayTile->jumpTiles[i].first;
                possibleJumpTile = currPlayTile->jumpTiles[i].second;
                int rowDifference = currPlayTile->GetRowNumber() - possibleJumpTile->GetRowNumber();
                //Below are the conditions for the possible jumpTile to jump the jumpee
                if (!possibleJumpTile->GetOccupance() && jumpee->GetOccupance() && !isMyPiece(jumpee))
                    if (currPlayTile->GetPower())results.insert(results.begin(), possibleJumpTile);
                    else if (rowDifference * upDirection > 0) results.push_back(possibleJumpTile);
            }
        }
        return results;
    }

    void MovePiece(int fromIndex, int toIndex) {
        UpdateMovablePieces();
        PlayTile* fromTile = &gameBoard->playableTiles[fromIndex-1]; //pointing to our playtile at index. If this variable changes our object in array at index changes.
        PlayTile* toTile = &gameBoard->playableTiles[toIndex-1];
        MovePiece(fromTile, toTile);
    }
    
    void MovePiece(PlayTile* fromTile, PlayTile* toTile) {
        if (isMyPiece(fromTile)) {
            PlayTile* jumpee;
            for (int i = 0; i < fromTile->jumpTiles.size(); i++) {
                if (toTile == fromTile->jumpTiles[i].second) {
                    jumpee = fromTile->jumpTiles[i].first;
                    toTile = fromTile->jumpTiles[i].second;
                    toTile->SetOccupied(fromTile->GetOccupance(), fromTile->GetOccupiedColor(), CheckForKing(toTile));
                    fromTile->SetOccupied(false);
                    jumpee->SetOccupied(false);
                    return;
                }
            }
            if (isMyPiece(fromTile) && !toTile->GetOccupance() && fromTile->GetOccupance()) {
                toTile->SetOccupied(fromTile->GetOccupance(), fromTile->GetOccupiedColor(),CheckForKing(toTile));
                fromTile->SetOccupied(false);
            }
        }
    }

    bool CheckForKing(PlayTile* toTile) {
        if (toTile->GetRowNumber() == 1 || toTile->GetRowNumber() == 8) {
            //cout << "KingToUpgrade " << gameBoard->GetPlayTileNumber(toTile) << endl;
            return true;
        }
        return false;
    }

    void AutoMove() { //This is the function that is called for the computer aka playerTwo, playerOne if you select auto-move.
        UpdateMovablePieces();
        PlayTile* fromTile;
        PlayTile* toTile;
        if (movablePieces.size()) {
            for (int i = 0; i < movablePieces.size(); i++) {
                fromTile = movablePieces[i];
                vector<PlayTile*> possibleJumps = FindPossibleJumps(fromTile); //auto-move priority goes to jump moves.
                if (possibleJumps.size()) {
                    toTile = possibleJumps[0];
                    cout << name << " jumped from " << gameBoard->GetPlayTileNumber(fromTile) << " to " << gameBoard->GetPlayTileNumber(toTile) << endl;
                    //<< ", taking the " << << endl;
                    MovePiece(fromTile, toTile);
                    return;
                }
            }
            int randNumber = rand() % movablePieces.size();
            //cout << randNumber << " " << movablePieces.size() << " " << endl;
            fromTile = movablePieces[randNumber];
            vector<PlayTile*> possibleMoves = FindPossibleMoves(fromTile); //if not jump moves, priority moves to regular moves.
            if (possibleMoves.size()) {
                toTile = possibleMoves[0];
                MovePiece(fromTile, toTile);
                cout << name << " moved " << gameBoard->GetPlayTileNumber(fromTile) << " to " << gameBoard->GetPlayTileNumber(toTile) << endl;
                return;
            }
        }
        else {
            cout << "There are no available moves for " << name << ". YOU WIN!" << endl;
        }

    }
    bool CheckPlayTileInput(string str) {
        for (int i = 0; i < str.length(); i++)
            if (isdigit(str[i]))
                return true;
        return false;
    }
    bool CheckFrom(string str) {
        if (CheckPlayTileInput(str) && CheckMoveAvailability(str)) return true;
        return false;
    }
    bool CheckMoveAvailability(string playTileNumber) {
        if ((FindPossibleMoves(gameBoard->GetPlayTile(stoi(playTileNumber)-1)).size()) && 
            FindPossibleJumps(gameBoard->GetPlayTile(stoi(playTileNumber)-1)).size()){
            return true;
        }
        return false;
    }
    bool CheckIsPossibleTo(int to, int from) {
        for (int i = 0; i < gameBoard->GetPlayTile(from-1)->moveTiles.size(); i++) {
            if (gameBoard->GetPlayTile(from-1)->moveTiles[i] == gameBoard->GetPlayTile(to-1)) return true;
        }
        return false;
    }
   
    bool CheckTo(string str, int from) {
        if (CheckPlayTileInput(str) && CheckIsPossibleTo(stoi(str),from)) return true;
        return false;
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
    int gameMode;
    char playerOneColor;
    char playerTwoColor;
    bool hintsOn;
    bool autoPlaying;
    bool fromIsValid,toIsValid;
    bool gameOver;
    Board gameBoard;
    
    Player playerOne, playerTwo;
    string playerName;
    string input;
    string buffer;
    gameBoard.BoardSetup(8);//board starts out as empty.

    cout << "What is your name?" << endl;
    getline(cin, playerName);
    cout << "\n"<<playerName << ", What character would you like for your pieces?" << endl;
    getline(cin, input);
    playerOneColor = input.empty() ? 'R' : input[0];
    playerOne = Player(tolower(playerOneColor),&gameBoard,1,playerName);
    playerOne.SetPieces(20, 31);

    cout << "\n" << playerName<< ", What character would you like the computer to have?" << endl;
    getline(cin, input);
    playerTwoColor = input.empty() ? 'B' : input[0];
    playerTwo = Player(tolower(playerTwoColor), &gameBoard, -1, "Computer");
    playerTwo.SetPieces(0, 11);

    cout << "\n" << playerName << ", Are you new to Checkers? (Answer Y/N)" << endl;
    getline(cin, input);

    if (toupper(input[0]) == 'Y') {
        hintsOn = true;
        cout <<"\n" << "*Hints Enabled*" << endl;
    }
    else {
        hintsOn = false;
        cout << "\n"<< "*Hints Disabled*" << endl;
    }
    int from, to;
    gameOver = false;


    //Main Game Loop
    while (!gameOver) {

        gameBoard.DrawFormattedBoard();
        //gameBoard.DrawBoardWithoutPieces(8);
        //playerOne.MakeMove();
        fromIsValid = false;
        toIsValid = false;
        autoPlaying = false;
        cout << "It is your turn, " << playerOne.GetName() << ". Enter the number for the tile you would like to move, then enter the tile you would like to move to." << endl;
        while (!fromIsValid && !autoPlaying) {
            getline(cin, input);
            if (playerOne.CheckFrom(input)) {
                from = stoi(input);
                fromIsValid = true;
            } 
            else {
                if (input[0] == '0') autoPlaying = true;
                else cout << "That is not a valid move. Please try again." << endl;
            }
        }
        if (hintsOn && !autoPlaying) {
            playerOne.DisplayPossibleMoves(gameBoard.GetPlayTile(from));
            playerOne.DisplayPossibleJumps(gameBoard.GetPlayTile(from));
            cout << endl;
        }
        
        while (!toIsValid && !autoPlaying) {
            
            getline(cin, input);
            if (playerOne.CheckTo(input, from)) {
                to = stoi(input);
                toIsValid = true;
            }
            else cout << "That is valid square to move to. Please try again." << endl;
        }
        if (autoPlaying) playerOne.AutoMove();
        else playerOne.MovePiece(from, to);

        playerTwo.AutoMove(); 
            return 0;
        }
    }