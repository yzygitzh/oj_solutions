class Solution {
public:
    int maxAreaOfIsland(vector<vector<int>>& grid) {
        int height = grid.size();
        int width = grid[0].size();
        
        int result = 0;
        for (int i = 0; i < height; i++) {
            for (int j = 0; j < width; j++) {
                if (grid[i][j] == 1) {
                    queue<vector<int>> bfsQ;
                    bfsQ.push(vector<int>{i, j});
                    grid[i][j] = -1;
                    int currSize = 0;
                    while (!bfsQ.empty()) {
                        currSize++;
                        vector<int> pos = bfsQ.front();
                        bfsQ.pop();
                        if (pos[0] - 1 >= 0 && grid[pos[0] - 1][pos[1]] == 1) {
                            grid[pos[0] - 1][pos[1]] = -1;
                            bfsQ.push(vector<int>{pos[0] - 1, pos[1]});
                        }
                        if (pos[1] - 1 >= 0 && grid[pos[0]][pos[1] - 1] == 1) {
                            grid[pos[0]][pos[1] - 1] = -1;
                            bfsQ.push(vector<int>{pos[0], pos[1] - 1});
                        }
                        if (pos[0] + 1 < height && grid[pos[0] + 1][pos[1]] == 1) {
                            grid[pos[0] + 1][pos[1]] = -1;
                            bfsQ.push(vector<int>{pos[0] + 1, pos[1]});
                        }
                        if (pos[1] + 1 < width && grid[pos[0]][pos[1] + 1] == 1) {
                            grid[pos[0]][pos[1] + 1] = -1;
                            bfsQ.push(vector<int>{pos[0], pos[1] + 1});
                        }
                    }
                    result = max(result, currSize);
                }
            }
        }
        return result;
    }
};