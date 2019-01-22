class Solution {
public:
    int uniquePaths(int m, int n) {
        if (m == 0 || n == 0) return 0;
        // (m, n) = (m-1, n) + (m-1, n-1)
        // need calculate (m+n, n)
        
        int a = m + n - 2, b = m - 1;
        long long result = 1;
        for (int i = 1; i <= m - 1; i++) {
            result = result + result * (n - 1) / i;
        }
        
        return (int)result;
    }
};