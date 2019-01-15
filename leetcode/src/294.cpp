class Solution {
public:
    unordered_map<string, int> memo;
    
    bool canWin(string s) {
        return allConditions(s) == 1;
    }
    
    // -1: lose all the time
    // 0: lose or win
    // 1: win all the time
    int allConditions(string s) {
        if (memo.find(s) == memo.end()) {
            unordered_set<int> conds;
            for (int i = 0; i + 1 < s.length(); i++) {
                if (s[i] == '+' && s[i + 1] == '+') {
                    s[i] = s[i + 1] = '-';
                    conds.insert(allConditions(s));
                    s[i] = s[i + 1] = '+';
                }
            }
            if (conds.size() == 0) {
                memo[s] = -1;
            } else {
                if (conds.find(-1) != conds.end()) {
                    // opponent loses all the time if we do some step
                    memo[s] = 1;
                } else if (conds.size() == 1 && conds.find(1) != conds.end()) {
                    // opponent wins for every choice
                    memo[s] = -1;
                } else {
                    memo[s] = 0;
                }
            }
        }
        return memo[s];
    }
};