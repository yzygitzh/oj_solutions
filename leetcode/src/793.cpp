class Solution {
public:
    long long numberOf5(long long x) {
        long long fivePower = 5, fiveCnt = 0;
        while (fivePower <= x) {
            fiveCnt += x / fivePower;
            fivePower *= 5;
        }
        return fiveCnt;
    }
    
    int preimageSizeFZF(int K) {
        // answer is 0 or 5
        // try to find the number that contains K 5's
        long long lK = K;
        long long left = 0, right = 1000000000LL * 5;
        while (left + 1 < right) {
            long long mid = left + (right - left) / 2;
            // calculate number of 5's
            if (numberOf5(mid) < lK) {
                left = mid;
            } else {
                right = mid;
            }
        }
        if (numberOf5(left) == lK) return 5;
        else if (numberOf5(right) == lK) return 5;
        else return 0;
    }
};