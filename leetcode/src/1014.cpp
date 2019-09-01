class Solution {
public:
    int maxScoreSightseeingPair(vector<int>& A) {
        int ALen = A.size(), maxVal = (1 << 31);
        set<int> prevVals;
        prevVals.insert(A[0]);
        for (int i = 1; i < ALen; i++) {
            maxVal = max(maxVal, A[i] + *prevVals.rbegin() - i);
            prevVals.insert(A[i] + i);
        }
        return maxVal;
    }
};