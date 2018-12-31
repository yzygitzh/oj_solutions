class Solution {
public:
    int numDistinct(string s, string t) {
        int sLen = s.size(), tLen = t.size();
        if (tLen == 0) return 1;
        if (sLen == 0) return 0;
        
        // matchST[M][N]: number of matches between
        // M-prefix of s and N-prefix of t
        vector<vector<int> > matchST(2, vector<int>(tLen + 1));
        matchST[0][0] = 1;
        for (int i = 1; i <= sLen; i++) {
            matchST[i % 2][0] = 1;
            for (int j = 1; j <= tLen; j++) {
                matchST[i % 2][j] = matchST[(i - 1) % 2][j];
                if (s[i - 1] == t[j - 1]) {
                    matchST[i % 2][j] += matchST[(i - 1) % 2][j - 1];
                }
            }
        }
        
        return matchST[sLen % 2][tLen];
    }
};