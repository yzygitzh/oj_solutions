class Solution {
public:
    map<vector<int>, bool> memo;
    
    bool isScramble(string s1, string s2) {
        int s1Len = s1.length();
        int s2Len = s2.length();
        if (s1Len != s2Len) return false;
        if (s1Len == 0) return true;
        return isScrambleIdx(s1, 0, s1Len - 1, s2, 0, s2Len - 1);
    }
    
    bool isScrambleIdx(string &s1, int left1, int right1,
                       string &s2, int left2, int right2) {
        if (left1 == right1) {
            return s1[left1] == s2[left2];
        }
        else if (memo.find(vector<int>{left1, right1, left2, right2}) != memo.end()) {
            return memo[vector<int>{left1, right1, left2, right2}];
        } else {
            bool found = false;
            // if they are the same
            map<char, int> charCnt1, charCnt2;
            for (int i = 0; i < right1 - left1 + 1; i++) {
                charCnt1[s1[left1 + i]]++;
                charCnt2[s2[left2 + i]]++;
            }
            if (charCnt1 != charCnt2) {
                memo[vector<int>{left1, right1, left2, right2}] = false;
                return false;
            }
            
            // found non-exchanged
            for (int i = 0; i < right1 - left1; i++) {
                bool leftFound = isScrambleIdx(s1, left1, left1 + i, s2, left2, left2 + i);
                bool rightFound = isScrambleIdx(s1, left1 + i + 1, right1, s2, left2 + i + 1, right2);
                if (leftFound && rightFound) {
                    memo[vector<int>{left1, right1, left2, right2}] = true;
                    return true;
                }
            }
            // found exchanged
            for (int i = 0; i < right1 - left1; i++) {
                bool leftFound = isScrambleIdx(s1, left1, left1 + i, s2, right2 - i, right2);
                bool rightFound = isScrambleIdx(s1, left1 + i + 1, right1, s2, left2, right2 - i - 1);
                if (leftFound && rightFound) {
                    memo[vector<int>{left1, right1, left2, right2}] = true;
                    return true;
                }
            }
            
            memo[vector<int>{left1, right1, left2, right2}] = false;
            return false;
        }
    }
};