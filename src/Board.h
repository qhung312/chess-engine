#pragma once
#include <string>
#include <vector>
#include <iostream>
#include <utility>

using namespace std;
using bitboard = unsigned long long;

enum Side { BLACK, WHITE };

struct Board {
    Board();
    Board(const vector<string>&, Side, bool, bool, bool, bool, int, int, int);
    void init(const vector<string>&, Side, bool, bool, bool, bool, int, int, int);
    bitboard whitePieces() const;
    bitboard blackPieces() const;
    
    bool occupied(int) const;
    bool whiteOccupied(int) const;
    bool blackOccupied(int) const;
    void set(bitboard&, int);
    void unset(int);

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
string convert64(int i);

// Allow debugging of a bitboard by printing out its bits
void printBitboard(ostream&, const bitboard&);
