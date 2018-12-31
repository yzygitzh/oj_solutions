class Solution {
public:
    int maxRotateFunction(vector<int>& A) {
        int ALen = A.size();
        if (ALen == 0) return 0;
        long long ASum = 0;
        for (int i = 0; i < ALen; i++) {
            ASum += A[i];
        }
        long long currF = 0;
        for (int i = 0; i < ALen; i++) {
            currF += i * A[i];
        }
        long long maxF = currF;
        for (int i = 1; i < ALen; i++) {
            currF = currF + ASum - ALen * A[ALen - i];
            if (currF > maxF) maxF = currF;
        }
        return maxF;
    }
};