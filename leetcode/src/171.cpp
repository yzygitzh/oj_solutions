class Solution {
public:
    int titleToNumber(string s) {
        long long sLen = s.length();
        long long lowCnt = 1;
        for (int i = 0; i < sLen; i++) {
            lowCnt *= 26;
        }
        long long result = 0;
        for (int i = 0; i < sLen; i++) {
            lowCnt /= 26;
            result += (int(s[i]) - 'A' + 1) * lowCnt;
        }
        return result;
    }
};