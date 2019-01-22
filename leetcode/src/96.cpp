class Solution {
public:
    int numTrees(int n) {
        if (n <= 0) return 0;
        long long result = 1;
        for (int i = 1; i <= n; i++) {
            result = 2 * (2 * i - 1) * result / (i + 1);
        }
        return (int)result;
    }
};