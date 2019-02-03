class Solution {
public:
    int lengthOfLongestSubstringKDistinct(string s, int k) {
        // two pointers
        int sLen = s.length();
        unordered_map<char, int> charCnt;
        int left = 0, right = 0, maxLen = 0;
        while (right < sLen) {
            charCnt[s[right]]++;
            if (charCnt.size() <= k) {
                maxLen = max(maxLen, right - left + 1);
            } else {
                while (charCnt.size() > k) {
                    charCnt[s[left]]--;
                    if (charCnt[s[left]] == 0) charCnt.erase(s[left]);
                    left++;
                }
            }
            right++;
        }
        return maxLen;
    }
};