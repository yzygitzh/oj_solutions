class Solution {
public:
    int firstUniqChar(string s) {
        int charCnt[26] = {0}, charIdx[26] = {0};
        for (int i = 0; i < s.length(); i++) {
            charCnt[s[i] - 'a']++;
            charIdx[s[i] - 'a'] = i;
        }
        int minIdx = s.length();
        for (int i = 0; i < 26; i++) {
            if (charCnt[i] == 1 && charIdx[i] < minIdx) {
                minIdx = charIdx[i];
            }
        }
        return minIdx < s.length() ? minIdx : -1;
    }
};