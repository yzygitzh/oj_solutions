class Solution {
public:
    string shortestPalindrome(string s) {
        if (s.length() == 0) return s;
        vector<int> nextArray(s.length() + 1, 0);
        nextArray[0] = -1;
        int i = 0, j = -1;
        while (i <= s.length()) {
            while (j >= 0 && s[i] != s[j]) j = nextArray[j];
            i++, j++;
            if (i == s.length() + 1) break;
            if (s[i] == s[j]) nextArray[i] = nextArray[j];
            else nextArray[i] = j;
        }
        i = s.length() - 1, j = 0;
        while (i > j) {
            while (j >= 0 && s[i] != s[j]) j = nextArray[j];
            i--, j++;
        }
        string patch = s.substr(i + j + 1);
        reverse(patch.begin(), patch.end());
        return patch + s;
    }
};