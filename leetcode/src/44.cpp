class Solution {
public:
    bool isMatch(string s, string p) {
        int sLen = s.length();
        int pLen = p.length();
        
        vector<vector<int> > F(2, vector<int>(pLen + 1, 0));
        
        F[0][0] = 1;
        for (int i = 1; i <= pLen; i++) {
            if (p[i - 1] == '*') F[0][i] = 1;
            else break;
        }

        for (int sIdx = 1; sIdx <= sLen; sIdx++) {
            F[sIdx % 2][0] = 0;
            for (int pIdx = 1; pIdx <= pLen; pIdx++) {
                F[sIdx % 2][pIdx] = 0;

                if (p[pIdx - 1] == s[sIdx - 1] || p[pIdx - 1] == '?') {
                    F[sIdx % 2][pIdx] |= F[(sIdx - 1) % 2][pIdx - 1];
                }

                if (p[pIdx - 1] == '*') {
                    F[sIdx % 2][pIdx] |= F[sIdx % 2][pIdx - 1];
                    F[sIdx % 2][pIdx] |= F[(sIdx - 1) % 2][pIdx];
                }
            }
        }
        
        return F[sLen % 2][pLen] == 1;
    }
};