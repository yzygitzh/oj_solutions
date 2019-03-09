class Solution {
public:
    int longestOnes(vector<int>& A, int K) {
        // two pointers, zero count == K
        int ALen = A.size();
        int left = 0, right = 0, zeroCnt = 0, maxCnt = 0;
        while (right < ALen) {
            if (A[right] == 0) zeroCnt++;
            right++;
            
            if (zeroCnt <= K) {
                maxCnt = max(maxCnt, right - left);
            }
            
            while (zeroCnt > K) {
                if (A[left] == 0) zeroCnt--;
                left++;
            }
        }
        return maxCnt;
    }
};