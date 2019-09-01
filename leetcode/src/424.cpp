class Solution {
public:
    int characterReplacement(string s, int k) {
        int charCnt[26] = {0};
        int left = 0, right = 0, maxCnt = 0;
        while (right < s.length()) {
            charCnt[s[right] - 'A']++;
            maxCnt = max(maxCnt, charCnt[s[right] - 'A']);
            right++;
            while (right - left > maxCnt + k) {
                charCnt[s[left] - 'A']--;
                left++;
            }
        }
        return min(int(s.length()), maxCnt + k);
    }
};