class Solution {
public:
    int smallestRepunitDivByK(int K) {
        // enumeration, <= 100000
        int currNum = 0;
        for (int i = 1; i <= 100000; i++) {
            currNum *= 10;
            currNum += 1;
            currNum %= K;
            if (currNum == 0) return i;
        }
        return -1;
    }
};