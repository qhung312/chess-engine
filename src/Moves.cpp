#include "Moves.h"
#include "Board.h"
#include "Globals.h"
#include "Bitwise.h"
#include <cassert>

vector<string> pseudoLegal(const Board& b) {
    bitboard wp = b.whitePieces();
    bitboard bp = b.blackPieces();
    if (b.turnToPlay == WHITE) {
        return moveBishop(b.whiteBishop, wp, bp) + moveRook(b.whiteRook, wp, bp) +
               moveKnight(b.whiteKnight, wp, bp) + moveQueen(b.whiteQueen, wp, bp) +
               moveWhiteKing(b) + moveWhitePawn(b);
    } else {
        return moveBishop(b.blackBishop, bp, wp) + moveRook(b.blackRook, bp, wp) +
               moveKnight(b.blackKnight, bp, wp) + moveQueen(b.blackQueen, bp, wp) +
               moveBlackKing(b) + moveBlackPawn(b);
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
    bitboard p = b.whitePawn;
    bitboard white = b.whitePieces();
    bitboard black = b.blackPieces();
    
    while (p) {
        int i = __builtin_ctzll(p);
        bitboard can = whitePawnMask(1ULL << i, white, black, b.enPassant);
        while (can) {
            int j = __builtin_ctzll(can);
            if (j < 8) {
                ans.push_back(convert64(i) + convert64(j) + "q");
                ans.push_back(convert64(i) + convert64(j) + "r");
                ans.push_back(convert64(i) + convert64(j) + "b");
                ans.push_back(convert64(i) + convert64(j) + "n");
            } else {
                ans.push_back(convert64(i) + convert64(j));
            }
            can ^= 1ULL << j;
        }
        p ^= 1ULL << i;
    }
    return ans;
}

vector<string> moveBlackPawn(const Board& b) {
    vector<string> ans;
    bitboard p = b.blackPawn;
    bitboard white = b.whitePieces();
    bitboard black = b.blackPieces();
    
    while (p) {
        int i = __builtin_ctzll(p);
        bitboard can = blackPawnMask(1ULL << i, black, white, b.enPassant);
        while (can) {
            int j = __builtin_ctzll(can);
            if (j >= 56) {
                ans.push_back(convert64(i) + convert64(j) + "q");
                ans.push_back(convert64(i) + convert64(j) + "r");
                ans.push_back(convert64(i) + convert64(j) + "b");
                ans.push_back(convert64(i) + convert64(j) + "n");
            } else {
                ans.push_back(convert64(i) + convert64(j));
            }
            can ^= 1ULL << j;
        }
        p ^= 1ULL << i;
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