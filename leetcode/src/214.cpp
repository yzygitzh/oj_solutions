class Solution {
public:
  string shortestPalindrome(string s) {
    int sLen = s.length();
    if (sLen <= 1) return s;
    // calculate next
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
    // do match, from s end.
    i = sLen - 1, k = 0;
    while (i > k) {
      while (k >= 0 && s[i] != s[k]) k = next[k];
      i--, k++;
    }
    // build palindrome
    string rightHalf = s.substr(k);
    string leftHalf = rightHalf;
    reverse(leftHalf.begin(), leftHalf.end());
    if (i == k) {
      return leftHalf + rightHalf.substr(1);
    } else {
      return leftHalf + rightHalf;
    }
  }
};
