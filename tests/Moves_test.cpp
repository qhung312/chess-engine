#include <bits/stdc++.h>
#include "../src/Moves.h"
using namespace std;

int main() {
    Board a = boardFromFEN("rnbqkbnr/ppp1pppp/8/4P3/6P1/7P/PPpP1P2/RNBQKBNR b KQkq - 0 5");
    // cout << a << '\n';
    auto v = pseudoLegal(a);
    for (auto& [s, b] : v) {
        cout << s << '\n' << b << '\n';
    }
}
