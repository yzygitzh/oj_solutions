class Solution {
public:
    int ALen;
    
    int bitCnt(int x) {
        int count = 0;
        while (x) {
            count += (x & 1);
            x >>= 1;
        }
        return count;
    }
    
    bool isPerfectSquare(long long x, long long y) {
        long long sqrSum = (long long)(sqrt(x + y));
        return x + y == sqrSum * sqrSum;
    }
    
    // chosenSet, lastChosen
    vector<vector<int>> memo;
    
    int numSquarefulPerms(vector<int>& A) {
        // state DP, halmiton path
        ALen = A.size();
        memo = vector<vector<int>>(1 << ALen, vector<int>(ALen, -1));
        unordered_map<int, int> lastChosenToCnt;
        for (int i = 0; i < ALen; i++) {
            lastChosenToCnt[A[i]] = dfs((1 << ALen) - 1, i, A);
        }
        int cntSum = 0;
        for (auto itr = lastChosenToCnt.begin(); itr != lastChosenToCnt.end(); ++itr) {
            cntSum += itr->second;
        }
        return cntSum;
    }
    
    int dfs(int chosenSet, int lastChosen, vector<int>& A) {
        if (memo[chosenSet][lastChosen] == -1) {
            if (bitCnt(chosenSet) == 1) {
                memo[chosenSet][lastChosen] = 1;
            } else {
                int newChosenSet = chosenSet ^ (1 << lastChosen);
                unordered_map<int, int> lastChosenToCnt;
                for (int i = 0; i < ALen; i++) {
                    if ((newChosenSet & (1 << i)) &&
                        isPerfectSquare(A[i], A[lastChosen])) {
                        lastChosenToCnt[A[i]] = dfs(newChosenSet, i, A);
                    }
                }
                int cntSum = 0;
                for (auto itr = lastChosenToCnt.begin(); itr != lastChosenToCnt.end(); ++itr) {
                    cntSum += itr->second;
                }
                memo[chosenSet][lastChosen] = cntSum;
            }
        }
        return memo[chosenSet][lastChosen];
    }
};