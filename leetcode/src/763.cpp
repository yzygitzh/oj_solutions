class Solution {
public:
    vector<int> partitionLabels(string S) {
        vector<vector<int>> charToIndices(26);
        for (int i = 0; i < S.length(); i++) {
            charToIndices[S[i] - 'a'].push_back(i);
        }
        vector<int> result;
        int idx = 0, lowerBound = 0, upperBound = 0;
        while (idx < S.length()) {
            upperBound = max(upperBound, charToIndices[S[idx] - 'a'].back());
            if (idx == upperBound) {
                result.push_back(upperBound - lowerBound + 1);
                lowerBound = upperBound = idx + 1;
            }
            idx++;
        }
        return result;
    }
};