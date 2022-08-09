#include "Search.h"
#include <algorithm>
#include <cassert>

Board tt_board[TRANSPOSITION_SIZE];
bool tt_empty[TRANSPOSITION_SIZE];
int tt_depth[TRANSPOSITION_SIZE];
int tt_score[TRANSPOSITION_SIZE];
string tt_bestmove[TRANSPOSITION_SIZE];
NodeType tt_type[TRANSPOSITION_SIZE];

vector<string> pv_line;

void clearTransposition() {
    fill(tt_empty, tt_empty + TRANSPOSITION_SIZE, true);
}

void storeTransposition(int i, const Board& cur, int depth, int score, const string& bestmove, NodeType type) {
    tt_board[i] = cur;
    tt_empty[i] = false;
    tt_depth[i] = depth;
    tt_score[i] = score;
    tt_bestmove[i] = bestmove;
    tt_type[i] = type;
}

Engine::Engine() {
    board = Board();
}

void reorder_moves(vector<string>& moves, const string& s) {
    int i = find(moves.begin(), moves.end(), s) - moves.begin();
    assert(i != moves.size());
    swap(moves[i], moves.front());
}

Move Engine::search(const Board& cur, int d, int a, int b, bool follow_pv) {
    // Check if position is already stored
    int key = cur.hashKey();
    
    if (!tt_empty[key] && tt_board[key] == cur && tt_depth[key] >= d) {
        NodeType type = tt_type[key];
        if (type == EXACT) {
            return {tt_bestmove[key], tt_score[key]};
        } else if (type == GREATER_EQUAL) {
            int na = max(a, tt_score[key]);
            if (na >= b) {
                return {tt_bestmove[key], tt_score[key]};
            }
        } else {
            int nb = min(b, tt_score[key]);
            if (a >= nb) {
                return {tt_bestmove[key], tt_score[key]};
            }
        }
    }
    
    // Check for ending positions
    auto v = legalMoves(cur);
    if (v.empty()) {
        if (checked(cur, cur.turnToPlay)) {
            int score = cur.turnToPlay == WHITE ? -MATE_SCORE : MATE_SCORE;
            storeTransposition(key, cur, d, score, "", EXACT);
            return {"", score};
        } else {
            storeTransposition(key, cur, d, STALEMATE_SCORE, "", EXACT);
            return {"", STALEMATE_SCORE};
        }
    }
    
    if (d == 0) {
        int score = evaluate(cur);
        storeTransposition(key, cur, d, score, "", EXACT);
        return {"", score};
    }
    
    // Start normal search but try to follow pv first
    nodes_looked++;
    
    int pvIdx = cur_depth - d;
    bool can_pv = follow_pv && (pvIdx < pv_line.size());
    if (can_pv) reorder_moves(v, pv_line[pvIdx]);
    
    if (cur.turnToPlay == WHITE) {
        Move ans = {"", -INF};
        for (int i = 0; i < (int) v.size(); i++) {
            auto nxt = doMove(cur, v[i]);
            auto res = search(nxt, d - 1, a, b, can_pv && i == 0);
            if (res.second > ans.second) {
                ans.first = v[i];
                ans.second = res.second;
            }
            a = max(a, res.second);
            
            if (a >= b) {
                storeTransposition(key, cur, d, a, v[i], GREATER_EQUAL);
                return ans;
            }
        }
        
        storeTransposition(key, cur, d, ans.second, ans.first, EXACT);
        return ans;
    } else {
        Move ans = {"", INF};
        for (int i = 0; i < (int) v.size(); i++) {
            auto nxt = doMove(cur, v[i]);
            auto res = search(nxt, d - 1, a, b, can_pv && i == 0);
            if (res.second < ans.second) {
                ans.first = v[i];
                ans.second = res.second;
            }
            b = min(b, res.second);
            
            if (a >= b) {
                storeTransposition(key, cur, d, b, v[i], LESS_EQUAL);
                return ans;
            }
        }
        
        storeTransposition(key, cur, d, ans.second, ans.first, EXACT);
        return ans;
    }
}

Move Engine::search() {
    pv_line.clear();
    Move ans;
    
    for (cur_depth = 1; cur_depth <= SEARCH_DEPTH; cur_depth++) {
        nodes_looked = 0;
        ans = search(board, cur_depth, -INF, INF, 1);
        int nodes = nodes_looked;
        
        pv_line.clear();
        string best = ans.first;
        Board cur = board;
        while (best != "") {
            pv_line.push_back(best);
            cur = doMove(cur, best);
            best = search(cur, cur_depth - (int) pv_line.size(), -INF, INF, false).first;
        }
        
        cout << "info depth " << cur_depth << " nodes " << nodes << " pv ";
        for (auto& s : pv_line) cout << s << ' ';
        cout << '\n';
    }
    return ans;
}