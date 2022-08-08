#include "Search.h"
#include <climits>

Move search(const Board& cur, int d, int a, int b) {
    auto v = legalMoves(cur);
    
    if (v.empty()) {
        if (checked(cur, cur.turnToPlay)) {
            return {"", cur.turnToPlay == WHITE ? -KING_WEIGHT : KING_WEIGHT};
        } else {
            return {"", 0};
        }
    }
    
    if (d == 0) {
        return {"", evaluate(cur)};
    }
    
    if (cur.turnToPlay == WHITE) {
        Move ans = {"", INT_MIN};
        for (auto& s : v) {
            auto nxt = doMove(cur, s);
            auto res = search(nxt, d - 1, a, b);
            if (res.second > ans.second) {
                ans.first = s;
                ans.second = res.second;
            }
            a = max(a, res.second);
            if (a >= b) {
                break;
            }
        }
        
        return ans;
    } else {
        Move ans = {"", INT_MAX};
        for (auto& s : v) {
            auto nxt = doMove(cur, s);
            auto res = search(nxt, d - 1, a, b);
            if (res.second < ans.second) {
                ans.first = s;
                ans.second = res.second;
            }
            b = min(b, res.second);
            if (a >= b) {
                break;
            }
        }
        
        return ans;
    }
}

Move search(const Board& cur) {
    return search(cur, SEARCH_DEPTH, INT_MIN, INT_MAX);
}