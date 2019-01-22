class Solution {
public:
    bool searchMatrix(vector<vector<int>>& matrix, int target) {
        int m = matrix.size();
        if (m == 0) return false;
        int n = matrix[0].size();
        if (n == 0) return false;
        
        int left = 0, right = m * n - 1;
        while (left + 1 < right) {
            int mid = (left + right) / 2;
            int row = mid / n;
            int col = mid % n;
            if (matrix[row][col] < target) {
                left = mid;
            } else {
                right = mid;
            }
        }
        
        if (matrix[left / n][left % n] == target) {
            return true;
        } else if (matrix[right / n][right % n] == target) {
            return true;
        } else {
            return false;
        }
    }
};