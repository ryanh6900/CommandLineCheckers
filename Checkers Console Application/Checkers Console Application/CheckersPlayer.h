#pragma once
#include "GamePlayer.h"
#include "CheckersBoard.h"
#include "CheckersPiece.h"
#include "BoardSquare.h"
class CheckersPlayer :
    public GamePlayer
{
private:
    vector<CheckersPiece*> moveablePieces;
    int upDirection = 0;
    int pieceCount;

public:
    CheckersPlayer();
    CheckersPlayer(char _playerColor, int direction, CheckersBoard* board, string _name = "Human");
    void SetPieces(int start, int end);
};

//class Player {
//
//private:
//    string name;
//    char playerColor;
//    Board* gameBoard = nullptr;
//    vector<PlayTile*> movablePieces;
//    int upDirection = 0; //used to determine which moves are appropriate for the player based on what side of the board they are on. 
//    int pieceCount;
//    bool playerIsMad; //a little humor
//
//public:
//    Player() {
//        playerColor = ' ';
//        upDirection = 0;
//        gameBoard = nullptr;
//        name = "";
//    }
//    Player(char _playerColor, Board* board, int direction, string _name = "Human") {
//        playerColor = _playerColor;
//        gameBoard = board;
//        upDirection = direction;
//        name = _name;
//    }
//    string GetName() {
//        return name;
//    }
//    bool isMyPiece(PlayTile* playTile) {
//        if (playTile && toupper(playTile->GetOccupiedColor()) == toupper(playerColor)) return true;
//        return false;
//    }
//    void SetPieces(int start, int end) { //this needs to be called once. movablepieces does not change even when player makes moves, only the position of tiles changes.
//        for (int i = start; i <= end; i++) {
//            PlayTile* playerPiece = &gameBoard->playableTiles[i];
//            playerPiece->SetOccupied(true, playerColor);
//        }
//    }
//    void ResignAndKnockPiecesOffBoard() {
//        for (int i = 0; i < 32; i++)
//            if (toupper(gameBoard->playableTiles[i].GetOccupiedColor()) == toupper(playerColor))
//                gameBoard->playableTiles[i].SetOccupied(false);
//        playerIsMad = true;
//    }
//    bool IsAGoodPlayer() {
//        return !playerIsMad;
//    }
    /*int GetPieceCount() {
        pieceCount = 0;
        for (int i = 0; i < 32; i++) {
            if (toupper(gameBoard->playableTiles[i].GetOccupiedColor()) == toupper(playerColor))
                pieceCount++;
        }
        return pieceCount;
    }*/
//
//    void DisplayPossibleMoves(PlayTile* currPlayTile) {
//        vector <PlayTile*>::iterator it;
//        vector<PlayTile*> possibleMoveTiles = FindPossibleMoves(currPlayTile);
//
//        if (isMyPiece(currPlayTile) && possibleMoveTiles.size()) {
//            PlayTile* adjTile;
//            cout << "Available squares to move are: " << endl;
//            for (int i = 0; i < possibleMoveTiles.size(); i++) {
//                adjTile = possibleMoveTiles[i];
//                if (!adjTile->GetOccupance()) cout << gameBoard->GetPlayTileNumber(adjTile) << " ";
//            }
//            cout << endl;
//        }
//        else cout << "There are no available single moves!" << endl;
//    }
//
//    void DisplayPossibleJumps(PlayTile* currPlayTile) {
//        vector <PlayTile*>::iterator it;
//        vector<PlayTile*> jumpTiles = FindPossibleJumps(currPlayTile);
//
//        if (isMyPiece(currPlayTile) && jumpTiles.size()) {
//            cout << "There are jumps available! Available squares to jump are: " << endl;
//            for (auto it = jumpTiles.begin(); it != jumpTiles.end(); it++) {
//                auto& jumpTile = *it;
//                cout << gameBoard->GetPlayTileNumber(jumpTile) << " ";
//            }
//            cout << endl;
//        }
//    }
//
//    void UpdateMovablePieces() {
//        movablePieces.clear();
//        PlayTile* currTile;
//        for (int i = 0; i < 32; i++) {
//            currTile = gameBoard->GetPlayTile(i);
//            if (FindPossibleMoves(currTile).size()) movablePieces.push_back(currTile);
//            if (FindPossibleJumps(currTile).size()) movablePieces.push_back(currTile);
//        }
//    }
//
//    vector<PlayTile*> FindPossibleMoves(PlayTile* currPlayTile) {
//        PlayTile* possibleMoveTile;
//        vector<PlayTile*> results;
//
//        if (isMyPiece(currPlayTile)) {
//            for (int i = 0; i < currPlayTile->moveTiles.size(); i++) {
//                possibleMoveTile = currPlayTile->moveTiles[i];
//                int rowDifference = currPlayTile->GetRowNumber() - possibleMoveTile->GetRowNumber();
//                if (!possibleMoveTile->GetOccupance()) {
//                    if (currPlayTile->GetPower() || rowDifference * upDirection > 0) //results.insert(results.begin(), possibleMoveTile);
//                        results.push_back(possibleMoveTile);
//                }
//
//            }
//        }
//        return results;
//    }
//
//    vector<PlayTile*> FindPossibleJumps(PlayTile* currPlayTile) {
//        PlayTile* possibleJumpTile;
//        PlayTile* jumpee;
//        vector<PlayTile*> results;
//        if (isMyPiece(currPlayTile)) {
//            for (int i = 0; i < currPlayTile->jumpTiles.size(); i++) {
//                jumpee = currPlayTile->jumpTiles[i].first;
//                possibleJumpTile = currPlayTile->jumpTiles[i].second;
//                int rowDifference = currPlayTile->GetRowNumber() - possibleJumpTile->GetRowNumber();
//                //Below are the conditions for the possible jumpTile to jump the jumpee
//                if (!possibleJumpTile->GetOccupance() && jumpee->GetOccupance() && !isMyPiece(jumpee)) {
//                    if (currPlayTile->GetPower()) results.insert(results.begin(), possibleJumpTile);
//                    else if (rowDifference * upDirection > 0) results.push_back(possibleJumpTile);
//                }
//            }
//        }
//        return results;
//    }
//
//    void MovePiece(int fromIndex, int toIndex) {
//        UpdateMovablePieces();
//        PlayTile* fromTile = &gameBoard->playableTiles[fromIndex]; //pointing to our playtile at index. If this variable changes our object in array at index changes.
//        PlayTile* toTile = &gameBoard->playableTiles[toIndex];
//        MovePiece(fromTile, toTile);
//    }
//
//    void CheckMultipleJump(PlayTile* toTile) { //recursively call to MovePiece, how we check to double or triple jump.
//        // find new jumps starting at the toTile from previous jump
//        vector<PlayTile*> nextJumps = FindPossibleJumps(toTile);
//        if (nextJumps.empty()) return;
//        // another jump exists
//        PlayTile* newToTile = nextJumps[0];
//        MovePiece(toTile, newToTile);
//    }
//
//    void MovePiece(PlayTile* fromTile, PlayTile* toTile) {
//        if (isMyPiece(fromTile)) {
//            PlayTile* jumpee;
//            for (int i = 0; i < fromTile->jumpTiles.size(); i++) {
//                if (toTile == fromTile->jumpTiles[i].second) {
//                    jumpee = fromTile->jumpTiles[i].first;
//                    toTile = fromTile->jumpTiles[i].second;
//                    toTile->SetOccupied(fromTile->GetOccupance(), fromTile->GetOccupiedColor(), CheckForKing(toTile));
//                    fromTile->SetOccupied(false);
//                    jumpee->SetOccupied(false);
//                    cout << name << " jumped from " << gameBoard->GetPlayTileNumber(fromTile);
//                    cout << " to " << gameBoard->GetPlayTileNumber(toTile) << endl;
//                    CheckMultipleJump(toTile); //recursively calls MovePiece if needed to do double, and even triple jumps.
//                    return;
//                }
//            }
//            if (isMyPiece(fromTile) && !toTile->GetOccupance() && fromTile->GetOccupance()) {
//                toTile->SetOccupied(fromTile->GetOccupance(), fromTile->GetOccupiedColor(), CheckForKing(toTile));
//                fromTile->SetOccupied(false);
//                cout << name << " moved " << gameBoard->GetPlayTileNumber(fromTile);
//                cout << " to " << gameBoard->GetPlayTileNumber(toTile) << endl;
//            }
//        }
//    }
//
//    bool CheckForKing(PlayTile* toTile) {
//        if (toTile->GetRowNumber() == 1 || toTile->GetRowNumber() == 8)
//            return true;
//        return false;
//    }
//
//    void AutoMove() { //This is the function that is called for the computer aka playerTwo.
//        UpdateMovablePieces();
//        PlayTile* fromTile;
//        PlayTile* toTile;
//        if (movablePieces.size()) {
//            for (int i = 0; i < movablePieces.size(); i++) {
//                fromTile = movablePieces[i];
//                vector<PlayTile*> possibleJumps = FindPossibleJumps(fromTile); //move priority goes to jump moves.
//                if (possibleJumps.size()) {
//                    toTile = possibleJumps[0];
//                    MovePiece(fromTile, toTile);
//                    return;
//                }
//            }
//            int randNumber = rand() % movablePieces.size();
//            fromTile = movablePieces[randNumber];
//            vector<PlayTile*> possibleMoves = FindPossibleMoves(fromTile); //if not jump moves, priority moves to regular moves.
//            if (possibleMoves.size()) {
//                randNumber = rand() % possibleMoves.size();
//                toTile = possibleMoves[randNumber];
//                MovePiece(fromTile, toTile);
//                return;
//            }
//        }
//        else {
//            cout << "There are no available moves for " << name << endl;
//        }
//
//    }
//
//    bool CheckFrom(string str) {
//        if (CheckPlayTileInput(str) && CheckMoveAvailability(str)) return true;
//        return false;
//    }
//
//    bool CheckTo(string to, string from) {
//        if (CheckPlayTileInput(to) && CheckIsPossibleTo(to, from)) return true;
//        return false;
//    }
//
//    bool CheckPlayTileInput(string str) {
//        for (int i = 0; i < str.length(); i++)
//            if (isdigit(str[i]))
//                return true;
//        return false;
//    }
//
//    bool CheckMoveAvailability(string playTileNumber) {
//        PlayTile* playTile = gameBoard->GetPlayTile(playTileNumber);
//        if ((FindPossibleMoves(playTile).size()) ||
//            FindPossibleJumps(playTile).size()) {
//            return true;
//        }
//        return false;
//    }
//
//    bool CheckIsPossibleTo(string toString, string fromString) {
//        PlayTile* toPlayTile = gameBoard->GetPlayTile(toString);
//        PlayTile* fromPlayTile = gameBoard->GetPlayTile(fromString);
//        vector<PlayTile*> possibleMoves = FindPossibleMoves(fromPlayTile);
//        vector<PlayTile*> possibleJumps = FindPossibleJumps(fromPlayTile);
//        auto it = find(possibleMoves.begin(), possibleMoves.end(), toPlayTile);
//        auto it2 = find(possibleJumps.begin(), possibleJumps.end(), toPlayTile);
//        if (it != possibleMoves.end() || it2 != possibleJumps.end()) return true;
//        return false;
//    }
//};
