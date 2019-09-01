class Solution {
public:
    int countSubstrings(string s) {
        int result = 0;
        // odd substrings
        for (int i = 0; i < s.length(); i++) {
            for (int j = 0; i - j >= 0 && i + j < s.length(); j++) {
                if (s[i - j] == s[i + j]) {
                    result++;
                } else {
                    break;
                }
            }
        }
        // even substrings
        for (int i = 0; i < s.length(); i++) {
            for (int j = 0; i - j >= 0 && i + j + 1 < s.length(); j++) {
                if (s[i - j] == s[i + j + 1]) {
                    result++;
                } else {
                    break;
                }
            }
        }
        return result;
    }
};