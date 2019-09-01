class Solution {
public:
    string convertToTitle(int n) {
        string result;
        long long lN = n;
        long long lowCnt = 26, totalCnt = 0;
        // 26 + 26*26 + 26*26*26 + ...
        while (totalCnt + lowCnt < lN) {
            totalCnt += lowCnt;
            lowCnt *= 26;
        }
        // BA: 26 + 26*1 + 1
        while (lN) {
            lowCnt /= 26;
            int delta = (lN - totalCnt + lowCnt - 1) / lowCnt - 1;
            result += 'A' + delta;
            lN -= lowCnt * (delta + 1);
            totalCnt -= lowCnt;
        }
        return result;
    }
};