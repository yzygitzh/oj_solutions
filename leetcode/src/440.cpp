class Solution {
public:
    long long findGap(long long n, long long low) {
        long long gap = 0, high = low + 1;
        while (low <= n) {
            gap += min(n + 1, high) - low;
            low *= 10;
            high *= 10;
        }
        return gap;
    }
    
    int findKthNumber(int n, int k) {
        int result = 1;
        k -= 1;
        while (k > 0) {
            long long gap = findGap(n, result);
            if ((long long)k >= gap) {
                result++;
                k -= (int)gap;
            } else {
                result *= 10;
                k -= 1;
            }
        }
        return result;
    }
};