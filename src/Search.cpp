#include "Search.h"
#include <algorithm>
#include <cassert>

Board tt_board[TRANSPOSITION_SIZE];
bool tt_empty[TRANSPOSITION_SIZE];
int tt_depth[TRANSPOSITION_SIZE];
int tt_score[TRANSPOSITION_SIZE];
string tt_bestmove[TRANSPOSITION_SIZE];
NodeType tt_type[TRANSPOSITION_SIZE];

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

Move Engine::search(int d, int a, int b) {
    // Check if position is already stored
    Board cur = st.top();
    int key = cur.hashKey();
    
    if (!tt_empty[key] && tt_board[key] == cur && tt_depth[key] >= d) {
        NodeType type = tt_type[key];
        if (type == EXACT) {
            used_lookup++;
            return {tt_bestmove[key], tt_score[key]};
        } else if (type == GREATER_EQUAL) {
            int na = max(a, tt_score[key]);
            if (na >= b) {
                used_lookup++;
                return {tt_bestmove[key], tt_score[key]};
            }
        } else {
            int nb = min(b, tt_score[key]);
            if (a >= nb) {
                used_lookup++;
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
    
    // Start normal search
    used_lookup++;
    if (cur.turnToPlay == WHITE) {
        Move ans = {"", -INF};
        for (auto& s : v) {
            auto nxt = doMove(cur, s);
            st.push(nxt);
            
            auto res = search(d - 1, a, b);
            st.pop();
            if (res.second > ans.second) {
                ans.first = s;
                ans.second = res.second;
            }
            a = max(a, res.second);
            
            if (a >= b) {
                storeTransposition(key, cur, d, a, s, GREATER_EQUAL);
                return ans;
            }
        }
        
        storeTransposition(key, cur, d, ans.second, ans.first, EXACT);
        return ans;
    } else {
        Move ans = {"", INF};
        for (auto& s : v) {
            auto nxt = doMove(cur, s);
            st.push(nxt);
            
            auto res = search(d - 1, a, b);
            st.pop();
            if (res.second < ans.second) {
                ans.first = s;
                ans.second = res.second;
            }
            b = min(b, res.second);
            
            if (a >= b) {
                storeTransposition(key, cur, d, b, s, LESS_EQUAL);
                return ans;
            }
        }
        
        storeTransposition(key, cur, d, ans.second, ans.first, EXACT);
        return ans;
    }
}

Move Engine::search() {
    used_lookup = 0;
    if (!st.empty()) st.pop();
    st.push(board);
    return search(SEARCH_DEPTH, -INF, INF);
}