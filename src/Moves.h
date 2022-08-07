#pragma once
#include "Board.h"
#include "Globals.h"

using namespace std;

/*
Generate strings in long algebraic notation that represents
pseudo-legal moves of the given board. Needs to be filtered
to check for legal moves.
*/

vector<string> pseudoLegal(const Board&);
vector<string> legalMoves(const Board&);

vector<string> moveWhitePawn(const Board&);
vector<string> moveBlackPawn(const Board&);
vector<string> moveWhiteKing(const Board&);
vector<string> moveBlackKing(const Board&);

vector<string> moveRook(bitboard, bitboard, bitboard);
vector<string> moveBishop(bitboard, bitboard, bitboard);
vector<string> moveQueen(bitboard, bitboard, bitboard);
vector<string> moveKnight(bitboard, bitboard, bitboard);

bitboard unsafe(bitboard, Side, bitboard, bitboard, bitboard, bitboard, bitboard, bitboard);
bool checked(const Board&, const Side);

// Helper function to concatenate vectors
template<typename T>
vector<T> operator+(const vector<T>&, const vector<T>&);