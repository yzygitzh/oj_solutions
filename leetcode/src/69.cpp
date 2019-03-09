class Solution {
public:
    int mySqrt(int x) {
        long long left = 0, right = x;
        while (left + 1 < right) {
            long long mid = (left + right) / 2;
            if (mid * mid < (long long)x) {
                left = mid;
            } else {
                right = mid;
            }
        }
        if (right * right <= (long long)x) return right;
        else return left;
    }
};