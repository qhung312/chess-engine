#pragma once
#include <string>
#include <vector>
#include <iostream>

using namespace std;
using bitboard = unsigned long long;

enum Side { BLACK, WHITE };

struct Board {
    Board();
    Board(const vector<string>&, Side, bool, bool, bool, bool, int, int, int);
    void init(const vector<string>&, Side, bool, bool, bool, bool, int, int, int);

    // Allow debugging of entire board by printing 8x8 chessboard
    friend ostream& operator<<(ostream&, const Board&);
    
    Side turnToPlay;
    
    bitboard whiteKing, blackKing;
    bitboard whiteRook, blackRook;
    bitboard whiteBishop, blackBishop;
    bitboard whiteQueen, blackQueen;
    bitboard whiteKnight, blackKnight;
    bitboard whitePawn, blackPawn;
    
    bool whiteKingCastle, blackKingCastle;
    bool whiteQueenCastle, blackQueenCastle;
    
    int enPassant; // -1 if no target available
    int halfMove;
    int fullMove;
};

Board boardFromFEN(const string&);
int convertAlgebraic(const string&);

// Allow debugging of a bitboard by printing out its bits
void printBitboard(ostream&, const bitboard&);
