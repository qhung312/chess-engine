#include <bits/stdc++.h>
#include "../src/Moves.h"
using namespace std;

int main() {
    Board a = boardFromFEN("rnbqkbnr/pp3ppp/2p5/1B1pp3/4P3/5N2/PPPP1PPP/RNBQK2R w KQkq - 0 4");
    auto v = pseudoLegal(a);
    for (auto& s : v) {
        cout << s << '\n';
    }
}
