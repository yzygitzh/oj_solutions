class Solution {
public:
    int maxLen = 0;
    
    int longestSubstring(string s, int k) {
        // recursively find letters that with total number < k
        // until there is none
        // recurssion depth is maximum 26
        
        int sLen = s.length();
        if (sLen < k || k <= 0 || sLen == 0) return 0;
        
        vector<vector<int>> prefixCnt(26, vector<int>(sLen + 1, 0));
        unordered_map<char, int> letterCnt;
        for (int i = 0; i < sLen; i++) {
            letterCnt[s[i]]++;
            for (int j = 0; j < 26; j++) {
                prefixCnt[j][i + 1] = letterCnt['a' + j];
            }
        }
        findMaxLen(s, 0, s.length() - 1, prefixCnt, k);
        return maxLen;
    }
    
    void findMaxLen(string &s, int left, int right,
                    vector<vector<int>>& prefixCnt, int k) {
        if (right - left + 1 < k) return;
        // build letter cnt
        map<int, char> cntToLetter;
        for (int i = 0; i < 26; i++) {
            int count = prefixCnt[i][right + 1] - prefixCnt[i][left];
            if (count) cntToLetter[count] = (char)('a' + i);
        }
        if (cntToLetter.rbegin()->first < k) return;
        if (cntToLetter.begin()->first >= k) {
            maxLen = max(maxLen, right - left + 1);
        } else {
            char delim = cntToLetter.begin()->second;
            int currLeft = left, currRight = currLeft;
            while (currRight <= right) {
                if (s[currRight] == delim) {
                    findMaxLen(s, currLeft, currRight - 1, prefixCnt, k);
                    currLeft = currRight + 1;
                }
                currRight++;
            }
            findMaxLen(s, currLeft, currRight - 1, prefixCnt, k);
        }
    }
};