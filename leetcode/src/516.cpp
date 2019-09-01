class Solution {
public:
    int longestPalindromeSubseq(string s) {
        if (s.length() == 0) {
            return 0;
        }
        vector<vector<int>> longest(s.length(), vector<int>(s.length(), 1));
        for (int len = 2; len <= s.length(); len++) {
            for (int i = 0; i + len - 1 < s.length(); i++) {
                longest[i][i + len - 1] = max(longest[i][i + len - 2],
                                              longest[i + 1][i + len - 1]);
                if (len >= 2 && s[i] == s[i + len - 1]) {
                    longest[i][i + len - 1] = max(longest[i][i + len - 1],
                                                  len == 2 ?
                                                  2 : longest[i + 1][i + len - 2] + 2);
                }
            }
        }
        return longest[0][s.length() - 1];
    }
};