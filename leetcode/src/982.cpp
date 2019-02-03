class Solution {
public:
    int countTriplets(vector<int>& A) {
        int ALen = A.size();
        vector<int> memo((1L << 16), 0);

        for (int i = 0; i < ALen; i++) {
            for (int j = 0; j < ALen; j++) {
                memo[A[i] & A[j]]++;
            }
        }
        
        int count = 0;
        for (int i = 0; i < ALen; i++) {
            for (int j = 0; j < (1 << 16); j++) {
                if ((j & A[i]) == 0) count += memo[j];
            }
        }
        return count;
    }
};