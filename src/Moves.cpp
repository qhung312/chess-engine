#include "Moves.h"

vector<string> pseudoLegal(const Board& b) {
    return moveWhitePawn(b);
}

vector<string> moveWhitePawn(const Board& b) {
    vector<string> ans;
    bitboard white = b.whitePieces();
    bitboard black = b.blackPieces();
    bitboard empty = ~(white | black);
    
    // Capture left and right without promoting
    bitboard captureLeft = (b.whitePawn >> 9) & black & ~ROW0 & ~COL7;
    while (captureLeft) {
        int i = __builtin_ctzll(captureLeft);
        ans.push_back(convert64(i + 9) + convert64(i));
        captureLeft ^= 1ULL << i;
    }
    bitboard captureRight = (b.whitePawn >> 7) & black & ~ROW0 & ~COL0;
    while (captureRight) {
        int i = __builtin_ctzll(captureRight);
        ans.push_back(convert64(i + 7) + convert64(i));
        captureRight ^= 1ULL << i;
    }
    
    // Move 1 forward
    bitboard oneForward = (b.whitePawn >> 8) & empty & ~ROW0;
    while (oneForward) {
        int i = __builtin_ctzll(oneForward);
        ans.push_back(convert64(i + 8) + convert64(i));
        oneForward ^= 1ULL << i;
    }
    
    // Move 2 forward
    bitboard twoForward = (b.whitePawn >> 16) & empty & (empty >> 8) & ~ROW0;
    while (twoForward) {
        int i = __builtin_ctzll(twoForward);
        ans.push_back(convert64(i + 16) + convert64(i));
        twoForward ^= 1ULL << i;
    }
    
    // Left capture to promote (always queen)
    bitboard leftPromote = (b.whitePawn >> 9) & black & ROW0 & ~COL7;
    while (leftPromote) {
        int i = __builtin_ctzll(leftPromote);
        ans.push_back(convert64(i + 9) + convert64(i) + "q");
        leftPromote ^= 1ULL << i;
    }
    // Right capture to promote (always queen)
    bitboard rightPromote = (b.whitePawn >> 7) & black & ROW0 & ~COL0;
    while (rightPromote) {
        int i = __builtin_ctzll(rightPromote);
        ans.push_back(convert64(i + 7) + convert64(i) + "q");
        rightPromote ^= 1ULL << i;
    }
    
    // Move 1 forward to promote (always queen)
    bitboard onePromote = (b.whitePawn >> 8) & empty & ROW0;
    while (onePromote) {
        int i = __builtin_ctzll(rightPromote);
        ans.push_back(convert64(i + 8) + convert64(i));
        onePromote ^= 1ULL << i;
    }
    
    // en passant left and right
    if (b.enPassant != -1) {
        bitboard enLeft = (b.whitePawn >> 9) & (1ULL << b.enPassant) & ~COL7;
        if (enLeft) {
            int i = b.enPassant;
            ans.push_back(convert64(i + 9) + convert64(i));
        }
        bitboard enRight = (b.whitePawn >> 7) & (1ULL << b.enPassant) & ~COL0;
        if (enRight) {
            int i = b.enPassant;
            ans.push_back(convert64(i + 7) + convert64(i));
        }
    }
    
    return ans;
}

vector<string> moveBlackPawn(const Board& b) {
    vector<string> ans;
    bitboard white = b.whitePieces();
    bitboard black = b.blackPieces();
    bitboard empty = ~(white | black);
    
    // Capture left and right without promoting
    bitboard captureLeft = (b.blackPawn << 7) & white & ~ROW7 & ~COL7;
    while (captureLeft) {
        int i = __builtin_ctzll(captureLeft);
        ans.push_back(convert64(i - 7) + convert64(i));
        captureLeft ^= 1ULL << i;
    }
    bitboard captureRight = (b.blackPawn << 9) & white & ~ROW7 & ~COL0;
    while (captureRight) {
        int i = __builtin_ctzll(captureRight);
        ans.push_back(convert64(i - 9) + convert64(i));
        captureRight ^= 1ULL << i;
    }
    
    // Move 1 forward
    bitboard oneForward = (b.blackPawn << 8) & empty & ~ROW7;
    while (oneForward) {
        int i = __builtin_ctzll(oneForward);
        ans.push_back(convert64(i - 8) + convert64(i));
        oneForward ^= 1ULL << i;
    }
    
    // Move 2 forward
    bitboard twoForward = (b.blackPawn << 16) & empty & (empty << 8) & ROW3;
    while (twoForward) {
        int i = __builtin_ctzll(twoForward);
        ans.push_back(convert64(i - 16) + convert64(i));
        twoForward ^= 1ULL << i;
    }
    
    // Left capture to promote (always queen)
    bitboard leftPromote = (b.blackPawn << 7) & white & ROW7 & ~COL7;
    while (leftPromote) {
        int i = __builtin_ctzll(leftPromote);
        ans.push_back(convert64(i - 7) + convert64(i) + "q");
        leftPromote ^= 1ULL << i;
    }
    // Right capture to promote (always queen)
    bitboard rightPromote = (b.blackPawn << 9) & white & ROW7 & ~COL0;
    while (rightPromote) {
        int i = __builtin_ctzll(rightPromote);
        ans.push_back(convert64(i - 9) + convert64(i) + "q");
        rightPromote ^= 1ULL << i;
    }
    
    // En passant
    if (b.enPassant != -1) {
        bitboard enLeft = (b.blackPawn << 7) & (1ULL << b.enPassant) & ~COL7;
        if (enLeft) {
            int i = b.enPassant;
            ans.push_back(convert64(i - 7) + convert64(i));
        }
        bitboard enRight = (b.blackPawn << 9) & (1ULL << b.enPassant) & ~COL0;
        if (enRight) {
            int i = b.enPassant;
            ans.push_back(convert64(i - 9) + convert64(i));
        }
    }
    
    return ans;
}
