class Solution {
public:
    int getAbs(int x) {
        return x < 0 ? -x : x;
    }
    
    int minTotalDistance(vector<vector<int>>& grid) {
        // calculate mid of x and y
        int m = grid.size();
        if (m == 0) return 0;
        int n = grid[0].size();
        if (n == 0) return 0;
        
        vector<int> xPos, yPos;
        int pointCnt = 0;
        for (int i = 0; i < m; i++) {
            for (int j = 0; j < n; j++) {
                if (grid[i][j]) {
                    xPos.push_back(i);
                    yPos.push_back(j);
                    pointCnt++;
                }
            }
        }
        nth_element(yPos.begin(), yPos.begin() + pointCnt / 2, yPos.end());
        
        int xMid = xPos[pointCnt / 2];
        int yMid = yPos[pointCnt / 2];
        
        int minDis = 0;
        for (int i = 0; i < pointCnt; i++) {
            minDis += getAbs(xPos[i] - xMid) + getAbs(yPos[i] - yMid);
        }
        return minDis;
    }
};