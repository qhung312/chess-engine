#include <bits/stdc++.h>
#include "../src/Moves.h"
using namespace std;

constexpr int MAX_DEPTH = 5;

int ans = 0;
int perft(const Board& b, int d) {
    if (d == 0) {
        return 1;
    }
    auto v = legalMoves(b);
    int ans = 0;
    for (auto s : v) {
        auto nb = doMove(b, s);
        int res = perft(nb, d - 1);
        ans += res;
        if (d == MAX_DEPTH) {
            cout << s << ": " << res << '\n';
        }
    }
    return ans;
}

int main() {
    Board a = boardFromFEN("rn4nr/pp3kpp/1qp4B/4p3/3Pb1Q1/b4N2/PPP2PPP/RN3RK1 w - - 0 10");
    cout << perft(a, MAX_DEPTH) << '\n';
    cout << "That took: " << (double) clock() / CLOCKS_PER_SEC << "s\n";
    return 0;
}