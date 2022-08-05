#include <bits/stdc++.h>
#include "../src/Moves.h"
using namespace std;

int main() {
    Board a = boardFromFEN("8/8/3q4/8/p2R2K1/4Bq2/8/3n4 w - - 0 1");
    auto v = pseudoLegal(a);
    for (auto& s : v) {
        cout << s << '\n';
    }
}
