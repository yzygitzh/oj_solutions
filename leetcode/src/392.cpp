class Solution {
public:
    bool isSubsequence(string s, string t) {
        int sLen = s.length();
        if (sLen == 0) return true;
        int tLen = t.length();
        if (tLen < sLen) return false;
        
        int tIdx = 0, sIdx = 0;
        while (tIdx < tLen && sIdx < sLen) {
            if (s[sIdx] == t[tIdx]) {
                sIdx++;
            }
            tIdx++;
        }
        return sIdx == sLen;
    }
};