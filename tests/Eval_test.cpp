#include <bits/stdc++.h>
#include "../src/Eval.h"

using namespace std;

int main() {
    cout << "--> Evaluating starting board: " << evaluate(Board()) << '\n';
    
    const string fen1 = "r1bqkb1r/ppp1pppp/2n2n2/3p4/4P3/2N2N2/PPPP1PPP/R1BQKB1R w KQkq - 4 4";
    cout << "---> Evaluating board from FEN\n";
    cout << fen1 << ": " << evaluate(boardFromFEN(fen1)) << '\n';
    
    const string fen2 = "r1b1kb1r/pppNpppp/2n2n2/3p4/4P3/2N5/PPPP1PPP/R1BQKB1R b KQkq - 0 5";
    cout << fen2 << ": " << evaluate(boardFromFEN(fen2)) << '\n';
    
    const string fen3 = "r1bk1Q2/2p2p2/ppn1pN1p/3p4/4P3/2N5/PPPP1PPP/R1B1KB1R b KQ - 0 10";
    cout << fen3 << ": " << evaluate(boardFromFEN(fen3)) << '\n';
    
    const string fen4 = "N1b2b2/5p1Q/ppnk4/4p3/4P3/2N5/PPPP1PPP/R1B1KB1R b KQ - 0 13";
    cout << fen4 << ": " << evaluate(boardFromFEN(fen4)) << '\n';
    
    const string fen5 = "rnbqkbnr/pppppppp/8/8/4P3/8/PPPP1PPP/RNBQKBNR b KQkq - 0 1";
    cout << fen5 << ": " << evaluate(boardFromFEN(fen5)) << '\n';
}