class Solution {
public:
    vector<int> pancakeSort(vector<int>& A) {
        // put max values at the downmost
        vector<int> result;
        
        int ALen = A.size();
        for (int i = ALen; i > 0; i--) {
            int currMaxIdx = 0;
            for (int j = 0; j < i; j++) {
                if (A[j] == i) {
                    currMaxIdx = j;
                    break;
                }
            }
            if (currMaxIdx == i - 1) continue;
            // do two reverses
            reverse(A.begin(), A.begin() + currMaxIdx + 1);
            result.push_back(currMaxIdx + 1);
            reverse(A.begin(), A.begin() + i);
            result.push_back(i);
        }
        
        return result;
    }
};