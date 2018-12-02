class Solution {
public:
    int largestComponentSize(vector<int>& A) {
        sort(A.begin(), A.end());
        int ALen = A.size();
        
        // gen prime set
        vector<int> primes{2};
        map<int, int> prime2idx;
        prime2idx[2] = 0;
        for (int i = 3; i <= A[ALen - 1]; i++) {
            bool isPrime = true;
            for (int j = 2; j <= (int)sqrt(i); j++) {
                if (i % j == 0) {
                    isPrime = false;
                    break;
                }
            }
            if (isPrime) {
                prime2idx[i] = primes.size();
                primes.push_back(i);
            }
        }
        int primesLen = primes.size();
        set<int> primeSet(primes.begin(), primes.end());
 
        vector<int> parent(primesLen, 0);
        for (int i = 0; i < primesLen; i++) {
            parent[i] = i;
        }
        
        map<int, int> APrimeCount; // primeIdx to A's elements that having this prime as its smallest factor
        for (int i = 0; i < ALen; i++) {
            int tester = A[i];
            int primeIdx = 0;
            int firstPrimeIdx = -1;
            bool isFirstPrime = true;
            
            while (tester != 1) {
                if (primeSet.count(tester)) {
                    if (isFirstPrime) {
                        APrimeCount[prime2idx[tester]]++;
                    } else {
                        unionSet(parent, firstPrimeIdx, prime2idx[tester]);
                    }
                    break;
                }
                if (tester % primes[primeIdx] == 0) {
                    if (isFirstPrime) {
                        APrimeCount[primeIdx]++;
                        firstPrimeIdx = primeIdx;
                        isFirstPrime = false;
                    } else {
                        unionSet(parent, firstPrimeIdx, primeIdx);
                    }
                    while (tester % primes[primeIdx] == 0) tester /= primes[primeIdx];
                }
                primeIdx++;
            }
        }
        
        int maxCount = -1;
        map<int, int> nodeCount;
        for (int i = 0; i < primesLen; i++) {
            nodeCount[findParent(parent, i)] += APrimeCount[i];
            if (nodeCount[findParent(parent, i)] > maxCount) maxCount = nodeCount[findParent(parent, i)];
        }
        return maxCount;
    }
    
    void unionSet(vector<int>& parent, int idx1, int idx2) {
        int parent1 = findParent(parent, idx1);
        int parent2 = findParent(parent, idx2);
        parent[parent1] = parent2;
    }
    
    int findParent(vector<int>& parent, int idx) {
        if (parent[idx] != idx) {
            parent[idx] = findParent(parent, parent[idx]);
            return parent[idx];
        } else {
            return idx;
        }
    }
};