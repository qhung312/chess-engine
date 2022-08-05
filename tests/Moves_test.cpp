#include <bits/stdc++.h>
#include "../src/Moves.h"
using namespace std;

int main() {
    Board a = boardFromFEN("rnbqkbnr/1ppppppp/8/p7/7P/8/PPPPPPP1/RNBQKBNR w KQkq - 0 2");
    auto v = pseudoLegal(a);
    for (auto& s : v) {
        cout << s << '\n';
    }
}
