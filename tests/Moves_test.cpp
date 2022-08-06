#include <bits/stdc++.h>
#include <cassert>
#include <ctime>
#include "../src/Moves.h"
using namespace std;

constexpr int MAX_DEPTH = 6;

long long ans = 0;
void recurse(Board b, int depth) {
    ans++;
    if (depth == MAX_DEPTH) return;
    auto v = legalMoves(b);
    for (auto& m : v) {
        Board nb = doMove(b, m);
        recurse(nb, depth + 1);
    }
}

int main() {
    Board a = Board();
    recurse(a, 0);
    cout << "Nodes processed: " << ans - 1 << '\n'; // Minus initial state
    cerr << (double) clock() / CLOCKS_PER_SEC << '\n';
}
