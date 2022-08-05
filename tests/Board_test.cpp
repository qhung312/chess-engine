#include <bits/stdc++.h>
#include "../src/Board.h"
using namespace std;

int main() {
    cout << "---> Printing standard board...\n";
    Board standardBoard;
    cout << standardBoard << '\n';
    
    cout << "---> Printing binary representation of 10\n";
    printBitboard(cout, 10);
    cout << '\n';
    
    const string fen1 = "rnb1kbnr/pp3ppp/2p5/3pp3/B3P2q/5N2/PPPP1PPP/RNBQ1RK1 b kq - 3 5";
    cout << "---> Reading board from FEN " << fen1 << '\n';
    auto boardFen1 = boardFromFEN(fen1);
    cout << boardFen1 << '\n';
    
    const string fen2 = "rnb1k1nr/pppp1ppp/8/4p1B1/1b1P3q/3Q4/PPP1PPPP/RN1K1BNR b kq - 5 4";
    cout << "---> Reading board from FEN " << fen2 << '\n';
    auto boardFen2 = boardFromFEN(fen2);
    cout << boardFen2 << '\n';
}