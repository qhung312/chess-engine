#include "Eval.h"

int evaluate(const Board& b) {
    // Evaluate a board and return its value based
    // on the Simplified Evaluation Function
    // (https://www.chessprogramming.org/Simplified_Evaluation_Function).
    auto extractBits = [&](bitboard mask) -> int {
        int ans = 0;
        while (mask) {
            int i = __builtin_ctzll(mask);
            int x = i / 8, y = i % 8;
            if      (b.whiteKing >> i & 1ULL) { ans += KING_WEIGHT + KING_POSITION_WHITE[x][y]; }
            else if (b.whiteRook >> i & 1ULL) { ans += ROOK_WEIGHT + ROOK_POSITION_WHITE[x][y]; }
            else if (b.whiteBishop >> i & 1ULL) { ans += BISHOP_WEIGHT + BISHOP_POSITION_WHITE[x][y]; }
            else if (b.whiteQueen >> i & 1ULL) { ans += QUEEN_WEIGHT + QUEEN_POSITION_WHITE[x][y]; }
            else if (b.whiteKnight >> i & 1ULL) { ans += KNIGHT_WEIGHT + KNIGHT_POSITION_WHITE[x][y]; }
            else if (b.whitePawn >> i & 1ULL) { ans += PAWN_WEIGHT + PAWN_POSITION_WHITE[x][y]; }
            
            else if (b.blackKing >> i & 1ULL) { ans -= KING_WEIGHT + KING_POSITION_BLACK[x][y]; }
            else if (b.blackRook >> i & 1ULL) { ans -= ROOK_WEIGHT + ROOK_POSITION_BLACK[x][y]; }
            else if (b.blackBishop >> i & 1ULL) { ans -= BISHOP_WEIGHT + BISHOP_POSITION_BLACK[x][y]; }
            else if (b.blackQueen >> i & 1ULL) { ans -= QUEEN_WEIGHT + QUEEN_POSITION_BLACK[x][y]; }
            else if (b.blackKnight >> i & 1ULL) { ans -= KNIGHT_WEIGHT + KNIGHT_POSITION_BLACK[x][y]; }
            else { ans -= PAWN_WEIGHT + PAWN_POSITION_BLACK[x][y]; }
            
            mask &= ~(1ULL << i);
        }
        return ans;
    };
    
    int result = extractBits(b.whiteKing) + extractBits(b.whiteRook) + 
                 extractBits(b.whiteBishop) + extractBits(b.whiteQueen) +
                 extractBits(b.whiteKnight) + extractBits(b.whitePawn) +
                 
                 extractBits(b.blackKing) + extractBits(b.blackRook) +
                 extractBits(b.blackBishop) + extractBits(b.blackQueen) +
                 extractBits(b.blackKnight) + extractBits(b.blackPawn);
                 
    return result;
}