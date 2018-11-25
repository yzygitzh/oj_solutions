class Solution {
public:
    bool searchMatrix(vector<vector<int>>& matrix, int target) {
        int m = matrix.size();
        if (m == 0) return false;
        int n = matrix[0].size();
        if (n == 0) return false;
        
        // bin search row
        int up = 0, down = m - 1;
        while (up + 1 < down) {
            int mid = (up + down) / 2;
            if (matrix[mid][0] < target) {
                up = mid;
            } else {
                down = mid;
            }
        }
        
        for (int row = up; row <= down; row++) {
            int left = 0, right = n - 1;
            while (left + 1 < right) {
                int mid = (left + right) / 2;
                if (matrix[row][mid] < target) {
                    left = mid;
                } else {
                    right = mid;
                }
            }
            if (matrix[row][left] == target) return true;
            if (matrix[row][right] == target) return true;
        }
        
        return false;
    }
};