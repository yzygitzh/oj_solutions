class Solution {
public:
    int shortestWordDistance(vector<string>& words, string word1, string word2) {
        int wordsLen = words.size();
        int minDis = wordsLen;
        int idx = 0, lastIdx = -1;
        if (word1 == word2) {
            while (idx < wordsLen) {
                if (words[idx] == word1) {
                    if (lastIdx != -1) {
                        minDis = min(minDis, idx - lastIdx);
                    }
                    lastIdx = idx;
                }
                idx++;
            }
        } else {
            string lastWord;
            while (idx < wordsLen) {
                if (words[idx] == word1 || words[idx] == word2) {
                    if (lastIdx != -1 && lastWord != words[idx]) {
                        minDis = min(minDis, idx - lastIdx);
                    }
                    lastIdx = idx;
                    lastWord = words[idx];
                }
                idx++;
            }
        }
        return minDis;
    }
};