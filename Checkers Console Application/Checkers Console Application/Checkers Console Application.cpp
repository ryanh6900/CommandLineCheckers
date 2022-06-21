
/*
Name: Command Line Checkers Program from EA interview
Date: 6/17/2022
Author: Ryan Houston


This program plays the Game of Checkers, using text input and output, in a console window.

The Checkerboard is drawn using ASCII characters, as shown below.
Each playable square on the board displays a number that is used for entering moves.
The player enters a move by first entering the number of the square with the piece to be moved, followed
by the number of the square to move the piece to.

The file includes the main program, and the follow classes:

Key abstractions:

PlayTile -- the class represents the playable squares on the game board. There are 32 PlayTiles on the board.
Player -- this class represents either a human player or the computer player
Board -- this class represent the game board, and contains the 32 PlayTiles used in the game.

Build instructions:  Compile with V11 support. For example:
    g++ -std=c++11 -o checkers checkers.cpp
    ./checkers.cpp

Running the program:
Player is promtped to enter their name and select a letter to label their peices on the board.
For example: player enters the letter 'R', their pieces will be labeled (r) and (R) when "kinged".

Moves are specified by entering to numbers, representing the "from" and "to" positions on the board.
For example: 22 17

Example board:

|-------|-------|-------|-------|-------|-------|-------|-------|
|#######|      1|#######|      2|#######|      3|#######|      4|
|#######|  (b)  |#######|  (b)  |#######|  (b)  |#######|  (b)  |
|#######|-------|#######|-------|#######|-------|#######|-------|
|      5|#######|      6|#######|      7|#######|      8|#######|
|  (b)  |#######|  (b)  |#######|  (b)  |#######|  (b)  |#######|
|-------|#######|-------|#######|-------|#######|-------|#######|
|#######|      9|#######|     10|#######|     11|#######|     12|
|#######|  (b)  |#######|  (b)  |#######|  (b)  |#######|  (b)  |
|#######|-------|#######|-------|#######|-------|#######|-------|
|     13|#######|     14|#######|     15|#######|     16|#######|
|  ( )  |#######|  ( )  |#######|  ( )  |#######|  ( )  |#######|
|-------|#######|-------|#######|-------|#######|-------|#######|
|#######|     17|#######|     18|#######|     19|#######|     20|
|#######|  ( )  |#######|  ( )  |#######|  ( )  |#######|  ( )  |
|#######|-------|#######|-------|#######|-------|#######|-------|
|     21|#######|     22|#######|     23|#######|     24|#######|
|  (r)  |#######|  (r)  |#######|  (r)  |#######|  (r)  |#######|
|-------|#######|-------|#######|-------|#######|-------|#######|
|#######|     25|#######|     26|#######|     27|#######|     28|
|#######|  (r)  |#######|  (r)  |#######|  (r)  |#######|  (r)  |
|#######|-------|#######|-------|#######|-------|#######|-------|
|     29|#######|     30|#######|     31|#######|     32|#######|
|  (r)  |#######|  (r)  |#######|  (r)  |#######|  (r)  |#######|
|-------|#######|-------|#######|-------|#######|-------|#######|


*/

#include <iostream>
#include <vector>
#include <string>
using namespace std;

/*********************
PlayTile -- models the playable squares on the board.

Knows if the square in occupied or not, and if so, what letter to display for the piece,
and if it is a king or not.

PlayTile also knows which other tiles are valid moves or jumps from the tile.

**********************/

class PlayTile {
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
        if (adjacentPlayTile) moveTiles.push_back(adjacentPlayTile);
    }

    void AddJumpPair(PlayTile* adjTile, PlayTile* jumpTo) {
        if (adjTile && jumpTo) jumpTiles.emplace_back(adjTile, jumpTo);
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

/*********************

Board

**********************/

class Board {

public:
    PlayTile playableTiles[32]; //taking advantage of the fact that arrays are static.

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

            if (index % 4 == 0 && index > 0) cout << endl << endl;

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
                    cout << counter++;
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
            currTile->AddAdjacent(GetPlayTile(row - 1, column - 1)); //diagonal up to left
            currTile->AddAdjacent(GetPlayTile(row - 1, column + 1)); //diagonal up to right
            currTile->AddAdjacent(GetPlayTile(row + 1, column - 1)); //diagonal down to left
            currTile->AddAdjacent(GetPlayTile(row + 1, column + 1)); //diagonal down to right

            currTile->AddJumpPair(GetPlayTile(row - 1, column - 1), GetPlayTile(row - 2, column - 2));
            currTile->AddJumpPair(GetPlayTile(row - 1, column + 1), GetPlayTile(row - 2, column + 2));
            currTile->AddJumpPair(GetPlayTile(row + 1, column - 1), GetPlayTile(row + 2, column - 2));
            currTile->AddJumpPair(GetPlayTile(row + 1, column + 1), GetPlayTile(row + 2, column + 2));
        }
    }

    PlayTile* GetPlayTile(int i, int j) { //very powerful function
        for (int index = 0; index < 32; index++) {
            if (i == playableTiles[index].GetRowNumber() &&
                j == playableTiles[index].GetColumnNumber()) return &playableTiles[index];
        }
        return nullptr;
    }

    PlayTile* GetPlayTile(int playTileIndex) {
        return &playableTiles[playTileIndex];
    }
    PlayTile* GetPlayTile(string verifiedTileNumber) {
        int index = stoi(verifiedTileNumber) - 1;
        return GetPlayTile(index);
    }
    int GetPlayTileNumber(PlayTile* playTile) {
        int i = playTile->GetRowNumber();
        int j = playTile->GetColumnNumber();
        for (int index = 0; index < 32; index++) {
            if (i == playableTiles[index].GetRowNumber() &&
                j == playableTiles[index].GetColumnNumber()) return index + 1;
        }
        return 0;
    }

};

/*********************

Player

**********************/

class Player {

private:
    string name;
    char playerColor;
    Board* gameBoard = nullptr;
    vector<PlayTile*> movablePieces;
    int upDirection = 0;
    int pieceCount;
    bool playerIsMad; //a little humor
public:
    Player() {
        playerColor = ' ';
        upDirection = 0;
        gameBoard = nullptr;
        name = "";
    }
    Player(char _playerColor, Board* board, int direction, string _name = "Human") {
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
        for (int i = start; i <= end; i++) {
            PlayTile* playerPiece = &gameBoard->playableTiles[i];
            playerPiece->SetOccupied(true, playerColor);
        }
    }
    void ResignAndKnockPiecesOffBoard() {
        for (int i = 0; i < 32; i++)
            if (toupper(gameBoard->playableTiles[i].GetOccupiedColor()) == toupper(playerColor))
                gameBoard->playableTiles[i].SetOccupied(false);
        playerIsMad = true;
    }
    bool IsAGoodPlayer() {
        return !playerIsMad;
    }
    int GetPieceCount() {
        pieceCount = 0;
        for (int i = 0; i < 32; i++) {
            if (toupper(gameBoard->playableTiles[i].GetOccupiedColor()) == toupper(playerColor))
                pieceCount++;
        }
        return pieceCount;
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
        else cout << "There are no available single moves!" << endl;
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
            if (FindPossibleMoves(currTile).size()) movablePieces.push_back(currTile);
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
                    if (currPlayTile->GetPower() || rowDifference * upDirection > 0) //results.insert(results.begin(), possibleMoveTile);
                    results.push_back(possibleMoveTile);
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
                if (!possibleJumpTile->GetOccupance() && jumpee->GetOccupance() && !isMyPiece(jumpee)) {
                    if (currPlayTile->GetPower()) results.insert(results.begin(), possibleJumpTile);
                    else if (rowDifference * upDirection > 0) results.push_back(possibleJumpTile);
                }
            }
        }
        return results;
    }

    void MovePiece(int fromIndex, int toIndex) {
        UpdateMovablePieces();
        PlayTile* fromTile = &gameBoard->playableTiles[fromIndex]; //pointing to our playtile at index. If this variable changes our object in array at index changes.
        PlayTile* toTile = &gameBoard->playableTiles[toIndex];
        MovePiece(fromTile, toTile);
    }

    void CheckMultipleJump(PlayTile* toTile) {
        // find new jumps starting at the toTile from previous jump
        vector<PlayTile*> nextJumps = FindPossibleJumps(toTile);
        if (nextJumps.empty()) return;
        // another jump exists
        PlayTile* newToTile = nextJumps[0];
        MovePiece(toTile, newToTile); 
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
                    cout << name << " jumped from " << gameBoard->GetPlayTileNumber(fromTile);
                    cout << " to " << gameBoard->GetPlayTileNumber(toTile) << endl;
                    CheckMultipleJump(toTile); //recursively calls MovePiece if needed
                    return;
                }
            }
            if (isMyPiece(fromTile) && !toTile->GetOccupance() && fromTile->GetOccupance()) {
                toTile->SetOccupied(fromTile->GetOccupance(), fromTile->GetOccupiedColor(), CheckForKing(toTile));
                fromTile->SetOccupied(false);
                cout << name << " moved " << gameBoard->GetPlayTileNumber(fromTile);
                cout << " to " << gameBoard->GetPlayTileNumber(toTile) << endl;
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

    void AutoMove() { //This is the function that is called for the computer aka playerTwo.
        UpdateMovablePieces();
        PlayTile* fromTile;
        PlayTile* toTile;
        if (movablePieces.size()) {
            for (int i = 0; i < movablePieces.size(); i++) {
                fromTile = movablePieces[i];
                vector<PlayTile*> possibleJumps = FindPossibleJumps(fromTile); //move priority goes to jump moves.
                if (possibleJumps.size()) {
                    toTile = possibleJumps[0];
                    MovePiece(fromTile, toTile);
                    return;
                }
            }
            int randNumber = rand() % movablePieces.size();
            //cout << randNumber << " " << movablePieces.size() << " " << endl;
            fromTile = movablePieces[randNumber];
            vector<PlayTile*> possibleMoves = FindPossibleMoves(fromTile); //if not jump moves, priority moves to regular moves.
            if (possibleMoves.size()) {
                randNumber = rand() % possibleMoves.size();
                toTile = possibleMoves[randNumber];
                MovePiece(fromTile, toTile);
                return;
            }
        }
        else {
            cout << "There are no available moves for " << name << endl;
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
        PlayTile* playTile = gameBoard->GetPlayTile(playTileNumber);
        if ((FindPossibleMoves(playTile).size()) ||
            FindPossibleJumps(playTile).size()){
            return true;
        }
        return false;
    }

    bool CheckIsPossibleTo(string toString, string fromString) {
        cout << toString << " and " << fromString << endl;
        PlayTile* toPlayTile = gameBoard->GetPlayTile(toString);
        PlayTile* fromPlayTile = gameBoard->GetPlayTile(fromString);
        vector<PlayTile*> possibleMoves = FindPossibleMoves(fromPlayTile); 
        vector<PlayTile*> possibleJumps = FindPossibleJumps(fromPlayTile);
        auto it = find(possibleMoves.begin(), possibleMoves.end(), toPlayTile);
        auto it2 = find(possibleJumps.begin(), possibleJumps.end(), toPlayTile);
        if (it != possibleMoves.end() || it2 != possibleJumps.end()) return true;
        return false;
    }

    bool CheckTo(string to, string from) {
        if (CheckPlayTileInput(to) && CheckIsPossibleTo(to, from)) return true;
        return false;
    }
};

int main()
{
    cout << "Welcome to the Game of Checkers!" << "\n\n";
    int boardSize = 8;
    
    char playerOneColor;
    char playerTwoColor;
    bool hintsOn;
    bool autoPlaying;
    bool fromIsValid, toIsValid;
    bool donePlaying, playerResigning;
    Board gameBoard;

    Player playerOne, playerTwo;
    string playerName;
    string input;
    string buffer;
    string fromString, toString;
    gameBoard.BoardSetup(8);//board starts out as empty.

    cout << "What is your name?" << endl;
    getline(cin, playerName);
    playerName.erase(remove(playerName.begin(), playerName.end(), ' '), playerName.end());
    cout << "\n" << playerName << ", what character would you like for your pieces?" << endl;
    getline(cin, input);
    playerOneColor = input.empty() ? 'R' : input[0];
    playerOne = Player(tolower(playerOneColor), &gameBoard, 1, playerName);
    playerOne.SetPieces(20, 31);

    cout << "\n" << playerName << ", what character would you like the computer to have?" << endl;
    getline(cin, input);
    playerTwoColor = input.empty() ? 'B' : input[0];
    playerTwo = Player(tolower(playerTwoColor), &gameBoard, -1, "Computer");
    playerTwo.SetPieces(0, 11);

    cout << "\n" << playerName << ", are you new to Checkers? (Y/N)" << endl;
    getline(cin, input);

    if (toupper(input[0]) == 'Y') {
        hintsOn = true;
        cout << "\n" << "*Hints Enabled*" << endl;
    }
    else {
        hintsOn = false;
        cout << "\n" << "*Hints Disabled*" << endl;
    }
    
    playerResigning = false;
    donePlaying = false;
    //Main Game Loop
    while (!donePlaying) {
        if (playerOne.GetPieceCount() == 0 || playerTwo.GetPieceCount() == 0) {
            string winnerName = (playerOne.GetPieceCount()==0 && !playerOne.IsAGoodPlayer()) ? playerTwo.GetName() : playerOne.GetName();
            cout << "\nGAMEOVER!\nThe winner is " << winnerName << "!\nWould you like to play again? (Y/N) " << endl;
            getline(cin, input);
            if (toupper(input[0]) == 'Y') {
                gameBoard.BoardSetup(8);
                playerTwo.SetPieces(0, 11);
                playerOne.SetPieces(20, 31);
                cout << "Would you like hints this time? (Y/N)" << endl;
                getline(cin, input);
                if (toupper(input[0]) == 'Y') {
                    hintsOn = true;
                    cout << "\n" << "*Hints Enabled*" << endl;
                }
                else {
                    hintsOn = false;
                    cout << "\n" << "*Hints Disabled*" << endl;
                }
                playerResigning = false;
            }
            else donePlaying = true;
        }
        fromIsValid = false;
        toIsValid = false;
        autoPlaying = false;

        gameBoard.DrawFormattedBoard();
        cout << "You have " << playerOne.GetPieceCount() << " pieces left | The Computer has " 
            << playerTwo.GetPieceCount() << " pieces left...";
        if (playerOne.GetPieceCount() > playerTwo.GetPieceCount()) cout << "YOU ARE WINNING IN MATERIAL!" << endl;
        else if (playerOne.GetPieceCount() == playerTwo.GetPieceCount()) cout << "The material is even." << endl;
        else cout << "You are losing in material." << endl;
        cout << "It is your turn, " << playerOne.GetName() << "." << endl;
        if(hintsOn) cout << "Enter the number for the tile you would like to move, then enter the tile you would like to move to. \nType 'resign' to play again more quickly" << endl;

        while (!fromIsValid && !autoPlaying && !playerResigning) {

            getline(cin, fromString);

            if (!fromString.compare("resign")) {
                playerOne.ResignAndKnockPiecesOffBoard();
                playerResigning = true;
            }
            else if (playerOne.CheckFrom(fromString)) {
              
                fromIsValid = true;
            }
            else {
                if (fromString[0] == '0') autoPlaying = true;
                else cout << "That is not a valid move. Please try again." << endl;
            }
        }
        if (playerResigning) continue;
        if (hintsOn && !autoPlaying) {
            playerOne.DisplayPossibleMoves(gameBoard.GetPlayTile(fromString));
            playerOne.DisplayPossibleJumps(gameBoard.GetPlayTile(fromString));
            cout << endl;
        }

        while (!toIsValid && !autoPlaying) {

            getline(cin, toString);
            if (playerOne.CheckTo(toString, fromString)) {
               
                toIsValid = true;
            }
            else cout << "That is not a valid square to move to. Please try again." << endl;
        }
        
        if (autoPlaying) {
            playerOne.AutoMove();
            autoPlaying = false;
        }
        else {
            int to = stoi(toString) - 1;
            int from = stoi(fromString) - 1;
            playerOne.MovePiece(from, to);
        }
        playerTwo.AutoMove();
    }
    return 0;
}

