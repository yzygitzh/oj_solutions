class Solution {
public:
    int shortestPathBinaryMatrix(vector<vector<int>>& grid) {
        vector<vector<int>> visited(grid.size(), vector<int>(grid[0].size(), 0));
        queue<vector<int>> bfsQ;
        if (grid[0][0] == 0) {
            bfsQ.push(vector<int>{0, 0, 1});
            visited[0][0] = 1;
        }
        while (!bfsQ.empty()) {
            vector<int> state = bfsQ.front();
            bfsQ.pop();
            if (state[0] == grid.size() - 1 &&
                state[1] == grid[0].size() - 1) {
                return state[2];
            }
            for (int i = -1; i <= 1; i++) {
                for (int j = -1; j <= 1; j++) {
                    if (state[0] + i >= 0 && state[0] + i < grid.size() &&
                        state[1] + j >= 0 && state[1] + j < grid[0].size() &&
                        !visited[state[0] + i][state[1] + j] &&
                        grid[state[0] + i][state[1] + j] == 0) {
                        visited[state[0] + i][state[1] + j] = 1;
                        bfsQ.push(vector<int>{state[0] + i, state[1] + j, state[2] + 1});
                    }
                }
            }
        }
        return -1;
    }
};