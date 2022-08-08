#include <bits/stdc++.h>
#include "../src/Search.h"

using namespace std;

int main() {
    Board a = boardFromFEN("8/6K1/1p1B1RB1/8/2Q5/2n1kP1N/3b4/4n3 w - - 0 1");
    auto best = search(a);
    cout << "Best move: " << best.first << '\n';
    
    cout << "That took: " << setprecision(12) << (double) clock() / CLOCKS_PER_SEC << "s\n";
}