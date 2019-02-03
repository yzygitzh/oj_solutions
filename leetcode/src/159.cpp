class Solution {
public:
    int lengthOfLongestSubstringTwoDistinct(string s) {
        // two pointers
        int sLen = s.length();
        int result = 0;
        
        map<char, int> charCnt;
        int left = 0, right = 0;
        while (right < sLen) {
            charCnt[s[right]]++;
            while (charCnt.size() > 2) {
                charCnt[s[left]]--;
                if (charCnt[s[left]] == 0) charCnt.erase(s[left]);
                left++;
            }
            result = max(result, right - left + 1);
            right++;
        }
        
        return result;
    }
};