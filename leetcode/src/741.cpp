class Solution {
public:
    int cherryPickup(vector<vector<int>>& grid) {
        // dp on the same step to avoid repeat pick
        int N = grid.size();
        // path 1 row, path 1 col, path 2 row
        int maxPick[50][50][50] = {0};
        maxPick[0][0][0] = grid[0][0];
        for (int i1 = 0; i1 < N; i1++) {
            for (int j1 = 0; j1 < N; j1++) {
                for (int i2 = 0; i2 < N; i2++) {
                    int j2 = (i1 + j1 - i2);
                    if (i1 == 0 && j1 == 0 || j2 < 0 || j2 >= N ||
                        grid[i1][j1] < 0 || grid[i2][j2] < 0) {
                        continue;
                    }
                    maxPick[i1][j1][i2] = -1;
                    if (i1 - 1 >= 0 && i2 - 1 >= 0 &&
                        grid[i1 - 1][j1] >= 0 && grid[i2 - 1][j2] >= 0 &&
                        maxPick[i1 - 1][j1][i2 - 1] >= 0) {
                        maxPick[i1][j1][i2] = max(maxPick[i1][j1][i2],
                                                  maxPick[i1 - 1][j1][i2 - 1] +
                                                  grid[i1][j1] +
                                                  (i1 == i2 && j1 == j2 ? 0 : grid[i2][j2]));
                    }
                    if (i1 - 1 >= 0 && j2 - 1 >= 0 &&
                        grid[i1 - 1][j1] >= 0 && grid[i2][j2 - 1] >= 0 &&
                        maxPick[i1 - 1][j1][i2] >= 0) {
                        maxPick[i1][j1][i2] = max(maxPick[i1][j1][i2],
                                                  maxPick[i1 - 1][j1][i2] +
                                                  grid[i1][j1] +
                                                  (i1 == i2 && j1 == j2 ? 0 : grid[i2][j2]));
                    }
                    if (j1 - 1 >= 0 && i2 - 1 >= 0 &&
                        grid[i1][j1 - 1] >= 0 && grid[i2 - 1][j2] >= 0 &&
                        maxPick[i1][j1 - 1][i2 - 1] >= 0) {
                        maxPick[i1][j1][i2] = max(maxPick[i1][j1][i2],
                                                  maxPick[i1][j1 - 1][i2 - 1] +
                                                  grid[i1][j1] +
                                                  (i1 == i2 && j1 == j2 ? 0 : grid[i2][j2]));
                    }
                    if (j1 - 1 >= 0 && j2 - 1 >= 0 &&
                        grid[i1][j1 - 1] >= 0 && grid[i2][j2 - 1] >= 0 &&
                        maxPick[i1][j1 - 1][i2] >= 0) {
                        maxPick[i1][j1][i2] = max(maxPick[i1][j1][i2],
                                                  maxPick[i1][j1 - 1][i2] +
                                                  grid[i1][j1] +
                                                  (i1 == i2 && j1 == j2 ? 0 : grid[i2][j2]));
                    }
                }
            }
        }
        return max(0, maxPick[N - 1][N - 1][N - 1]);
    }
};