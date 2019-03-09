class Solution {
public:
    int getAbs(int x) {
        return x < 0 ? -x : x;
    }
    
    int findRotateSteps(string ring, string key) {
        // F[M][N]: minCost to spell first M characters with ending state N
        // F[M][N] = min(F[M-1][j] + rotatingCost(j, N) + 1)
        // -1 for invalid state
        int rLen = ring.length(), kLen = key.length();
        vector<vector<int>> minCost(2, vector<int>(rLen, -1));
        
        for (int i = 0; i < rLen; i++) {
            minCost[0][i] = min(i, rLen - i);
        }
        for (int i = 1; i <= kLen; i++) {
            for (int j = 0; j < rLen; j++) {
                if (ring[j] == key[i - 1]) {
                    int currMinCost = ~(1 << 31);
                    for (int k = 0; k < rLen; k++) {
                        if (minCost[(i - 1) % 2][k] >= 0) {
                            currMinCost = min(currMinCost,
                                              minCost[(i - 1) % 2][k] +
                                              min(getAbs(j - k), rLen - getAbs(j - k)) + 1);
                        }
                    }
                    minCost[i % 2][j] = currMinCost;
                } else {
                    minCost[i % 2][j] = -1;
                }
            }
        }
        
        int result = ~(1 << 31);
        for (int i = 0; i < rLen; i++) {
            if (minCost[kLen % 2][i] >= 0) {
                result = min(result, minCost[kLen % 2][i]);
            }
        }
        
        return result;
    }
};