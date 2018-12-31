class Solution {
public:
    long long getMin(long long x, long long y) {
        return x < y ? x : y;
    }
    
    int leastOpsExpressTarget(int x, int target) {
        // for any target, assume target < x^(k + 1), two ways to get it
        // 1. get target
        // 2. get x^(k + 1) - target, then use x^(k + 1) to substract it
        // pos->ways to get target, neg->ways to get x^(k + 1) - target
        
        long long lTarget = target;
        long long lX = x;
        
        long long pos = 0, neg = 0, newPos, newNeg;
        long long k = 0;

        while (lTarget) {
            long long subTarget = lTarget % lX;
            lTarget /= lX;
            
            if (k > 0) {
                // 21 = 10 * 2 + 1
                // 21 = 10 * 3 - 9
                newPos = getMin(k * subTarget + pos, k * (subTarget + 1) + neg);
                // we can also get 79
                // 79 = 10 * 8 - 1
                // 79 = 10 * 8 - (10 - 9): same as 3rd line, but worse
                // 79 = 10 * 7 + 9
                // 79 = 10 * 7 + 10 - 1: same as 1st line
                newNeg = getMin(k * (lX - subTarget) + pos, k * (lX - subTarget - 1) + neg);
            } else {
                newPos = 2 * subTarget - 1;
                newNeg = 2 * (lX - subTarget) - 1;
            }
            
            pos = newPos;
            neg = newNeg;
            k++;
        }
        
        return (int)getMin(pos, k + neg);
    }
};