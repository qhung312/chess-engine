#pragma once
#include <vector>
#include <iostream>

using namespace std;
using bitboard = unsigned long long;
using u64 = unsigned long long; // Same type but used for Zobrist keys

const int TRANSPOSITION_SIZE = 224737;

extern u64 WHITEPAWN_RANDOM[64];
extern u64 WHITEKNIGHT_RANDOM[64];
extern u64 WHITEBISHOP_RANDOM[64];
extern u64 WHITEROOK_RANDOM[64];
extern u64 WHITEQUEEN_RANDOM[64];
extern u64 WHITEKING_RANDOM[64];

extern u64 BLACKPAWN_RANDOM[64];
extern u64 BLACKKNIGHT_RANDOM[64];
extern u64 BLACKBISHOP_RANDOM[64];
extern u64 BLACKROOK_RANDOM[64];
extern u64 BLACKQUEEN_RANDOM[64];
extern u64 BLACKKING_RANDOM[64];

extern u64 WHITE_TURN_RANDOM;
extern u64 WKC_RANDOM;
extern u64 WQC_RANDOM;
extern u64 BKC_RANDOM;
extern u64 BQC_RANDOM;
extern u64 EN_RANDOM[8];

enum Side { BLACK, WHITE };

struct Board {
    Board();
    Board(const vector<string>&, Side, bool, bool, bool, bool, int);
    void init(const vector<string>&, Side, bool, bool, bool, bool, int);
    bitboard whitePieces() const;
    bitboard blackPieces() const;
    
    bool occupied(int) const;
    bool whiteOccupied(int) const;
    bool blackOccupied(int) const;
    void set(bitboard&, int);
    void unset(int);

    // Allow debugging of entire board by printing 8x8 chessboard
    friend ostream& operator<<(ostream&, const Board&);
    friend bool operator==(const Board&, const Board&);
    
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
    
    u64 Z; // Zobrist key
    int hashKey() const;
};

u64 getZobrist(const Board&);

Board boardFromFEN(const string&);
Board doMove(const Board&, const string&);
int convertAlgebraic(const string&);
string convert64(int i);

// Allow debugging of a bitboard by printing out its bits
void printBitboard(ostream&, const bitboard&);
