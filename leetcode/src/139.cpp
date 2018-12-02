class Solution {
public:
    bool wordBreak(string s, vector<string>& wordDict) {
        int sLen = s.length();
        int dictSize = wordDict.size();
        if (dictSize == 0) return false;
        vector<int> breakable(sLen, 0);
        for (int i = 0; i < sLen; i++) {
            for (int j = 0; j < dictSize; j++) {
                string word = wordDict[j];
                int wordLen = word.length();
                int lastIdx = i - wordLen;
                int tryIdx = i - wordLen + 1;
                if (tryIdx >= 0 && s.substr(tryIdx, wordLen) == word &&
                    (lastIdx < 0 || breakable[lastIdx])) {
                    breakable[i] = 1;
                    break;
                }
            }
        }
        return breakable[sLen - 1] == 1;
    }
};