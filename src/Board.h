#pragma once
#include <string>
#include <vector>
#include <iostream>

using namespace std;
using bitboard = unsigned long long;

class Board {
public:
    Board();
    Board(const vector<string>&);
    void init(const vector<string>&);
    
    // Allow debugging of entire board by printing 8x8 chessboard
    friend ostream& operator<<(ostream&, const Board&);
    
private:
    bitboard whiteKing, blackKing;
    bitboard whiteRook, blackRook;
    bitboard whiteBishop, blackBishop;
    bitboard whiteQueen, blackQueen;
    bitboard whiteKnight, blackKnight;
    bitboard whitePawn, blackPawn;
};

Board boardFromFEN(const string&);

// Allow debugging of a bitboard by printing out its bits
void printBitboard(ostream&, const bitboard&);