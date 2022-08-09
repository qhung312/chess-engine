#include "Board.h"
#include <sstream>
#include <random>
#include <chrono>

using namespace std;

mt19937_64 rng(chrono::steady_clock::now().time_since_epoch().count());
unsigned long long random64() {
    return rng();
}

void init_random() {
    // Initialize random numbers to create Zobrist keys
    // Performace doesn't matter, since this only runs once
    for (int i = 0; i < 64; i++) WHITEPAWN_RANDOM[i] = random64();
    for (int i = 0; i < 64; i++) WHITEKNIGHT_RANDOM[i] = random64();
    for (int i = 0; i < 64; i++) WHITEBISHOP_RANDOM[i] = random64();
    for (int i = 0; i < 64; i++) WHITEROOK_RANDOM[i] = random64();
    for (int i = 0; i < 64; i++) WHITEQUEEN_RANDOM[i] = random64();
    for (int i = 0; i < 64; i++) WHITEKING_RANDOM[i] = random64();
    
    for (int i = 0; i < 64; i++) BLACKPAWN_RANDOM[i] = random64();
    for (int i = 0; i < 64; i++) BLACKKNIGHT_RANDOM[i] = random64();
    for (int i = 0; i < 64; i++) BLACKBISHOP_RANDOM[i] = random64();
    for (int i = 0; i < 64; i++) BLACKROOK_RANDOM[i] = random64();
    for (int i = 0; i < 64; i++) BLACKQUEEN_RANDOM[i] = random64();
    for (int i = 0; i < 64; i++) BLACKKING_RANDOM[i] = random64();
    
    WHITE_TURN_RANDOM = random64();
    WKC_RANDOM = random64(); WQC_RANDOM = random64();
    BKC_RANDOM = random64(); BQC_RANDOM = random64();
    for (int i = 0; i < 8; i++) {
        EN_RANDOM[i] = random64();
    }
}

int main() {
    init_random();
    Board a = doMove(Board(), "e2e4");
    a = doMove(a, "d7d5");
    a = doMove(a, "e4d5");
    a = doMove(a, "d8d5");
    a = doMove(a, "f1c4");
    a = doMove(a, "f7f5");
    a = doMove(a, "g1f3");
    a = doMove(a, "d5d4");
    Board b = boardFromFEN("rnb1kbnr/ppp1p1pp/8/5p2/2Bq4/5N2/PPPP1PPP/RNBQK2R w KQkq - 2 5");
    cout << a << b;
    return 0;
}