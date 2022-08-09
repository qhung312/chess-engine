#pragma once
#include "Moves.h"
#include "Eval.h"
#include <stack>

using namespace std;
using Move = pair<string, int>;

enum NodeType { GREATER_EQUAL, LESS_EQUAL, EXACT };

extern Board tt_board[TRANSPOSITION_SIZE];
extern bool tt_empty[TRANSPOSITION_SIZE];
extern int tt_depth[TRANSPOSITION_SIZE];
extern int tt_score[TRANSPOSITION_SIZE];
extern string tt_bestmove[TRANSPOSITION_SIZE];
extern NodeType tt_type[TRANSPOSITION_SIZE];

void clearTransposition();
void storeTransposition(int, const Board&, int, int, const string&, NodeType);

struct Engine {
    int used_lookup;
    
    Board board;
    stack<Board> st;
    Engine();
    Move search(int, int, int);
    Move search();
};