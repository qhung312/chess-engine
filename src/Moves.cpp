#include "Moves.h"

vector<string> pseudoLegal(const Board& b) {
    return moveBishop(b.whiteBishop, b.whitePieces(), b.blackPieces());
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

vector<string> moveRook(bitboard r, bitboard same, bitboard diff) {
    vector<string> ans;
    bitboard empty = ~(same | diff);
    while (r) {
        int i = __builtin_ctzll(r);
        // Move up
        for (int j = i - 8; j >= 0; j -= 8) {
            if (!(same >> j & 1ULL)) ans.push_back(convert64(i) + convert64(j));
            if (!(empty >> j & 1ULL)) break;
        }
        // Move down
        for (int j = i + 8; j < 63; j += 8) {
            if (!(same >> j & 1ULL)) ans.push_back(convert64(i) + convert64(j));
            if (!(empty >> j & 1ULL)) break;
        }
        // Move left
        for (int j = i - 1; j / 8 == i / 8; j--) {
            if (!(same >> j & 1ULL)) ans.push_back(convert64(i) + convert64(j));
            if (!(empty >> j & 1ULL)) break;
        }
        // Move right
        for (int j = i + 1; j / 8 == i / 8; j++) {
            if (!(same >> j & 1ULL)) ans.push_back(convert64(i) + convert64(j));
            if (!(empty >> j & 1ULL)) break;
        }
        r ^= 1ULL << i;
    }
    return ans;
}

vector<string> moveBishop(bitboard b, bitboard same, bitboard diff) {
    vector<string> ans;
    bitboard empty = ~(same | diff);
    while (b) {
        int i = __builtin_ctzll(b);
        // Left up
        for (int x = i / 8 - 1, y = i % 8 - 1; x >= 0 && y >= 0; x--, y--) {
            int j = x * 8 + y;
            if (!(same >> j & 1ULL)) ans.push_back(convert64(i) + convert64(j));
            if (!(empty >> j & 1ULL)) break;
        }
        // Left down
        for (int x = i / 8 + 1, y = i % 8 - 1; x < 8 && y >= 0; x++, y--) {
            int j = x * 8 + y;
            if (!(same >> j & 1ULL)) ans.push_back(convert64(i) + convert64(j));
            if (!(empty >> j & 1ULL)) break;
        }
        // Right up
        for (int x = i / 8 - 1, y = i % 8 + 1; x >= 0 && y < 8; x--, y++) {
            int j = x * 8 + y;
            if (!(same >> j & 1ULL)) ans.push_back(convert64(i) + convert64(j));
            if (!(empty >> j & 1ULL)) break;
        }
        // Right down
        for (int x = i / 8 + 1, y = i % 8 + 1; x < 8 && y < 8; x++, y++) {
            int j = x * 8 + y;
            if (!(same >> j & 1ULL)) ans.push_back(convert64(i) + convert64(j));
            if (!(empty >> j & 1ULL)) break;
        }
        b ^= 1ULL << i;
    }
    return ans;
}