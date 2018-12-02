class Solution {
public:
    int str2num(string s) {
        int sLen = s.size();
        int sum = 0;
        for (int i = 0; i < sLen; i++) {
            sum *= 10;
            sum += s[i] - '0';
        }
        return sum;
    }
    
    int numDecodings(string s) {
        int sLen = s.size();
        if (s[0] == '0') return 0;
        if (sLen == 1) return 1;
        vector<int> ways(sLen, 0);
        ways[0] = 1;
        
        if (s[1] != '0') ways[1] += ways[0];
        int twoDigit = str2num(s.substr(0, 2));
        if (10 <= twoDigit && twoDigit <= 26) ways[1] += 1;

        for (int i = 2; i < sLen; i++) {
            if (s[i] != '0') ways[i] += ways[i - 1];
            twoDigit = str2num(s.substr(i - 1, 2));
            if (10 <= twoDigit && twoDigit <= 26) ways[i] += ways[i - 2];
        }
        return ways[sLen - 1];
    }
};