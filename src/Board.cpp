#include "Board.h"

Board::Board() {
    const vector<string> b = {
        "rnbqkbnr",
        "pppppppp",
        "........",
        "........",
        "........",
        "........",
        "PPPPPPPP",
        "RNBQKBNR",
    };
    init(b);
}

Board::Board(const vector<string>& b) {
    init(b);
}

void Board::init(const vector<string>& b) {
    whiteKing = blackKing = 0;
    whiteRook = blackRook = 0;
    whiteBishop = blackBishop = 0;
    whiteQueen = blackQueen = 0;
    whiteKnight = blackKnight = 0;
    whitePawn = blackPawn = 0;
    for (int i = 0; i < 64; i++) {
        int r = i / 8, c = i % 8;
        switch(b[r][c]) {
            case 'r':
                blackRook |= 1ULL << i;
                break;
            case 'n':
                blackKnight |= 1ULL << i;
                break;
            case 'b':
                blackBishop |= 1ULL << i;
                break;
            case 'q':
                blackQueen |= 1ULL << i;
                break;
            case 'k':
                blackKing |= 1ULL << i;
                break;
            case 'p':
                blackPawn |= 1ULL << i;
                break;
            case 'R':
                whiteRook |= 1ULL << i;
                break;
            case 'N':
                whiteKnight |= 1ULL << i;
                break;
            case 'B':
                whiteBishop |= 1ULL << i;
                break;
            case 'Q':
                whiteQueen |= 1ULL << i;
                break;
            case 'K':
                whiteKing |= 1ULL << i;
                break;
            case 'P':
                whitePawn |= 1ULL << i;
                break;
        }
    }
}

ostream& operator<<(ostream& out, const Board& board) {
    vector<string> b(8, string(8, '.'));
    for (int i = 0; i < 64; i++) {
        int r = i / 8, c = i % 8;
        if (board.whiteKing >> i & 1ULL) b[r][c] = 'K';
        if (board.blackKing >> i & 1ULL) b[r][c] = 'k';
        if (board.whiteRook >> i & 1ULL) b[r][c] = 'R';
        if (board.blackRook >> i & 1ULL) b[r][c] = 'r';
        if (board.whiteBishop >> i & 1ULL) b[r][c] = 'B';
        if (board.blackBishop >> i & 1ULL) b[r][c] = 'b';
        if (board.whiteQueen >> i & 1ULL) b[r][c] = 'Q';
        if (board.blackQueen >> i & 1ULL) b[r][c] = 'q';
        if (board.whiteKnight >> i & 1ULL) b[r][c] = 'N';
        if (board.blackKnight >> i & 1ULL) b[r][c] = 'n';
        if (board.whitePawn >> i & 1ULL) b[r][c] = 'P';
        if (board.blackPawn >> i & 1ULL) b[r][c] = 'p';
    }
    for (auto& s : b) out << s << '\n';
    return out;
}

void printBitboard(ostream& out, const bitboard& b) {
    for (int i = 0; i < 64; i++) {
        out << (b >> i & 1ULL);
    }
    out << '\n';
}