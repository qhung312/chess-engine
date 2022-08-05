#include <bits/stdc++.h>
#include "../src/Moves.h"
using namespace std;

int main() {
    auto v = pseudoLegal(boardFromFEN("rnbq1bnr/p2kpPpp/1pp5/3p4/8/8/PPPP1PPP/RNBQKBNR w KQ - 1 5"));
    for (auto& [s, b] : v) {
        cout << s << '\n' << b << '\n';
    }
}
