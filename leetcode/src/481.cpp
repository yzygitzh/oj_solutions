class Solution {
public:
    int magicalString(int n) {
        // two pointers
        string magic = "122";
        int leftIdx = 2;
        while (magic.length() < n) {
            int leftDigit = magic[leftIdx] - '0';
            int fillDigit = 3 - (*magic.rbegin() - '0');
            for (int i = 0; i < leftDigit; i++) {
                magic += (char)('0' + fillDigit);
            }
            leftIdx++;
        }
        int oneCnt = 0;
        for (int i = 0; i < n; i++) {
            if (magic[i] == '1') oneCnt++;
        }
        return oneCnt;
    }
};