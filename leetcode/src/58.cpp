class Solution {
public:
    int lengthOfLastWord(string s) {
        int wordLen = 0;
        for (auto itr = s.rbegin(); itr != s.rend(); ++itr) {
            if (*itr == ' ') {
                if (wordLen != 0) break;
            } else {
                wordLen++;
            }
        }
        return wordLen;
    }
};