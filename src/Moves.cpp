#include "Moves.h"
#include "Board.h"
#include "Globals.h"
#include "Bitwise.h"
#include <cassert>

vector<string> pseudoLegal(const Board& b) {
    bitboard wp = b.whitePieces();
    bitboard bp = b.blackPieces();
    if (b.turnToPlay == WHITE) {
        return moveWhitePawn(b) + moveRook(b.whiteRook, wp, bp) +
               moveBishop(b.whiteBishop, wp, bp) + moveQueen(b.whiteQueen, wp, bp) +
               moveWhiteKing(b) + moveKnight(b.whiteKnight, wp, bp);
    } else {
        return moveBlackPawn(b) + moveRook(b.blackRook, bp, wp) +
               moveBishop(b.blackBishop, bp, wp) + moveQueen(b.blackQueen, bp, wp) +
               moveBlackKing(b) + moveKnight(b.blackKnight, bp, wp);
    }
}

vector<string> legalMoves(const Board& b) {
    auto moves = pseudoLegal(b);
    vector<string> ans;
    for (auto& s : moves) {
        Board nb = doMove(b, s);
        if (checked(nb, b.turnToPlay)) {
            continue;
        }
        ans.push_back(s);
    }
    return ans;
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
    bitboard twoForward = (b.whitePawn >> 16) & empty & (empty >> 8) & ROW4;
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
        int i = __builtin_ctzll(onePromote);
        ans.push_back(convert64(i + 8) + convert64(i) + "q");
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
    // move once to promote (always queen)
    bitboard onePromote = (b.blackPawn << 8) & empty & ROW7;
    while (onePromote) {
        int i = __builtin_ctzll(onePromote);
        ans.push_back(convert64(i - 8) + convert64(i) + "q");
        onePromote ^= 1ULL << i;
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

vector<string> moveWhiteKing(const Board& b) {
    assert(__builtin_popcountll(b.whiteKing) == 1);
    bitboard empty = ~(b.whitePieces() | b.blackPieces());
    vector<string> ans;
    int i = __builtin_ctzll(b.whiteKing);
    bitboard can = kingMask(b.whiteKing, b.whitePieces());
    while (can) {
        int j = __builtin_ctzll(can);
        ans.push_back(convert64(i) + convert64(j));
        can ^= 1ULL << j;
    }
    
    bitboard safe = ~unsafe(b.whitePieces(), WHITE, b.blackPawn,
                         b.blackRook, b.blackBishop, b.blackQueen,
                         b.blackKing, b.blackKnight);
                         
    if (b.whiteKingCastle) {
        if ((empty >> 61 & 1ULL) & (empty >> 62 & 1ULL)) {
            if ((safe >> 60 & 1ULL) & (safe >> 61 & 1ULL) & (safe >> 62 & 1ULL)) {
                ans.push_back("e1g1");
            }
        }
    }
    if (b.whiteQueenCastle) {
        if ((empty >> 57 & 1ULL) & (empty >> 58 & 1ULL) & (empty >> 59 & 1ULL)) {
            if ((safe >> 58 & 1ULL) & (safe >> 59 & 1ULL) & (safe >> 60 & 1ULL)) {
                ans.push_back("e1c1");
            }
        }
    }
    return ans;
}

vector<string> moveBlackKing(const Board& b) {
    assert(__builtin_popcountll(b.blackKing) == 1);
    bitboard empty = ~(b.whitePieces() | b.blackPieces());
    vector<string> ans;
    int i = __builtin_ctzll(b.blackKing);
    bitboard can = kingMask(b.blackKing, b.blackPieces());
    while (can) {
        int j = __builtin_ctzll(can);
        ans.push_back(convert64(i) + convert64(j));
        can ^= 1ULL << j;
    }
    
    bitboard safe = ~unsafe(b.blackPieces(), BLACK, b.whitePawn,
                            b.whiteRook, b.whiteBishop, b.whiteQueen,
                            b.whiteKing, b.whiteKnight);
    
    if (b.blackKingCastle) {
        if ((empty >> 5 & 1ULL) & (empty >> 6 & 1ULL)) {
            if ((safe >> 4 & 1ULL) & (safe >> 5 & 1ULL) & (safe >> 6 & 1ULL)) {
                ans.push_back("e8g8");
            }
        }
    }
    if (b.blackQueenCastle) {
        if ((empty >> 1 & 1ULL) & (empty >> 2 & 1ULL) & (empty >> 3 & 1ULL)) {
            if ((safe >> 2 & 1ULL) & (safe >> 3 & 1ULL) & (safe >> 4 & 1ULL)) {
                ans.push_back("e8c8");
            }
        }
    }
    return ans;
}

vector<string> moveRook(bitboard r, bitboard same, bitboard diff) {
    vector<string> ans;
    while (r) {
        int i = __builtin_ctzll(r);
        bitboard can = rookMask(1ULL << i, same, diff);
        while (can) {
            int j = __builtin_ctzll(can);
            ans.push_back(convert64(i) + convert64(j));
            can ^= 1ULL << j;
        }
        r ^= 1ULL << i;
    }
    return ans;
}

vector<string> moveBishop(bitboard b, bitboard same, bitboard diff) {
    vector<string> ans;
    while (b) {
        int i = __builtin_ctzll(b);
        bitboard can = bishopMask(1ULL << i, same, diff);
        while (can) {
            int j = __builtin_ctzll(can);
            ans.push_back(convert64(i) + convert64(j));
            can ^= 1ULL << j;
        }
        b ^= 1ULL << i;
    }
    return ans;
}

vector<string> moveQueen(bitboard q, bitboard same, bitboard diff) {
    vector<string> ans;
    while (q) {
        int i = __builtin_ctzll(q);
        bitboard can = queenMask(1ULL << i, same, diff);
        while (can) {
            int j = __builtin_ctzll(can);
            ans.push_back(convert64(i) + convert64(j));
            can ^= 1ULL << j;
        }
        q ^= 1ULL << i;
    }
    return ans;
}

vector<string> moveKnight(bitboard n, bitboard same, bitboard diff) {
    vector<string> ans;
    while (n) {
        int i = __builtin_ctzll(n);
        bitboard can = knightMask(1ULL << i, same);
        while (can) {
            int j = __builtin_ctzll(can);
            ans.push_back(convert64(i) + convert64(j));
            can ^= 1ULL << j;
        }
        n ^= 1ULL << i;
    }
    return ans;
}

bitboard unsafe(bitboard same, Side side, bitboard pawn,
             bitboard rook, bitboard bishop, bitboard queen,
             bitboard king, bitboard knight) {
    bitboard mask = 0;
    bitboard diff = pawn | rook | bishop | queen | king | knight;
    bitboard empty = ~(same | diff);
    
    // Pawn capture in one move. Depends on side played
    if (side == WHITE) {
        mask = (pawn << 7) & ~diff & ~COL7;
        mask |= (pawn << 9) & ~diff & ~COL0;
    } else {
        mask = (pawn >> 7) & ~diff & ~COL0;
        mask |= (pawn >> 9) & ~diff & ~COL7;
    }
    
    // Rook, bishop and queen
    mask |= rookMask(rook, diff, same);
    mask |= bishopMask(bishop, diff, same);
    mask |= queenMask(queen, diff, same);
    
    // Knights and kings
    mask |= kingMask(king, diff);
    mask |= knightMask(knight, diff);
    
    return mask;
}

bool checked(const Board& b, const Side side) {
    if (side == WHITE) {
        assert(__builtin_popcountll(b.whiteKing) == 1);
        return b.whiteKing & unsafe(b.whitePieces(), WHITE, b.blackPawn,
                                    b.blackRook, b.blackBishop, b.blackQueen,
                                    b.blackKing, b.blackKnight);
    } else {
        assert(__builtin_popcountll(b.blackKing) == 1);
        return b.blackKing & unsafe(b.blackPieces(), BLACK, b.whitePawn,
                                    b.whiteRook, b.whiteBishop, b.whiteQueen,
                                    b.whiteKing, b.whiteKnight);
    }
}

template<typename T>
vector<T> operator+(const vector<T>& a, const vector<T>& b) {
    vector<T> ans;
    ans.reserve(a.size() + b.size());
    for (auto& x : a) ans.push_back(x);
    for (auto& x : b) ans.push_back(x);
    return ans;
}