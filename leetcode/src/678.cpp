class Solution {
public:
    bool checkValidString(string s) {
        int sLen = s.length();
        // F[M][N]: first M characters with N more left parentheses.
        vector<vector<int>> validPrefix(2, vector<int>(sLen + 1, 0));
        validPrefix[0][0] = 1;
        for (int i = 0; i < sLen; i++) {
            for (int j = 0; j <= sLen; j++) {
                validPrefix[(i + 1) % 2][j] = 0;
            }
            for (int j = 0; j <= i; j++) {
                if (s[i] == '(' || s[i] == '*') {
                    validPrefix[(i + 1) % 2][j + 1] |= validPrefix[i % 2][j];
                }
                if (s[i] == ')' || s[i] == '*') {
                    if (j - 1 >= 0) {
                        validPrefix[(i + 1) % 2][j - 1] |= validPrefix[i % 2][j];
                    }
                }
                if (s[i] == '*') {
                    validPrefix[(i + 1) % 2][j] |= validPrefix[i % 2][j];
                }
            }
        }
        return validPrefix[sLen % 2][0];
    }
};