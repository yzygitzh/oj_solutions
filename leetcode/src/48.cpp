class Solution {
public:
    void rotate(vector<vector<int>>& matrix) {
        int n = matrix.size();
        for (int i = 0; i < n; i++) {
            int edgeLen = n - 2 * i - 1;
            for (int j = 0; j < edgeLen; j++) {
                int row1 = i, col1 = i + j;
                int row2 = i + j, col2 = n - i - 1;
                int row3 = n - i - 1, col3 = n - (i + j) - 1;
                int row4 = n - (i + j) - 1, col4 = i;
                
                int m1 = matrix[row1][col1];
                int m2 = matrix[row2][col2];
                int m3 = matrix[row3][col3];
                int m4 = matrix[row4][col4];
                
                matrix[row1][col1] = m4;
                matrix[row2][col2] = m1;
                matrix[row3][col3] = m2;
                matrix[row4][col4] = m3;
            }
        }
    }
};