class Solution {
public:
    int maxTurbulenceSize(vector<int>& A) {
        int ALen = A.size();
        vector<int> tub1(ALen), tub2(ALen);
        tub1[0] = tub2[0] = 1;
        for (int i = 1; i < ALen; i++) {
            if (i % 2) {
                if (A[i - 1] < A[i]) {
                    tub2[i] = tub2[i - 1] + 1;
                } else {
                    tub2[i] = 1;
                }
                if (A[i - 1] > A[i]) {
                    tub1[i] = tub1[i - 1] + 1;
                } else {
                    tub1[i] = 1;
                }
            } else {
                if (A[i - 1] > A[i]) {
                    tub2[i] = tub2[i - 1] + 1;
                } else {
                    tub2[i] = 1;
                }
                if (A[i - 1] < A[i]) {
                    tub1[i] = tub1[i - 1] + 1;
                } else {
                    tub1[i] = 1;
                }
            }
        }
        int maxLen = 1;
        for (int i = 1; i < ALen; i++) {
            maxLen = max(maxLen, max(tub1[i], tub2[i]));
        }
        return maxLen;
    }
};