class Solution {
public:
    bool isOneEditDistance(string s, string t) {
        int sLen = s.length(), tLen = t.length();
        int sIdx = 0, tIdx = 0;

        while (sIdx < sLen && tIdx < tLen && s[sIdx] == t[tIdx]) {
            sIdx++;
            tIdx++;
        }
        // no distance
        if (sIdx == sLen && tIdx == tLen) return false;
        
        if (sLen == tLen) {
            // replace
            sIdx++;
            tIdx++;
        } else if (sLen < tLen) {
            // insert
            tIdx++;
        } else {
            // remove
            sIdx++;
        }
        
        while (sIdx < sLen && tIdx < tLen && s[sIdx] == t[tIdx]) {
            sIdx++;
            tIdx++;
        }
        return (sIdx == sLen && tIdx == tLen);
    }
};