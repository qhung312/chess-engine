#include <bits/stdc++.h>
#include "../src/Board.h"
using namespace std;

int main() {
    cout << "---> Printing standard board...\n";
    Board standardBoard;
    cout << standardBoard << '\n';
    
    cout << "---> Printing binary representation of 10\n";
    printBitboard(cout, 10);
    cout << '\n';
}