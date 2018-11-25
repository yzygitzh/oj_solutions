class Solution {
public:
    int lengthOfLongestSubstring(string s) {
        int sLen = s.length();
        if (sLen <= 1) return sLen;
        
        map<char, int> lastIdx;
        for (char c = 'a'; c <= 'z'; c++) {
            lastIdx[c] = -1;
        }
        vector<int> longest(sLen, 1);
        
        int maxLen = 1;
        lastIdx[s[0]] = 0;
        for (int i = 1; i < sLen; i++) {
            if (lastIdx[s[i]] < i - longest[i - 1]) {
                longest[i] = longest[i - 1] + 1;
            } else {
                longest[i] = i - lastIdx[s[i]];
            }
            if (longest[i] > maxLen) maxLen = longest[i];
            lastIdx[s[i]] = i;
        }
        
        return maxLen;
    }
};