#include "Eval.h"

int evaluate(const Board& b) {
    // Evaluate a board and return its value based
    // on the Simplified Evaluation Function
    // (https://www.chessprogramming.org/Simplified_Evaluation_Function).
    
    auto extractBits = [&](bitboard x, int w, const vector<vector<int>>& pos) -> int {
        int ans = 0;
        while (x) {
            int lsb = __builtin_ctzll(x);
            x ^= (1ULL << lsb);
            ans += w * pos[lsb / 8][lsb % 8];
        }
        return ans;
    };
    
    int result = 0;
    result += extractBits(b.whiteKing, KING_WEIGHT, KING_POSITION_WHITE);
    result += extractBits(b.whiteRook, ROOK_WEIGHT, ROOK_POSITION_WHITE);
    result += extractBits(b.whiteBishop, BISHOP_WEIGHT, BISHOP_POSITION_WHITE);
    result += extractBits(b.whiteQueen, QUEEN_WEIGHT, QUEEN_POSITION_WHITE);
    result += extractBits(b.whiteKnight, KNIGHT_WEIGHT, KNIGHT_POSITION_WHITE);
    result += extractBits(b.whitePawn, PAWN_WEIGHT, PAWN_POSITION_WHITE);
    
    result += extractBits(b.blackKing, -KING_WEIGHT, KING_POSITION_BLACK);
    result += extractBits(b.blackRook, -ROOK_WEIGHT, ROOK_POSITION_BLACK);
    result += extractBits(b.blackBishop, -BISHOP_WEIGHT, BISHOP_POSITION_BLACK);
    result += extractBits(b.blackQueen, -QUEEN_WEIGHT, QUEEN_POSITION_BLACK);
    result += extractBits(b.blackKnight, -KNIGHT_WEIGHT, KNIGHT_POSITION_BLACK);
    result += extractBits(b.blackPawn, -PAWN_WEIGHT, PAWN_POSITION_BLACK);
    return result;
}