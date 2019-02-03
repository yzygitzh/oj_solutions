class Solution {
public:
    string smallestGoodBase(string n) {
        // (b^n - 1) / (b - 1) = b^0 + b^1 + ... + b^(n-1) = p
        // enumerate 1 length (n)
        // then binary search b
        stringstream ss;
        unsigned long long lN;
        ss << n;
        ss >> lN;
        for (int oneLen = 64; oneLen >= 1; oneLen--) {
            unsigned long long leftK = 2, rightK = 1000000000000000000ULL;
            __uint128_t sum, currPow;
            while (leftK + 1 < rightK) {
                sum = 0, currPow = 1;
                __uint128_t mid = (leftK + rightK) / 2;
                for (int i = 0; i <= oneLen - 1 && sum < (__uint128_t)lN; i++) {
                    sum += currPow;
                    currPow *= mid;
                }
                if (sum < (__uint128_t)lN) {
                    leftK = mid;
                } else {
                    rightK = mid;
                }
            }
            sum = 0, currPow = 1;
            for (int i = 0; i <= oneLen - 1; i++) {
                sum += currPow;
                currPow *= leftK;
            }
            if (sum == (__uint128_t)lN) return to_string(leftK);
            sum = 0, currPow = 1;
            for (int i = 0; i <= oneLen - 1; i++) {
                sum += currPow;
                currPow *= rightK;
            }
            if (sum == (__uint128_t)lN) return to_string(rightK);
        }
        return "";
    }
};