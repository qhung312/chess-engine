#include "Board.h"
#include <sstream>

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
    init(b, WHITE, true, true, true, true, -1, 0, 1);
}

Board::Board(const vector<string>& b, Side side, bool wkc, bool wqc, bool bkc, bool bqc, int en, int half, int full) {
    init(b, side, wkc, wqc, bkc, bqc, en, half, full);
}

void Board::init(const vector<string>& b, Side side, bool wkc, bool wqc, bool bkc, bool bqc, int en, int half, int full) {
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
    
    turnToPlay = side;
    
    whiteKingCastle = wkc;
    whiteQueenCastle = wqc;
    blackKingCastle = bkc;
    blackQueenCastle = bqc;
    
    enPassant = en;
    halfMove = half;
    fullMove = full;
}

bitboard Board::whitePieces() const {
    return whiteKing | whiteRook |
           whiteBishop | whiteQueen |
           whiteKnight | whitePawn;
}

bitboard Board::blackPieces() const {
    return blackKing | blackRook |
           blackBishop | blackQueen |
           blackKnight | blackPawn;
}

bool Board::whiteOccupied(int i) const {
    return whitePieces() >> i & 1ULL;
}

bool Board::blackOccupied(int i) const {
    return blackPieces() >> i & 1ULL;
}

bool Board::occupied(int i) const {
    return whiteOccupied(i) | blackOccupied(i);
}

void Board::set(bitboard& b, int i) {
    if (!(b >> i & 1)) b ^= (1ULL << i);
}

void Board::unset(int i) {
    if (whiteKing >> i & 1ULL) whiteKing ^= 1ULL << i;
    if (whiteRook >> i & 1ULL) whiteRook ^= 1ULL << i;
    if (whiteBishop >> i & 1ULL) whiteBishop ^= 1ULL << i;
    if (whiteQueen >> i & 1ULL) whiteQueen ^= 1ULL << i;
    if (whiteKnight >> i & 1ULL) whiteKnight ^= 1ULL << i;
    if (whitePawn >> i & 1ULL) whitePawn ^= 1ULL << i;
    
    if (blackKing >> i & 1ULL) blackKing ^= 1ULL << i;
    if (blackRook >> i & 1ULL) blackRook ^= 1ULL << i;
    if (blackBishop >> i & 1ULL) blackBishop ^= 1ULL << i;
    if (blackQueen >> i & 1ULL) blackQueen ^= 1ULL << i;
    if (blackKnight >> i & 1ULL) blackKnight ^= 1ULL << i;
    if (blackPawn >> i & 1ULL) blackPawn ^= 1ULL << i;
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
    
    out << "Side to move: " << (board.turnToPlay == WHITE ? "White" : "Black") << '\n';
    out << "White king castle: " << (board.whiteKingCastle ? "yes" : "no") << '\n';
    out << "White queen castle: " << (board.whiteQueenCastle ? "yes" : "no") << '\n';
    out << "Black king castle: " << (board.blackKingCastle ? "yes" : "no") << '\n';
    out << "Black queen castle: " << (board.blackQueenCastle ? "yes" : "no") << '\n';
    out << "Possible en passant: " << board.enPassant << '\n';
    out << "Half moves: " << board.halfMove << '\n';
    out << "Full moves: " << board.fullMove << '\n';
    return out;
}

Board boardFromFEN(const string& fen) {
    stringstream stream(fen);
    string placement, turn, castling, enStr;
    int half, full;
    stream >> placement >> turn >> castling >> enStr >> half >> full;
    
    vector<string> board(8, string(8, '.'));
    int cur_line = 0;
    int i = 0;
    for (char c : placement) {
        if (c == '/') {
            cur_line++;
            i = 0;
            continue;
        }
        if (isdigit(c)) {
            i += c - '0';
        } else {
            board[cur_line][i] = c;
            i++;
        }
    }
    
    Side side = turn == "w" ? WHITE : BLACK;
    
    bool wkc = false, wqc = false;
    bool bkc = false, bqc = false;
    for (char c : castling) {
        wkc |= c == 'K';
        wqc |= c == 'Q';
        bkc |= c == 'k';
        bqc |= c == 'q';
    }
    
    int en = enStr == "-" ? -1 : convertAlgebraic(enStr);
    return Board(board, side, wkc, wqc, bkc, bqc, en, half, full);
}

int convertAlgebraic(const string& s) {
    int r = 8 - (s[1] - '0'), c = s[0] - 'a';
    return 8 * r + c;
}

string convert64(int i) {
    string ans(2, '.');
    ans[0] = i % 8 + 'a';
    ans[1] = '8' - (i / 8);
    return ans;
}

void printBitboard(ostream& out, const bitboard& b) {
    for (int i = 0; i < 64; i++) {
        out << (b >> i & 1ULL);
    }
    out << '\n';
}
