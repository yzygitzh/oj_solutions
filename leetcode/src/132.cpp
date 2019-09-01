class Solution {
public:
    int minCut(string s) {
        if (s.length() <= 1) {
            return 0;
        }
        vector<int> minCut(s.length() + 1);
        minCut[0] = 0;
        for (int i = 1; i <= s.length(); i++) {
            minCut[i] = 0xFFFFFFF;
        }
        for (int i = 0; i < s.length(); i++) {
            // odd
            for (int j = 0; i - j >= 0 && i + j < s.length(); j++) {
                if (s[i - j] == s[i + j]) {
                    minCut[i + j + 1] = min(minCut[i + j + 1],
                                            minCut[i - j] + 1);
                } else {
                    break;
                }
            }
            // even
            for (int j = 0; i - j >= 0 && i + j + 1 < s.length(); j++) {
                if (s[i - j] == s[i + j + 1]) {
                    minCut[i + j + 2] = min(minCut[i + j + 2],
                                            minCut[i - j] + 1);
                } else {
                    break;
                }
            }
        }
        return minCut[s.length()] - 1;
    }
};