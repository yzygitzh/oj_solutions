class Solution {
public:
    bool queryString(string S, int N) {
        int SLen = S.length();
        set<unsigned> substrNums;
        // O(31 * SLen)
        for (int i = 1; i <= min(SLen, 31); i++) {
            unsigned currNum = 0;
            for (int j = 0; j < SLen; j++) {
                currNum <<= 1;
                currNum |= S[j] - '0';
                if (j >= i) currNum &= ~(1 << i);
                // if (i == 2 && j == 3) return currNum == 2;
                if (j + 1 >= i) substrNums.insert(currNum);
            }
        }
        unsigned maxN = 0;
        for (auto u : substrNums) {
            if (u == 0) continue;
            if (maxN + 1 == u) maxN = u;
            else break;
        }
        return int(maxN) >= N;
    }
};