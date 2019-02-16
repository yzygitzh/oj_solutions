class Solution {
public:
    long long gcd(long long a, long long b) {
        return b == 0 ? a : gcd(b, a % b);
    }
    
    long long lcm(long long a, long long b) {
        return a * b / gcd(a, b);
    }
    
    long long calcTotalRank(long long ARank,
                            long long A, long long B, long long lcmAB) {
        long long ANum = ARank * (long long)A;
        long long BRank = ANum / (long long)B;
        return BRank + ARank - ANum / lcmAB;
    }
    
    int nthMagicalNumber(int iN, int iA, int iB) {
        long long N = (long long)iN;
        long long A = (long long)iA, B = (long long)iB;
        long long lcmAB = lcm(A, B);
        // binary search on A rank
        long long left = 1, right = N;
        while (left + 1 < right) {
            long long mid = (left + right) / 2;
            long long rank = calcTotalRank(mid, A, B, lcmAB);
            if (rank < N) {
                left = mid;
            } else {
                right = mid;
            }
        }
        long long ANum = -1;
        if (calcTotalRank(right, A, B, lcmAB) == N) {
            ANum = right;
        } else if (calcTotalRank(left, A, B, lcmAB) == N) {
            ANum = left;
        }
        if (ANum == -1) return nthMagicalNumber(iN, iB, iA);
        return (int)((ANum * A) % (1000000007LL));
    }
};