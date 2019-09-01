class Solution {
public:
    bool isMatch(string s, string p) {
        vector<int> pBase, isStar;
        for (int i = 0; i < p.length(); i++) {
            pBase.push_back(p[i]);
            if (i + 1 < p.length() && p[i + 1] == '*') {
                isStar.push_back(1);
                i++;
            } else {
                isStar.push_back(0);
            }
        }
        // F[m % 2][n]: first m chars of s matches first n chars of pBase
        vector<vector<int>> F(2, vector<int>(pBase.size() + 1, 0));
        F[0][0] = 1;
        for (int i = 1; i <= pBase.size(); i++) {
            if (!isStar[i - 1]) {
                break;
            }
            F[0][i] = 1;
        }
        for (int i = 1; i <= s.length(); i++) {
            F[i % 2][0] = 0;
            for (int j = 1; j <= pBase.size(); j++) {
                F[i % 2][j] = 0;
                if (isStar[j - 1]) {
                    F[i % 2][j] |= F[i % 2][j - 1];
                }
                if (isStar[j - 1] &&
                    (s[i - 1] == pBase[j - 1] || pBase[j - 1] == '.')) {
                    F[i % 2][j] |= F[(i - 1) % 2][j];
                }
                if (s[i - 1] == pBase[j - 1] || pBase[j - 1] == '.') {
                    F[i % 2][j] |= F[(i - 1) % 2][j - 1];
                }
            }
        }
        return F[s.length() % 2][pBase.size()];
    }
};