#include "Moves.h"

vector<Move> pseudoLegal(const Board& b) {
    return moveBlackPawn(b);
}

vector<Move> moveWhitePawn(const Board& b) {
    vector<Move> ans;
    bitboard white = b.whitePieces();
    bitboard black = b.blackPieces();
    bitboard empty = ~(white | black);
    
    // Capture left and right without promoting
    bitboard captureLeft = (b.whitePawn >> 9) & black & ~ROW0;
    while (captureLeft) {
        int i = __builtin_ctzll(captureLeft);
        string s = convert64(i + 9) + convert64(i);
        auto nb = b;
        nb.unset(i + 9); nb.unset(i); nb.set(nb.whitePawn, i);
        nb.halfMove = 0; nb.turnToPlay = BLACK; nb.enPassant = -1;
        ans.emplace_back(s, nb);
        captureLeft ^= 1ULL << i;
    }
    bitboard captureRight = (b.whitePawn >> 7) & black & ~ROW0;
    while (captureRight) {
        int i = __builtin_ctzll(captureRight);
        string s = convert64(i + 7) + convert64(i);
        auto nb = b;
        nb.unset(i + 7); nb.unset(i); nb.set(nb.whitePawn, i);
        nb.halfMove = 0; nb.turnToPlay = BLACK; nb.enPassant = -1;
        ans.emplace_back(s, nb);
        captureRight ^= 1ULL << i;
    }
    
    // Move 1 forward
    bitboard oneForward = (b.whitePawn >> 8) & empty & ~ROW0;
    while (oneForward) {
        int i = __builtin_ctzll(oneForward);
        string s = convert64(i + 8) + convert64(i);
        auto nb = b;
        nb.unset(i); nb.unset(i + 8); nb.set(nb.whitePawn, i);
        nb.halfMove = 0; nb.turnToPlay = BLACK; nb.enPassant = -1;
        ans.emplace_back(s, nb);
        oneForward ^= 1ULL << i;
    }
    
    // Move 2 forward
    bitboard twoForward = (b.whitePawn >> 16) & empty & (empty >> 8) & ~ROW0;
    while (twoForward) {
        int i = __builtin_ctzll(twoForward);
        string s = convert64(i + 16) + convert64(i);
        auto nb = b;
        nb.unset(i); nb.unset(i + 16); nb.set(nb.whitePawn, i);
        nb.halfMove = 0; nb.turnToPlay = BLACK; nb.enPassant = i + 8;
        ans.emplace_back(s, nb);
        twoForward ^= 1ULL << i;
    }
    
    // Left capture to promote (always queen)
    bitboard leftPromote = (b.whitePawn >> 9) & black & ROW0;
    while (leftPromote) {
        int i = __builtin_ctzll(leftPromote);
        string s = convert64(i + 9) + convert64(i) + "q";
        auto nb = b;
        nb.unset(i); nb.unset(i + 9); nb.set(nb.whiteQueen, i);
        nb.halfMove = 0; nb.turnToPlay = BLACK; nb.enPassant = -1;
        ans.emplace_back(s, nb);
        leftPromote ^= 1ULL << i;
    }
    // Right capture to promote (always queen)
    bitboard rightPromote = (b.whitePawn >> 7) & black & ROW0;
    while (rightPromote) {
        int i = __builtin_ctzll(rightPromote);
        string s = convert64(i + 7) + convert64(i) + "q";
        auto nb = b;
        nb.unset(i); nb.unset(i + 7); nb.set(nb.whiteQueen, i);
        nb.halfMove = 0; nb.turnToPlay = BLACK; nb.enPassant = -1;
        ans.emplace_back(s, nb);
        rightPromote ^= 1ULL << i;
    }
    
    // Move 1 forward to promote (always queen)
    bitboard onePromote = (b.whitePawn >> 8) & empty & ROW0;
    while (onePromote) {
        int i = __builtin_ctzll(rightPromote);
        string s = convert64(i + 8) + convert64(i);
        auto nb = b;
        nb.unset(i); nb.unset(i + 8); nb.set(nb.whiteQueen, i);
        nb.halfMove = 0; nb.turnToPlay = BLACK; nb.enPassant = -1;
        ans.emplace_back(s, nb);
        onePromote ^= 1ULL << i;
    }
    
    // en passant left and right
    if (b.enPassant != -1) {
        bitboard enLeft = (b.whitePawn >> 9) & (1ULL << b.enPassant);
        if (enLeft) {
            int i = b.enPassant;
            string s = convert64(i + 9) + convert64(i);
            auto nb = b;
            nb.unset(i + 8); nb.unset(i + 9); nb.set(nb.whitePawn, i);
            nb.halfMove = 0; nb.turnToPlay = BLACK; nb.enPassant = -1;
            ans.emplace_back(s, nb);
        }
        bitboard enRight = (b.whitePawn >> 7) & (1ULL << b.enPassant);
        if (enRight) {
            int i = b.enPassant;
            string s = convert64(i + 7) + convert64(i);
            auto nb = b;
            nb.unset(i + 7); nb.unset(i + 8); nb.set(nb.whitePawn, i);
            nb.halfMove = 0; nb.turnToPlay = BLACK; nb.enPassant = -1;
            ans.emplace_back(s, nb);
        }
    }
    
    return ans;
}

vector<Move> moveBlackPawn(const Board& b) {
    vector<Move> ans;
    bitboard white = b.whitePieces();
    bitboard black = b.blackPieces();
    bitboard empty = ~(white | black);
    
    // Capture left and right without promoting
    bitboard captureLeft = (b.blackPawn << 7) & white & ~ROW7;
    while (captureLeft) {
        int i = __builtin_ctzll(captureLeft);
        string s = convert64(i - 7) + convert64(i);
        auto nb = b;
        nb.unset(i - 7); nb.unset(i); nb.set(nb.blackPawn, i);
        nb.halfMove = 0; nb.fullMove++; nb.turnToPlay = WHITE; nb.enPassant = -1;
        ans.emplace_back(s, nb);
        captureLeft ^= 1ULL << i;
    }
    bitboard captureRight = (b.blackPawn << 9) & white & ~ROW7;
    while (captureRight) {
        int i = __builtin_ctzll(captureRight);
        string s = convert64(i - 9) + convert64(i);
        auto nb = b;
        nb.unset(i - 9); nb.unset(i); nb.set(nb.blackPawn, i);
        nb.halfMove = 0; nb.fullMove++; nb.turnToPlay = WHITE; nb.enPassant = -1;
        ans.emplace_back(s, nb);
        captureRight ^= 1ULL << i;
    }
    
    // Move 1 forward
    bitboard oneForward = (b.blackPawn << 8) & empty & ~ROW7;
    while (oneForward) {
        int i = __builtin_ctzll(oneForward);
        string s = convert64(i - 8) + convert64(i);
        auto nb = b;
        nb.unset(i - 8); nb.set(nb.blackPawn, i);
        nb.halfMove = 0; nb.fullMove++; nb.turnToPlay = WHITE; nb.enPassant = -1;
        ans.emplace_back(s, nb);
        oneForward ^= 1ULL << i;
    }
    
    // Move 2 forward
    bitboard twoForward = (b.blackPawn << 16) & empty & (empty << 8) & ROW3;
    while (twoForward) {
        int i = __builtin_ctzll(twoForward);
        string s = convert64(i - 16) + convert64(i);
        auto nb = b;
        nb.unset(i - 16); nb.set(nb.blackPawn, i);
        nb.halfMove = 0; nb.fullMove++; nb.turnToPlay = WHITE; nb.enPassant = i - 8;
        ans.emplace_back(s, nb);
        twoForward ^= 1ULL << i;
    }
    
    // Left capture to promote (always queen)
    bitboard leftPromote = (b.blackPawn << 7) & white & ROW7;
    while (leftPromote) {
        int i = __builtin_ctzll(leftPromote);
        string s = convert64(i - 7) + convert64(i) + "q";
        auto nb = b;
        nb.unset(i - 7); nb.unset(i); nb.set(nb.blackQueen, i);
        nb.halfMove = 0; nb.fullMove++; nb.turnToPlay = WHITE; nb.enPassant = -1;
        ans.emplace_back(s, nb);
        leftPromote ^= 1ULL << i;
    }
    // Right capture to promote (always queen)
    bitboard rightPromote = (b.blackPawn << 9) & white & ROW7;
    while (rightPromote) {
        int i = __builtin_ctzll(rightPromote);
        string s = convert64(i - 9) + convert64(i) + "q";
        auto nb = b;
        nb.unset(i - 9); nb.unset(i); nb.set(nb.blackQueen, i);
        nb.halfMove = 0; nb.fullMove++; nb.turnToPlay = WHITE; nb.enPassant = -1;
        ans.emplace_back(s, nb);
        rightPromote ^= 1ULL << i;
    }
    
    // En passant
    if (b.enPassant != -1) {
        bitboard enLeft = (b.blackPawn << 7) & (1ULL << b.enPassant);
        if (enLeft) {
            int i = b.enPassant;
            string s = convert64(i - 7) + convert64(i);
            auto nb = b;
            nb.unset(i - 8); nb.unset(i - 7); nb.set(nb.blackPawn, i);
            nb.halfMove = 0; nb.halfMove++; nb.turnToPlay = WHITE; nb.enPassant = -1;
            ans.emplace_back(s, nb);
        }
        bitboard enRight = (b.blackPawn << 9) & (1ULL << b.enPassant);
        if (enRight) {
            int i = b.enPassant;
            string s = convert64(i - 9) + convert64(i);
            auto nb = b;
            nb.unset(i - 9); nb.unset(i - 8); nb.set(nb.blackPawn, i);
            nb.halfMove = 0; nb.halfMove++; nb.turnToPlay = WHITE; nb.enPassant = -1;
            ans.emplace_back(s, nb);
        }
    }
    
    return ans;
}
