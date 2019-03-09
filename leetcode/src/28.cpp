class Solution {
public:
    int strStr(string haystack, string needle) {
        // do KMP
        int hLen = haystack.length(), nLen = needle.length();
        if (nLen == 0) return 0;
        if (hLen < nLen) return -1;
        // calc next array for needle
        vector<int> next(nLen);
        next[0] = -1;
        int i = 0, k = -1;
        while (i < nLen) {
            while (k >= 0 && needle[i] != needle[k]) k = next[k];
            i++, k++;
            if (i == nLen) break;
            if (needle[i] == needle[k]) next[i] = next[k];
            else next[i] = k;
        }
        // do match
        i = 0, k = 0;
        while (i < hLen && k < nLen) {
            while (k >= 0 && haystack[i] != needle[k]) k = next[k];
            i++, k++;
        }
        return k == nLen ? i - nLen : -1;
    }
};