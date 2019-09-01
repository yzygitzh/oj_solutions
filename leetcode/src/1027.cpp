class Solution {
public:
    int longestArithSeqLength(vector<int>& A) {
        int ALen = A.size();
        // delta, length
        vector<unordered_map<int, int>> maxLen(ALen);
        for (int i = 1; i < ALen; i++) {
            for (int j = 0; j < i; j++) {
                // at least 2-length sequence
                maxLen[i][A[i] - A[j]] = 2;
                if (maxLen[j].count(A[i] - A[j])) {
                    maxLen[i][A[i] - A[j]] = max(maxLen[i][A[i] - A[j]],
                                                 maxLen[j][A[i] - A[j]] + 1);
                }
            }
        }
        int result = 1;
        for (int i = 1; i < ALen; i++) {
            for (auto itr = maxLen[i].begin(); itr != maxLen[i].end(); ++itr) {
                result = max(result, itr->second);
            }
        }
        return result;
    }
};