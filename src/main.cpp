#include "Search.h"
#include <sstream>

using namespace std;

int main() {
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