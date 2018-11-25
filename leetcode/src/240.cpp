class Solution {
public:
    bool searchMatrix(vector<vector<int>>& matrix, int target) {
        int m = matrix.size();
        if (m == 0) return false;
        int n = matrix[0].size();
        if (n == 0) return false;
        
        return binSearch(matrix, 0, m - 1, 0, n - 1, target);
    }
    
    bool binSearch(vector<vector<int>>& matrix,
                   int upRow, int downRow, int leftCol, int rightCol,
                   int target) {
        if (upRow + 1 < downRow) {
            int midRow = (upRow + downRow) / 2;
            // find midCol
            int left = leftCol, right = rightCol;
            while (left + 1 < right) {
                int mid = (left + right) / 2;
                if (matrix[midRow][mid] < target) {
                    left = mid;
                } else {
                    right = mid;
                }
            }
            bool foundLeft = binSearch(matrix,
                                       midRow, downRow, leftCol, right,
                                       target);
            bool foundRight = binSearch(matrix,
                                        upRow, midRow, left, rightCol,
                                        target);
            return foundLeft || foundRight;
        } else if (leftCol + 1 < rightCol) {
            int midCol = (leftCol + rightCol) / 2;
            // find midRow
            int up = upRow, down = downRow;
            while (up + 1 < down) {
                int mid = (up + down) / 2;
                if (matrix[mid][midCol] < target) {
                    up = mid;
                } else {
                    down = mid;
                }
            }
            bool foundUp = binSearch(matrix,
                                     upRow, down, midCol, rightCol,
                                     target);
            bool foundDown = binSearch(matrix,
                                       up, downRow, leftCol, midCol,
                                       target);
            return foundUp || foundDown;
        } else {
            for (int i = upRow; i <= downRow; i++) {
                for (int j = leftCol; j <= rightCol; j++) {
                    if (matrix[i][j] == target) return true;
                }
            }
            return false;
        }
    }
};