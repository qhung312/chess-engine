#include "Bitwise.h"
#include "Globals.h"

bitboard north(bitboard x, bitboard same, bitboard diff) {
    bitboard mask = x;
    bitboard empty = ~(same | diff);
    mask |= (mask >> 8) & empty;
    mask |= (mask >> 8) & empty;
    mask |= (mask >> 8) & empty;
    mask |= (mask >> 8) & empty;
    mask |= (mask >> 8) & empty;
    mask |= (mask >> 8) & empty;
    mask |= (mask >> 8) & empty;
    mask |= (mask >> 8) & diff;
    return mask;
}

bitboard south(bitboard x, bitboard same, bitboard diff) {
    bitboard mask = x;
    bitboard empty = ~(same | diff);
    mask |= (mask << 8) & empty;
    mask |= (mask << 8) & empty;
    mask |= (mask << 8) & empty;
    mask |= (mask << 8) & empty;
    mask |= (mask << 8) & empty;
    mask |= (mask << 8) & empty;
    mask |= (mask << 8) & empty;
    mask |= (mask << 8) & diff;
    return mask;
}

bitboard west(bitboard x, bitboard same, bitboard diff) {
    bitboard mask = x;
    bitboard empty = ~(same | diff);
    mask |= (mask >> 1) & empty & ~COL7;
    mask |= (mask >> 1) & empty & ~COL7;
    mask |= (mask >> 1) & empty & ~COL7;
    mask |= (mask >> 1) & empty & ~COL7;
    mask |= (mask >> 1) & empty & ~COL7;
    mask |= (mask >> 1) & empty & ~COL7;
    mask |= (mask >> 1) & empty & ~COL7;
    mask |= (mask >> 1) & diff & ~COL7;
    return mask;
}

bitboard east(bitboard x, bitboard same, bitboard diff) {
    bitboard mask = x;
    bitboard empty = ~(same | diff);
    mask |= (mask << 1) & empty & ~COL0;
    mask |= (mask << 1) & empty & ~COL0;
    mask |= (mask << 1) & empty & ~COL0;
    mask |= (mask << 1) & empty & ~COL0;
    mask |= (mask << 1) & empty & ~COL0;
    mask |= (mask << 1) & empty & ~COL0;
    mask |= (mask << 1) & empty & ~COL0;
    mask |= (mask << 1) & diff & ~COL0;
    return mask;
}

bitboard northEast(bitboard x, bitboard same, bitboard diff) {
    bitboard mask = x;
    bitboard empty = ~(same | diff);
    mask |= (mask >> 7) & empty & ~COL0;
    mask |= (mask >> 7) & empty & ~COL0;
    mask |= (mask >> 7) & empty & ~COL0;
    mask |= (mask >> 7) & empty & ~COL0;
    mask |= (mask >> 7) & empty & ~COL0;
    mask |= (mask >> 7) & empty & ~COL0;
    mask |= (mask >> 7) & empty & ~COL0;
    mask |= (mask >> 7) & diff & ~COL0;
    return mask;
}

bitboard southEast(bitboard x, bitboard same, bitboard diff) {
    bitboard mask = x;
    bitboard empty = ~(same | diff);
    mask |= (mask << 9) & empty & ~COL0;
    mask |= (mask << 9) & empty & ~COL0;
    mask |= (mask << 9) & empty & ~COL0;
    mask |= (mask << 9) & empty & ~COL0;
    mask |= (mask << 9) & empty & ~COL0;
    mask |= (mask << 9) & empty & ~COL0;
    mask |= (mask << 9) & empty & ~COL0;
    mask |= (mask << 9) & diff & ~COL0;
    return mask;
}

bitboard southWest(bitboard x, bitboard same, bitboard diff) {
    bitboard mask = x;
    bitboard empty = ~(same | diff);
    mask |= (mask << 7) & empty & ~COL7;
    mask |= (mask << 7) & empty & ~COL7;
    mask |= (mask << 7) & empty & ~COL7;
    mask |= (mask << 7) & empty & ~COL7;
    mask |= (mask << 7) & empty & ~COL7;
    mask |= (mask << 7) & empty & ~COL7;
    mask |= (mask << 7) & empty & ~COL7;
    mask |= (mask << 7) & diff & ~COL7;
    return mask;
}

bitboard northWest(bitboard x, bitboard same, bitboard diff) {
    bitboard mask = x;
    bitboard empty = ~(same | diff);
    mask |= (mask >> 9) & empty & ~COL7;
    mask |= (mask >> 9) & empty & ~COL7;
    mask |= (mask >> 9) & empty & ~COL7;
    mask |= (mask >> 9) & empty & ~COL7;
    mask |= (mask >> 9) & empty & ~COL7;
    mask |= (mask >> 9) & empty & ~COL7;
    mask |= (mask >> 9) & empty & ~COL7;
    mask |= (mask >> 9) & diff & ~COL7;
    return mask;
}

bitboard rookMask(bitboard x, bitboard same, bitboard diff) {
    return (north(x, same, diff) | east(x, same, diff) |
            south(x, same, diff) | west(x, same, diff)) ^ x;
}

bitboard bishopMask(bitboard x, bitboard same, bitboard diff) {
    return (northEast(x, same, diff) | southEast(x, same, diff) |
            southWest(x, same, diff) | northWest(x, same, diff)) ^ x;
}

bitboard queenMask(bitboard x, bitboard same, bitboard diff) {
    return rookMask(x, same, diff) | bishopMask(x, same, diff);
}

bitboard knightMask(bitboard x, bitboard same) {
    bitboard mask = x;
    mask |= (x >> 15) & ~same & ~COL0;
    mask |= (x >> 6) & ~same & ~COL01;
    mask |= (x << 10) & ~same & ~COL01;
    mask |= (x << 17) & ~same & ~COL0;
    mask |= (x << 15) & ~same & ~COL7;
    mask |= (x << 6) & ~same & ~COL67;
    mask |= (x >> 10) & ~same & ~COL67;
    mask |= (x >> 17) & ~same & ~COL7;
    return mask ^ x;
}

bitboard kingMask(bitboard x, bitboard same) {
    bitboard mask = x;
    mask |= (x >> 8) & ~same;
    mask |= (x >> 7) & ~same & ~COL0;
    mask |= (x << 1) & ~same & ~COL0;
    mask |= (x << 9) & ~same & ~COL0;
    mask |= (x << 8) & ~same;
    mask |= (x << 7) & ~same & ~COL7;
    mask |= (x >> 1) & ~same & ~COL7;
    mask |= (x >> 9) & ~same & ~COL7;
    return mask ^ x;
}