#pragma once
#include "Moves.h"
#include "Eval.h"
#include <stack>

using namespace std;
using Move = pair<string, int>;

struct Engine {
    Board board;
    stack<Board> st;
    Engine();
    Move search(int, int, int);
    Move search();
};