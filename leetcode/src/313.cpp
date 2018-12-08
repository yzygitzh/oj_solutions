class Solution {
public:
    int nthSuperUglyNumber(int n, vector<int>& primes) {
        sort(primes.begin(), primes.end());
        int primesLen = primes.size();
        vector<int> pIdx(primesLen, 0);
        vector<int> ugly{1};
        
        for (int i = 0; i < n; i++) {
            unsigned long long finalUgly = *ugly.rbegin();
            unsigned long long minNum = ~(0LL);
            int minIdx;
            for (int j = 0; j < primesLen; j++) {
                unsigned long long uPrime, uUgly;
                while (true) {
                    uPrime = primes[j];
                    uUgly = ugly[pIdx[j]];
                    if (uPrime * uUgly <= finalUgly) pIdx[j]++;
                    else break;
                }
                if (uPrime * uUgly < minNum) {
                    minNum = uPrime * uUgly;
                    minIdx = j;
                }
            }
            ugly.push_back(primes[minIdx] * ugly[pIdx[minIdx]]);
            pIdx[minIdx]++;
        }
        
        return ugly[n - 1];
    }
};