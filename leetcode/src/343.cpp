class Solution {
public:
    int integerBreak(int n) {
        vector<int> maxProd(n + 1, 0);
        maxProd[1] = 1;
        for (int i = 2; i <= n; i++) {
            int currMaxProd = 0;
            for (int j = 1; j <= i - 1; j++) {
                int leftMax = maxProd[j] > j ? maxProd[j] : j;
                int rightMax = maxProd[i - j] > i - j ? maxProd[i - j] : i - j;
                int prod = leftMax * rightMax;
                if (prod > currMaxProd) currMaxProd = prod;
            }
            maxProd[i] = currMaxProd;
        }
        return maxProd[n];
    }
};