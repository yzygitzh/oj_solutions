/*
 * F[M]: Number of unique subsequences ended with M-th element
 * Find the largest N such that N < M and F[N] == F[M]
 * Then subsequences ended with element between N and M can be
 * extended by M-th element.
 */

class Solution {
public:
    int distinctSubseqII(string S) {
        int F[2010] = {0};
        int module = 1000000007;
        F[0] = 2; // F[-1] = 1
        for (int i = 1; i < S.length(); i++) {
            int nonIIdx = i - 1;
            while (true) {
                if (nonIIdx == 0 || S[nonIIdx] == S[i]) break;
                nonIIdx--;
            }
            
            F[i] += F[i - 1];
            F[i] %= module;            
            
            if (nonIIdx == 0) {
                if (S[0] != S[i]) {
                    F[i] += F[i - 1];
                    F[i] %= module;
                }
                else {
                    F[i] += F[i - 1] - 1;
                    F[i] %= module;
                }
            } else {
                F[i] += F[i - 1];
                F[i] %= module;
                F[i] += -F[nonIIdx - 1];
                while (F[i] < 0) F[i] += module;
                F[i] %= module;
            }
        }
        return (F[S.length() - 1] - 1) % module;
    }
};
