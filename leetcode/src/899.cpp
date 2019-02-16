class Solution {
public:
    string orderlyQueue(string S, int K) {
        if (K >= 2) {
            sort(S.begin(), S.end());
            return S;
        } else {
            string minS = S;
            int SLen = S.length();
            for (int i = 0; i < SLen; i++) {
                minS = min(minS, S);
                S = S.substr(1) + S[0];
            }
            return minS;
        }
    }
};