class NumMatrix {
public:
    vector<vector<int> > matrixSum;
    
    NumMatrix(vector<vector<int>> matrix) {
        int m = matrix.size();
        if (m == 0) return;
        int n = matrix[0].size();
        if (n == 0) return;
        
        matrixSum = vector<vector<int> >(m, vector<int>(n, 0));
        matrixSum[0][0] = matrix[0][0];
        for (int i = 1; i < m; i++) {
            matrixSum[i][0] = matrixSum[i - 1][0] + matrix[i][0];
        }
        for (int i = 1; i < n; i++) {
            matrixSum[0][i] = matrixSum[0][i - 1] + matrix[0][i];
        }
        for (int i = 1; i < m; i++) {
            for (int j = 1; j < n; j++) {
                matrixSum[i][j] = matrixSum[i - 1][j] +
                                  matrixSum[i][j - 1] -
                                  matrixSum[i - 1][j - 1] +
                                  matrix[i][j];
            }
        }
    }
    
    int sumRegion(int row1, int col1, int row2, int col2) {
        if (matrixSum.size() == 0) return 0;
        
        int rightDown = matrixSum[row2][col2];
        int up = 0;
        if (row1 > 0) up = matrixSum[row1 - 1][col2];
        int left = 0;
        if (col1 > 0) left = matrixSum[row2][col1 - 1];
        int leftUp = 0;
        if (row1 > 0 && col1 > 0) leftUp = matrixSum[row1 - 1][col1 - 1];
        return rightDown - up - left + leftUp;
    }
};

/**
 * Your NumMatrix object will be instantiated and called as such:
 * NumMatrix obj = new NumMatrix(matrix);
 * int param_1 = obj.sumRegion(row1,col1,row2,col2);
 */