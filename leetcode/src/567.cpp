class Solution {
public:
    bool checkInclusion(string s1, string s2) {
        unordered_map<char, int> s1CharCnt, s2CharCnt;
        for (auto c : s1) {
            s1CharCnt[c]++;
        }
        int left = 0, right = 0, windowCharCnt = 0;
        while (right < s2.length()) {
            char c = s2[right];
            s2CharCnt[c]++;
            windowCharCnt++;
            right++;
            while (left < right && s2CharCnt[c] > s1CharCnt[c]) {
                s2CharCnt[s2[left]]--;
                windowCharCnt--;
                left++;
            }
            if (windowCharCnt == s1.length()) {
                return true;
            }
        }
        return s1 == "";
    }
};