#pragma once
#include "Board.h"
#include "Globals.h"

using namespace std;

/*
Move generation for the engine
Each move has two attributes: the move taken and the resulting
board. Pawn movements need to be taken care of carefully.

Functions in here only generate pseudo-legal moves, which needs
to be filtered afterwards.
*/

struct Move {
    string s;
    Board b;
    Move() : s("") {}
    Move(const string& _s, const Board& _b) : s(_s), b(_b) {}
};

vector<Move> pseudoLegal(const Board&);

vector<Move> moveWhitePawn(const Board&);
vector<Move> moveBlackPawn(const Board&);
