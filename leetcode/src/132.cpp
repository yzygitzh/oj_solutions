class Solution {
public:
    int getMin(int a, int b) {
        return a < b ? a : b;
    }

    int minCut(string s) {
        int sLen = s.length();
        if (sLen <= 1) return 0;
        
        vector<vector<int> > isPalin(sLen, vector<int>(sLen, 0));
        for (int i = 0; i < sLen; i++) {
            for (int j = 0; i - j >= 0 && i + j < sLen; j++) {
                if (s[i - j] == s[i + j]) isPalin[i - j][i + j] = 1;
                else break;
            }
            for (int j = 0; i - j >= 0 && i + 1 + j < sLen; j++) {
                if (s[i - j] == s[i + 1 + j]) isPalin[i - j][i + 1 + j] = 1;
                else break;
            }
        }
        
        vector<int> minCutNum(sLen, 0); // consider prefix only
        for (int i = 1; i < sLen; i++) {
            if (isPalin[0][i]) continue;
            minCutNum[i] = i;
            for (int j = 1; j <= i; j++) {
                if (isPalin[j][i]) {
                    minCutNum[i] = getMin(minCutNum[i],
                                          minCutNum[j - 1] + 1);
                }
            }
        }
        
        return minCutNum[sLen - 1];
    }
};