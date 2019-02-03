class Solution {
public:
    int trapRainWater(vector<vector<int>>& heightMap) {
        int m = heightMap.size();
        if (m == 0) return 0;
        int n = heightMap[0].size();
        if (n == 0) return 0;
        
        vector<vector<int>> forbidden(m, vector<int>(n, 0));
        priority_queue<vector<int>,
                       vector<vector<int>>,
                       greater<vector<int>>> bfsQ;
        for (int i = 0; i < m; i++) {
            for (int j = 0; j < n; j++) {
                if (i != 0 && i != m - 1 && j != 0 && j != n - 1) continue;
                bfsQ.push(vector<int>{heightMap[i][j], i, j});
                forbidden[i][j] = 1;
            }
        }
        
        int result = 0;
        while (!bfsQ.empty()) {
            vector<int> minCell = bfsQ.top();
            bfsQ.pop();
            result += dfs(minCell[1], minCell[2], minCell[0],
                          forbidden, heightMap, bfsQ);
        }
        return result;
    }
    
    int dfs(int x, int y, int h,
            vector<vector<int>>& forbidden,
            vector<vector<int>>& heightMap,
            priority_queue<vector<int>,
                           vector<vector<int>>,
                           greater<vector<int>>>& bfsQ) {
        int filled = h - heightMap[x][y];
        heightMap[x][y] = max(h, heightMap[x][y]);

        if (!forbidden[x][y]) {
            bfsQ.push(vector<int>{heightMap[x][y], x, y});
        }
        forbidden[x][y] = 1;

        if (filled < 0) return 0;

        int m = heightMap.size();
        int n = heightMap[0].size();
        if (x - 1 >= 0 && !forbidden[x - 1][y]) {
            filled += dfs(x - 1, y, h, forbidden, heightMap, bfsQ);
        }
        if (x + 1 < m && !forbidden[x + 1][y]) {
            filled += dfs(x + 1, y, h, forbidden, heightMap, bfsQ);
        }
        if (y - 1 >= 0 && !forbidden[x][y - 1]) {
            filled += dfs(x, y - 1, h, forbidden, heightMap, bfsQ);
        }
        if (y + 1 < n && !forbidden[x][y + 1]) {
            filled += dfs(x, y + 1, h, forbidden, heightMap, bfsQ);
        }
        return filled;
    }
};