class Solution {
public:
    int numberOfArithmeticSlices(vector<int>& A) {
        int result = 0;
        int ALen = A.size();
        int currArithLen = 0;
        bool inArith;

        for (int i = 2; i < ALen; i++) {
            inArith = (long long)A[i] - (long long)A[i - 1] ==
                      (long long)A[i - 1] - (long long)A[i - 2];
            if (inArith) {
                currArithLen += 1;
                result += currArithLen;
            } else {
                currArithLen = 0;
            }
        }

        return result;
    }
};