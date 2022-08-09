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

extern vector<string> pv_line;

void clearTransposition();
void storeTransposition(int, const Board&, int, int, const string&, NodeType);

void reorder_moves(vector<string>&, const string&);

struct Engine {
    int nodes_looked;
    int cur_depth;
    
    Board board;
    Engine();
    Move search(const Board&, int, int, int, bool);
    Move search();
};