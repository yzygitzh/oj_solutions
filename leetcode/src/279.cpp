class Solution {
public:
    int numSquares(int n) {
        int maxSqrt = (int)sqrt(n);
        vector<int> leastNum(n + 1, 0x1FFFFFFF);
        leastNum[0] = 0;
        
        for (int i = 1; i <= maxSqrt; i++) {
            for (int j = 1; j <= n; j++) {
                if (j - i * i >= 0 &&
                    leastNum[j - i * i] + 1 < leastNum[j]) {
                    leastNum[j] = leastNum[j - i * i] + 1;
                }
            }
        }
        
        return leastNum[n];
    }
};