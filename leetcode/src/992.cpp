class Solution {
public:
    int subarraysWithKDistinct(vector<int>& A, int K) {
        return atMostK(A, K) - atMostK(A, K - 1);
    }
    
    int atMostK(vector<int>&A, int K) {
        int result = 0;
        int ALen = A.size();
        unordered_map<int, int> numCnt;
        int left = 0, right = 0;
        while (right < ALen) {
            numCnt[A[right]]++;
            while (numCnt.size() > K) {
                numCnt[A[left]]--;
                if (numCnt[A[left]] == 0) numCnt.erase(A[left]);
                left++;
            }
            result += right - left + 1;
            right++;
        }
        return result;
    }
};