class Solution {
public:
    string shortestPalindrome(string s) {
        // do kmp
        int sLen = s.length();
        if (sLen <= 1) return s;
        // calc next
        vector<int> next(sLen);
        next[0] = -1;
        int i = 0, k = -1;
        while (i < sLen) {
            while (k >= 0 && s[i] != s[k]) k = next[k];
            i++, k++;
            if (i == sLen) break;
            if (s[i] == s[k]) next[i] = next[k];
            else next[i] = k;
        }
        // do matching
        i = sLen - 1, k = 0;
        while (i > k) {
            while (k >= 0 && s[i] != s[k]) k = next[k];
            i--, k++;
        }
        string leftHalf, rightHalf;
        if (i == k) {
            rightHalf = s.substr(k + 1);
            leftHalf = rightHalf;
            reverse(leftHalf.begin(), leftHalf.end());
            return leftHalf + s[k] + rightHalf;
        } else {
            rightHalf = s.substr(k);
            leftHalf = rightHalf;
            reverse(leftHalf.begin(), leftHalf.end());
            return leftHalf + rightHalf;
        }
    }
};