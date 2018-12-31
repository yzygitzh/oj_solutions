class Solution {
public:
    int countDigitOne(int n) {
        if (n < 0) return 0;
        
        // first generate how many digits are there in all n-length numbers
        vector<long long> digitSums(32, 0);
        digitSums[0] = 1;
        long long numOfNums = 1;
        for (int i = 1; i < 16; i++) {
            numOfNums *= 10;
            digitSums[i] = digitSums[i - 1] * 10 + numOfNums;
        }
        
        long long mask = 1, lN = n, tmpN = n, nLen = 0;
        while (tmpN >= 10) {
            tmpN /= 10;
            mask *= 10;
            nLen++;
        }
        
        // 0 ~ lN
        // 23 -> 13 -> 3
        // 3 -> 2 -> 1 -> 0
        long long result = 0;
        while (lN) {
            long long currDigit = 0;
            while (lN >= mask) {
                lN -= mask;
                currDigit++;
                if (mask > 1) result += digitSums[nLen - 1];
            }
            if (currDigit >= 2) result += mask;
            else if (currDigit == 1) result += lN + 1;
            mask /= 10;
            nLen--;
        }
        return result;
    }
};