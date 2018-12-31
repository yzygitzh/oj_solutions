class Solution {
public:
    int getMin(int a, int b) {
        return a < b ? a : b;
    }

    int getMax(int a, int b) {
        return a > b ? a : b;
    }

    int maximalRectangle(vector<vector<char>>& matrix) {
        int m = matrix.size();
        if (m == 0) return 0;
        int n = matrix[0].size();
        if (n == 0) return 0;

        vector<int> maxH(n, 0), maxL(n, 0), maxR(n, 0);
        int maxArea = 0;

        for (int i = 0; i < m; i++) {
            vector<int> currMaxL(n, 0), currMaxR(n, 0);
            
            for (int j = 0; j < n; j++) {
                if (j == 0) {
                    currMaxL[j] = matrix[i][j] - '0';
                    currMaxR[n - 1 - j] = matrix[i][n - 1 - j] - '0';
                } else {
                    if (matrix[i][j] - '0' == 0) currMaxL[j] = 0;
                    else currMaxL[j] = currMaxL[j - 1] + 1;
                    if (matrix[i][n - 1 - j] - '0' == 0) currMaxR[n - 1 - j] = 0;
                    else currMaxR[n - 1 - j] = currMaxR[n - j] + 1;
                }
            }
            
            for (int j = 0; j < n; j++) {
                if (i == 0) {
                    maxH[j] = matrix[i][j] - '0';
                    maxL[j] = currMaxL[j];
                    maxR[j] = currMaxR[j];
                } else {
                    if (matrix[i][j] - '0' == 0){
                        maxH[j] = 0;
                    }
                    else {
                        if (maxH[j] == 0) {
                            maxL[j] = currMaxL[j];
                            maxR[j] = currMaxR[j];
                        } else {
                            maxL[j] = getMin(currMaxL[j], maxL[j]);
                            maxR[j] = getMin(currMaxR[j], maxR[j]);
                        }
                        maxH[j] = maxH[j] + 1;
                    }
                }
                int currArea = maxH[j] * (maxL[j] + maxR[j] - 1);
                maxArea = getMax(currArea, maxArea);
            }
        }

        return maxArea;
    }
};