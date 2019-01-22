class Solution {
public:
    int reverse(int x) {
        long long lX = x;
        int sign = lX < 0 ? -1 : 1;
        lX *= sign;
        
        long long result = 0;
        int digitLen = 0;
        while (lX) {
            result *= 10;
            result += (lX % 10);
            lX /= 10;
        }
        result *= sign;
        if (result < (long long)(1 << 31) || result >= (long long)~(1 << 31)) {
            return 0;
        } else {
            return (int)result;
        }
        
    }
};