class Solution {
public:
    bool isMatch(string s, string p) {
        // F[M][N]: whether s[1:M] matches p[1:N]
        // F[M][N] = (isalpha(p[N]) && s[M] == p[N] && F[M-1][N-1]) ||
        //           (isdot(p[N]) && F[M-1][N-1]) ||
        //           (isstar(p[N]) && F[M][N-1] || s[M] == p[N] && F[M-1][N-1])
        
        int sLen = s.length();
        int pLen = p.length();
        
        string newP;
        int newPLen = 0;
        vector<int> isStar;
        for (int i = 0; i < pLen; i++) {
            newP += p[i];
            newPLen++;
            if (i + 1 < pLen && p[i + 1] == '*') {
                isStar.push_back(1);
                i++;
            } else {
                isStar.push_back(0);
            }
        }
        
        vector<vector<int> > F(2, vector<int>(newPLen + 1, 0));
        
        F[0][0] = 1;
        for (int i = 1; i <= newPLen; i++) {
            if (isStar[i - 1]) F[0][i] = 1;
            else break;
        }

        for (int sIdx = 1; sIdx <= sLen; sIdx++) {
            F[sIdx % 2][0] = 0;
            for (int pIdx = 1; pIdx <= newPLen; pIdx++) {
                F[sIdx % 2][pIdx] = 0;
                
                if (newP[pIdx - 1] == s[sIdx - 1] || newP[pIdx - 1] == '.') {
                    F[sIdx % 2][pIdx] |= F[(sIdx - 1) % 2][pIdx - 1];
                }

                if (isStar[pIdx - 1]) {
                    F[sIdx % 2][pIdx] |= F[sIdx % 2][pIdx - 1];
                    if (newP[pIdx - 1] == s[sIdx - 1] || newP[pIdx - 1] == '.') {
                        F[sIdx % 2][pIdx] |= F[(sIdx - 1) % 2][pIdx];
                    }
                }
            }
        }
        
        return F[sLen % 2][newPLen] == 1;
    }
};