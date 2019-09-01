class Solution {
public:
    int maxSumTwoNoOverlap(vector<int>& A, int L, int M) {
        int maxLBeforeM = 0, maxMBeforeL = 0;
        int LBeforeM = 0, MBeforeL = 0;
        int currM = 0, currL = 0;
        int result = 0;
        for (int i = 0; i < A.size(); i++) {
            currM += A[i];
            currL += A[i];
            if (i >= M) {
                currM -= A[i - M];
                LBeforeM += A[i - M];
            }
            if (i >= L) {
                currL -= A[i - L];
                MBeforeL += A[i - L];
            }
            if (i >= M + L) {
                LBeforeM -= A[i - M - L];
                MBeforeL -= A[i - L - M];
            }
            if (i >= M + L - 1) {
                maxLBeforeM = max(maxLBeforeM, LBeforeM);
                maxMBeforeL = max(maxMBeforeL, MBeforeL);
                result = max(result, currM + maxLBeforeM);
                result = max(result, currL + maxMBeforeL);
            }
        }
        return result;
    }
};