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

vector<string> moveWhitePawn(const Board&);
vector<string> moveBlackPawn(const Board&);