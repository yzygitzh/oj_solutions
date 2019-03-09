class Solution {
public:
    int consecutiveNumbersSum(int N) {
        // N = k(k + 1) / 2 + k * M
        long long lN = N;
        int result = 0;
        for (long long k = 1; k * (k + 1) / 2 <= lN; k++) {
            if ((lN - k * (k + 1) / 2) % k == 0) result++;
        }
        return result;
    }
};