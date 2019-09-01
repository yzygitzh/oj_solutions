class Solution {
public:
    int change(int amount, vector<int>& coins) {
        sort(coins.begin(), coins.end());
        // planNum[m][n]: exchange n amount of money using first m types of coins
        vector<vector<int>> planNum(2, vector<int>(amount + 1, 0));
        planNum[0][0] = 1;
        for (int i = 1; i <= coins.size(); i++) {
            planNum[i % 2][0] = 1;
            for (int j = 1; j <= amount; j++) {
                planNum[i % 2][j] = planNum[(i - 1) % 2][j];
                if (j - coins[i - 1] >= 0) {
                    planNum[i % 2][j] += planNum[i % 2][j - coins[i - 1]];
                }
            }
        }
        return planNum[coins.size() % 2][amount];
    }
};