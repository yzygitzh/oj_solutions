class Solution {
public:
    int rangeBitwiseAnd(int m, int n) {
        // seek from most significant.
        // once there is difference, the lower bits are all zero.
        
        unsigned mask = 0x80000000;
        int result = 0;
        while (mask) {
            int mResult = m & mask;
            int nResult = n & mask;
            if (mResult == nResult) {
                result |= mResult;
            } else {
                break;
            }
            mask >>= 1;
        }
        
        return result;
    }
};