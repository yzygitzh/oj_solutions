class Solution {
public:
    string shortestPalindrome(string s) {
        // kmp
        int sLen = s.length();
        if (sLen <= 1) return s;
        // caculate next
        vector<int> next(sLen);
        next[0] = -1;
        int k = -1; // k is the moving point
        int idx = 0;
        while (idx < sLen) {
            while (k >= 0 && s[idx] != s[k]) k = next[k];
            idx++, k++;
            if (idx == sLen) break;
            if (s[idx] == s[k]) next[idx] = next[k];
            else next[idx] = k;
        }
        // do matching
        int left = 0, right = sLen - 1;
        while (left < right) {
            if (left == -1 || s[left] == s[right]) {
                left++;
                right--;
            } else {
                left = next[left];
            }
        }
        string leftAdd;
        if (left == right) {
            leftAdd = s.substr(left * 2 + 1);
        } else {
            leftAdd = s.substr(left * 2);
        }
        reverse(leftAdd.begin(), leftAdd.end());
        leftAdd += s;
        return leftAdd;
    }
};