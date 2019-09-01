class Solution {
public:
    vector<vector<int>> updateMatrix(vector<vector<int>>& matrix) {
        // minimum of left-up, right-up, left-down, right-down
        vector<vector<int>> result(matrix.size(), vector<int>(matrix[0].size(), 0x3FFFFFFF));
        for (int i = 0; i < matrix.size(); i++) {
            for (int j = 0; j < matrix[0].size(); j++) {
                if (matrix[i][j] == 0) {
                    result[i][j] = 0;
                } else {
                    if (i - 1 >= 0) {
                        result[i][j] = min(result[i][j], result[i - 1][j] + 1);
                    }
                    if (j - 1 >= 0) {
                        result[i][j] = min(result[i][j], result[i][j - 1] + 1);
                    }
                }
            }
        }
        for (int i = 0; i < matrix.size(); i++) {
            for (int j = matrix[0].size() - 1; j >= 0; j--) {
                if (matrix[i][j] == 0) {
                    result[i][j] = 0;
                } else {
                    if (i - 1 >= 0) {
                        result[i][j] = min(result[i][j], result[i - 1][j] + 1);
                    }
                    if (j + 1 < matrix[0].size()) {
                        result[i][j] = min(result[i][j], result[i][j + 1] + 1);
                    }
                }
            }
        }
        for (int i = matrix.size() - 1; i >= 0; i--) {
            for (int j = 0; j < matrix[0].size(); j++) {
                if (matrix[i][j] == 0) {
                    result[i][j] = 0;
                } else {
                    if (i + 1 < matrix.size()) {
                        result[i][j] = min(result[i][j], result[i + 1][j] + 1);
                    }
                    if (j - 1 >= 0) {
                        result[i][j] = min(result[i][j], result[i][j - 1] + 1);
                    }
                }
            }
        }
        for (int i = matrix.size() - 1; i >= 0; i--) {
            for (int j = matrix[0].size() - 1; j >= 0; j--) {
                if (matrix[i][j] == 0) {
                    result[i][j] = 0;
                } else {
                    if (i + 1 < matrix.size()) {
                        result[i][j] = min(result[i][j], result[i + 1][j] + 1);
                    }
                    if (j + 1 < matrix[0].size()) {
                        result[i][j] = min(result[i][j], result[i][j + 1] + 1);
                    }
                }
            }
        }
        return result;
    }
};