#include "Search.h"
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
    
    Engine e = Engine();

    bool running = true;
    while (running) {
        string line;
        getline(cin, line);

        if (line.find("uci") == 0) {
            cout << "id name " << ID << '\n';
            cout << "id author " << AUTHOR << '\n';

            cout << "uciok\n";
        } else if (line.find("setoption") == 0) {
            // add some options?
        } else if (line == "isready") {
            cout << "readyok\n";
        } else if (line == "ucinewgame") {
            // add some code here?
        } else if (line.find("position") == 0) {
            stringstream ss(line);
            string command;
            ss >> command >> command; // Skip the command 'position'

            if (command == "startpos") {
                e.board = Board();
            } else {
                // Read FEN
                string placement, active, castle, en, half, full;
                ss >> placement >> active >> castle >> en >> half >> full;

                string fen = placement + " " + active + " " + castle + " " + en + " " +
                             half + " " + full;
                e.board = boardFromFEN(fen);
            }

            if (line.find("moves") == string::npos) {
                continue;
            }

            string move;
            ss >> move; // To skip the command 'move'
            while (ss >> move) {
                e.board = doMove(e.board, move);
            }
        } else if (line.find("go") == 0) {
            auto res = e.search();
            cout << "bestmove " << res.first << '\n';
        } else if (line == "quit") {
            running = false;
        } else if (line == "print") {
            cout << e.board;
        }
    }
    
    return 0;
}