class Solution {
public:
    unordered_map<unsigned, bool> memo;
    
    bool canIWin(int maxChoosableInteger, int desiredTotal) {
        if ((maxChoosableInteger + 1) * maxChoosableInteger / 2 <
            desiredTotal) return false;
        if (desiredTotal <= 0) return true;
        return tryWin(maxChoosableInteger, desiredTotal, 0); 
    }
    
    bool tryWin(int maxInt, int rest, unsigned visited) {
        if (!memo.count(visited)) {
            for (int i = 1; i <= maxInt; i++) {
                if (!(visited & (1 << (i - 1)))) {
                    if (i >= rest) {
                        memo[visited] = true;
                        return memo[visited];
                    }
                    visited |= (1 << (i - 1));
                    int result = tryWin(maxInt, rest - i, visited);
                    visited ^= (1 << (i - 1));
                    if (result == false) {
                        memo[visited] = true;
                        return memo[visited];
                    }
                }
            }
            memo[visited] = false;
        }
        return memo[visited];
    }
};