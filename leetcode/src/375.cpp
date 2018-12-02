class Solution {
public:
    int getMoneyAmount(int n) {
        if (n < 1) return 0;
        vector<vector<int> > memo(n + 1, vector<int>(n + 1, -1));
        return guarantee(1, n, memo);
    }
    
    int guarantee(int left, int right, vector<vector<int> > &memo) {
        if (left == right) {
            return 0;
        } else if (memo[left][right] >= 0) {
            return memo[left][right];
        } else {
            int minCost = ~(1 << 31);
            for (int i = left; i <= right; i++) {
                int leftCost = 0, rightCost = 0, totalCost = i;
                if (i > left) leftCost = guarantee(left, i - 1, memo);
                if (i < right) rightCost = guarantee(i + 1, right, memo);
                totalCost += leftCost > rightCost ? leftCost : rightCost;
                if (totalCost < minCost) minCost = totalCost;
            }
            memo[left][right] = minCost;
            return memo[left][right];
        }
    }
};