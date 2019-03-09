class Solution {
public:
    int orangesRotting(vector<vector<int>>& grid) {
        int m = grid.size();
        int n = grid[0].size();
        int orangeCnt = 0;
        queue<vector<int>> rottenQ;
        for (int i = 0; i < m; i++) {
            for (int j = 0; j < n; j++) {
                if (grid[i][j] > 0) {
                    orangeCnt++;
                    if (grid[i][j] == 2) rottenQ.push(vector<int>{i, j, 0});
                }
            }
        }
        int rottenCnt = 0;
        int maxTime = 0;
        while (!rottenQ.empty()) {
            vector<int> currRotten = rottenQ.front();
            rottenQ.pop();
            rottenCnt++;
            int x = currRotten[0], y = currRotten[1], time = currRotten[2];
            maxTime = max(maxTime, time);
            if (x - 1 >= 0 && grid[x - 1][y] == 1) {
                grid[x - 1][y] = 2;
                rottenQ.push(vector<int>{x - 1, y, time + 1});
            }
            if (x + 1 < m && grid[x + 1][y] == 1) {
                grid[x + 1][y] = 2;
                rottenQ.push(vector<int>{x + 1, y, time + 1});
            }
            if (y - 1 >= 0 && grid[x][y - 1] == 1) {
                grid[x][y - 1] = 2;
                rottenQ.push(vector<int>{x, y - 1, time + 1});
            }
            if (y + 1 < n && grid[x][y + 1] == 1) {
                grid[x][y + 1] = 2;
                rottenQ.push(vector<int>{x, y + 1, time + 1});
            }
        }
        return rottenCnt == orangeCnt ? maxTime : -1;
    }
};