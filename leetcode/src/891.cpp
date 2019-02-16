class Solution {
public:
    int sumSubseqWidths(vector<int>& A) {
        int ALen = A.size();
        sort(A.begin(), A.end());
        
        vector<long long> pow2s(ALen + 1, 1);
        for (int i = 1; i <= ALen; i++) {
            pow2s[i] = 2 * pow2s[i - 1];
            pow2s[i] %= 1000000007LL;
        }
        
        long long result = 0;
        for (int i = 0; i + 1 < ALen; i++) {
            // pow2s - 1 - numOfSingleElements
            long long leftCnt = i >= 1 ? (pow2s[i + 1] - 1) - (i + 1) : 0;
            leftCnt = (leftCnt + 1000000007LL) % 1000000007LL;
            long long rightCnt = i + 2 < ALen ? (pow2s[ALen - i - 1] - 1) -
                                                (ALen - i - 1) : 0;
            rightCnt = (rightCnt + 1000000007LL) % 1000000007LL;
            long long totalCnt = ((pow2s[ALen] - 1) - ALen - leftCnt - rightCnt +
                                  1000000007LL * 4) % 1000000007LL;
            result += totalCnt * (long long)(A[i + 1] - A[i]);
            result %= 1000000007LL;
        }
        
        return (int)result;
    }
};