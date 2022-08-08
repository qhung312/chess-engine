#pragma once
#include "Board.h"

using namespace std;

/*
Helper functions for bitwise operations.
Generate mask of sliding pieces using dumb7fill (which should be faster than for loops)
(https://www.chessprogramming.org/Dumb7Fill)
*/

// Masks in each of the eight directions will contain the original cells that it was called from
// Need to xor those bits afterwards
bitboard north(bitboard, bitboard, bitboard);
bitboard south(bitboard, bitboard, bitboard);
bitboard west(bitboard, bitboard, bitboard);
bitboard east(bitboard, bitboard, bitboard);

bitboard northEast(bitboard, bitboard, bitboard);
bitboard southEast(bitboard, bitboard, bitboard);
bitboard southWest(bitboard, bitboard, bitboard);
bitboard northWest(bitboard, bitboard, bitboard);

// Specific functions for each pieces' movements that remove the original bits
// before returning the answer
bitboard rookMask(bitboard, bitboard, bitboard);
bitboard bishopMask(bitboard, bitboard, bitboard);
bitboard queenMask(bitboard, bitboard, bitboard);
bitboard knightMask(bitboard, bitboard);
bitboard kingMask(bitboard, bitboard);
bitboard whitePawnMask(bitboard, bitboard, bitboard, int);
bitboard blackPawnMask(bitboard, bitboard, bitboard, int);