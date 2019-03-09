class Solution {
public:
    bool isPowerOfTwo(int n) {
        long long lN = n;
        if (lN == 0) return false;
        return (lN & -lN) == lN;
    }
};