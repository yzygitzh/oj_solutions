class Solution {
public:
    int lastRemaining(int n) {
        // if we delete k times,
        // the remaining numbers are all
        // 2^k * a + b, where a is from 1...ceil(n / 2^k)
        // we need find b
        
        // 1 2 3 4 5 6 7 8 9 10 11 12 ... 40, k = 0
        // 2 4 6 8 10 12 ... 40, k = 1
        // 2 6 10 14 ... 38, k = 2
        // 6 14 22 30 38, k = 3
        // 14 30, k = 4
        // 30, k = 5
        
        // use recurssion
        // when k is odd, left(k) = left(k - 2) + 2^(k-1)
        // when k is even, right(k) = right(k - 2) - 2^(k - 1)
        
        long long nL = n;
        int maxK = 0;
        while ((1LL << maxK) <= nL) maxK++;
        maxK--;
        
        // judge which side to delete every time
        int leftSide = 1, rightSide = n, leftLen = n;
        for (int i = 0; i < maxK; i++) {
            if (leftLen % 2) {
                // delete both sides
                leftSide += (1 << i);
                rightSide -= (1 << i);
            } else {
                if (i % 2) {
                    // delete right side
                    rightSide -= (1 << i);
                } else {
                    // delete left side
                    leftSide += (1 << i);
                }
            }
            leftLen /= 2;
        }
        
        return leftSide;
    }
};