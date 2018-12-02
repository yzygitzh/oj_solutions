class Solution {
public:
    int coinChange(vector<int>& coins, int amount) {
        // minNum[M][N]: mininum coins needed to sum up M using first N coins
        // minNum[M][N] = min(minNum[M][N-1], minNum[M-val(N)][N])
        
        if (amount < 0) return -1;
        if (amount == 0) return 0;
        int coinsLen = coins.size();
        if (coinsLen == 0) return -1;
        
        vector<int> minNum(amount + 1, 0x1FFFFFFF);
        minNum[0] = 0;
        for (int i = 1; i <= coinsLen; i++) {
            for (int j = 1; j <= amount; j++) {
                if (j - coins[i - 1] >= 0 &&
                    minNum[j - coins[i - 1]] + 1 < minNum[j]) {
                    minNum[j] = minNum[j - coins[i - 1]] + 1;
                }
            }
        }
        
        if (minNum[amount] == 0x1FFFFFFF) return -1;
        else return minNum[amount];
    }
};