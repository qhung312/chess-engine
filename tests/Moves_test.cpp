#include <bits/stdc++.h>
#include "../src/Moves.h"
using namespace std;

const int MAX_DEPTH = 5;

stack<Board> st;
long long perft(int d) {
    if (d == 0) {
        return 1;
    }
    auto v = legalMoves(st.top());
    long long ans = 0;
    for (auto &s : v) {
        auto t = doMove(st.top(), s);
        st.push(t);
        long long res = perft(d - 1);
        ans += res;
        if (d == MAX_DEPTH) {
            printf("%s: %lld\n", s.c_str(), res);
        }
        st.pop();
    }
    return ans;
}

int main() {
    Board a = boardFromFEN("r3b3/B3rRn1/4NK1k/b3Q2B/5P2/P5R1/2N4q/4n3 w - - 0 1");
    st.push(a);
    long long ans = perft(MAX_DEPTH);
    cout << ans << '\n';
    
    cout << setprecision(15);
    double t = (double) clock() / CLOCKS_PER_SEC;
    cout << t << "s\n";
    cout << "Nodes per second: " << ans / t << '\n';
    return 0;
}