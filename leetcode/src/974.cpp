class Solution {
public:
    int subarraysDivByK(vector<int>& A, int K) {
        // shift array by -A[i] each time!
        
        int ALen = A.size();
        vector<int> remainderSeqNum(K, 0);
        int shift = 0, result = 0;
        
        for (int i = 0; i < ALen; i++) {
            int newA = A[i];
            while (newA < 0) newA += K;
            newA = newA % K;
            shift = (shift - newA + K) % K;
            remainderSeqNum[(shift + newA) % K] += 1;
            result += remainderSeqNum[shift % K];
        }
        
        return result;
    }
};