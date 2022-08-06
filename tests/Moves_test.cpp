#include <bits/stdc++.h>
#include "../src/Moves.h"
using namespace std;

int main() {
    Board a = boardFromFEN("rnbq1bnr/ppp1kppp/8/1B1pp3/4P3/5N2/PPPP1PPP/RNBQK2R w KQ - 2 4");
    auto ms = pseudoLegal(a);
    for (auto& m : ms) {
        cout << m << '\n';
        cout << doMove(a, m);
    }
}
