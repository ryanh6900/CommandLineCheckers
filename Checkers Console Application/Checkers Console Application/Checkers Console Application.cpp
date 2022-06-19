// Checkers Console Application.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <vector>
using namespace std;
struct Piece {
    char color;
    int row, column;
    bool isCaptured;

    Piece(char _color, int _row, int _column, bool _isCaptured) {
       color = _color;
       row = _row;
       column = _column;
       isCaptured = _isCaptured;
    }
    void DrawPiece(char color) {
        std::cout << " "<< color << " ";
    }

    int GetRow() {
        return row;
    }
    int GetColumn() {
        return column;
    }
    char GetColor() {
        return color;
    }
};

struct Board {
    void DrawBoardWithoutPieces(int size) {
        for (int i = 0; i < size; i++) {
            for (int j = 0; j < size; j++) {
                if (i % 2 == 0) {
                    if (j % 2 != 0) cout << " + ";
                    else cout << " - ";
                }
                else {
                    if (j % 2 != 0) cout << " - ";
                    else cout << " + ";
                }
            }
            cout << endl;
        }
    }

    void DrawBoard(int size, char playerOneColor, char playerTwoColor) {
        for (int i = 0; i < size; i++) {
            for (int j = 0; j < size; j++) {
                if (i % 2 == 0) {
                    if (j % 2 != 0) cout << " + ";
                    else cout << " - ";
                }
                else {
                    if (j % 2 != 0) cout << " - ";
                    else cout << " + ";
                }
            }
            cout << endl;
        }
    }
};

struct Player {
    char playerColor;
    vector<Piece> pieces;
    void SetupPieces(char color, bool isPlayerOne){/*, int boardSize, int rowsOfPieces, bool isPlayerOne) {*/
        playerColor = color;
            for (int i = 0; i < 8; i++) {
                for (int j = 0; j < 3; j++) {
                    if (i % 2 == 0) {
                        if (j % 2 != 0) {
                            Piece newPiece = isPlayerOne? Piece(color, i+3, j, false) : Piece(color, i, j,false);
                            pieces.push_back(newPiece);
                        }
                    }
                    else {
                        if (j % 2 == 0) {
                            Piece newPiece = isPlayerOne? Piece(color, i+3, j, false) : Piece(color,i,j, false);
                            pieces.push_back(newPiece);
                        }
                    }
                }
            }
    }
};

int main()
{
    cout << "Welcome to the Game of Checkers!" << "\n\n";
    int boardSize = 8;
    Board gameBoard;
    gameBoard.DrawBoardWithoutPieces(8);
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
