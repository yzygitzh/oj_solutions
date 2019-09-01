class Solution {
public:
    bool repeatedSubstringPattern(string s) {
        int sLen = s.length();
        if (sLen <= 1) return false;
        string target = s + s;
        target = target.substr(1, target.length() - 2);
        int tLen = target.length();

        // do kmp
        int i, k;
        vector<int> next(sLen);
        next[0] = -1;
        // calc next
        i = 0, k = -1;
        while (i < sLen) {
            while (k >= 0 && s[i] != s[k]) k = next[k];
            i++, k++;
            if (i == sLen) break;
            if (s[i] == s[k]) next[i] = next[k];
            else next[i] = k;
        }
        // do matching, i for target and k for s
        i = 0, k = 0;
        while (i < tLen && k < sLen) {
            while (k >= 0 && target[i] != s[k]) k = next[k];
            i++, k++;
        }

        return k == sLen;
    }
};