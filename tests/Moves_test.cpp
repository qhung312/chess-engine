#include <bits/stdc++.h>
#include "../src/Moves.h"
using namespace std;

constexpr int MAX_DEPTH = 4;

int perft(const Board& b, int d) {
    if (d == 0) return 1;
    int ans = 0;
    auto v = legalMoves(b);
    for (auto s : v) {
        Board nb = doMove(b, s);
        ans += perft(nb, d - 1);
    }
    return ans;
}

int main() {
    Board a = Board();
    cout << perft(a, MAX_DEPTH) << '\n';
    cout << "That took: " << (double) clock() / CLOCKS_PER_SEC << '\n';
}
