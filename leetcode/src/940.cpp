class Solution {
public:
    int distinctSubseqII(string S) {
        unordered_map<char, int> endCnt;
        for (int i = 0; i < S.length(); i++) {
            int newCnt = 1; // itself
            for (auto p : endCnt) {
                newCnt += p.second;
                newCnt %= 1000000007;
            }
            endCnt[S[i]] = newCnt;
        }
        int result = 0;
        for (auto p : endCnt) {
            result += p.second;
            result %= 1000000007;
        }
        return result;
    }
};