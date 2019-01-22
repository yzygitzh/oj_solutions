class Solution {
public:
    int longestValidParentheses(string s) {
        int maxLen = 0;
        int parentCnt, seqLen;
        
        int sLen = s.length();
        
        seqLen = parentCnt = 0;
        for (int i = 0; i < sLen; i++) {
            if (s[i] == '(') parentCnt++;
            else parentCnt--;
            seqLen++;
            if (parentCnt == 0) maxLen = max(seqLen, maxLen);
            else if (parentCnt < 0) seqLen = parentCnt = 0;
        }
        
        seqLen = parentCnt = 0;
        for (int i = sLen - 1; i >= 0; i--) {
            if (s[i] == ')') parentCnt++;
            else parentCnt--;
            seqLen++;
            if (parentCnt == 0) maxLen = max(seqLen, maxLen);
            else if (parentCnt < 0) seqLen = parentCnt = 0;
        }
        
        return maxLen;
    }
};