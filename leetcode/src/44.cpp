class Solution {
public:
    bool isMatch(string s, string p) {
        int sLen = s.length();
        int pLen = p.length();
        
        // matchSP[M][N]: M-length prefix of s matches N-length prefix of p
        // matchSP[M][N] = p[N-1] == '?' -> matchSP[M-1][N-1]
        //                 p[N-1] == '*' -> OR(matchSP[1...M][N-1])
        //                 p[N-1] == 'a-z' -> matchSP[M-1][N-1] AND s[M-1] == p[N-1]
        
        vector<vector<int> > matchSP(sLen + 1, vector<int>(2, 0));
        matchSP[0][0] = 1; // '' matches '' but not others
        for (int i = 1; i <= pLen; i++) {
            matchSP[0][i % 2] = p[i - 1] == '*' ? matchSP[0][(i - 1) % 2] : 0;
            int starMatched = matchSP[0][(i - 1) % 2];
            for (int j = 1; j <= sLen; j++) {
                starMatched |= matchSP[j][(i - 1) % 2];
                if (p[i - 1] == '?') {
                    matchSP[j][i % 2] = matchSP[j - 1][(i - 1) % 2];
                } else if (p[i - 1] == '*') {
                    matchSP[j][i % 2] = starMatched;
                } else {
                    matchSP[j][i % 2] = s[j - 1] == p[i - 1] ? matchSP[j - 1][(i - 1) % 2] : 0;
                }
            }
        }
        return matchSP[sLen][pLen % 2];
    }
};