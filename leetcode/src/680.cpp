class Solution {
public:
    bool validPalindrome(string s) {
        int sLen = s.length();
        int left = 0, right = sLen - 1;
        while (left < right) {
            if (left < right && s[left] != s[right]) break;
            left++, right--;
        }
        if (left >= right) return true;
        int oldLeft = left, oldRight = right;
        left = oldLeft + 1, right = oldRight;
        while (left < right) {
            if (left < right && s[left] != s[right]) {
                break;
            }
            left++, right--;
        }
        if (left >= right) return true;
        left = oldLeft, right = oldRight - 1;
        while (left < right) {
            if (left < right && s[left] != s[right]) {
                break;
            }
            left++, right--;
        }
        if (left >= right) return true;
        return false;
    }
};