#include <bits/stdc++.h>
#include "../src/Moves.h"
using namespace std;

int main() {
    Board a = boardFromFEN("r3kbnr/ppp2ppp/2nq4/3ppb2/2B1P2N/2P3P1/PP1P1P1P/RNBQK2R b KQkq - 0 6");
    auto v = pseudoLegal(a);
    for (auto& s : v) {
        cout << s << '\n';
    }
}
