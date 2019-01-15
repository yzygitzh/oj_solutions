class Solution {
public:
    int largestPerimeter(vector<int>& A) {
        int ALen = A.size();
        sort(A.begin(), A.end());
        for (int i = ALen - 3; i >= 0; i--) {
            if (A[i] + A[i + 1] > A[i + 2]) return A[i] + A[i + 1] + A[i + 2];
        }
        return 0;
    }
};