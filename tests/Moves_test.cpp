#include <bits/stdc++.h>
#include "../src/Moves.h"
using namespace std;

int main() {
    Board a = boardFromFEN("q7/8/6R1/8/4B3/8/2N3r1/8 w - - 0 1");
    auto v = pseudoLegal(a);
    for (auto& s : v) {
        cout << s << '\n';
    }
}
