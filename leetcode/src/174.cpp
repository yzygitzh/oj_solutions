class Solution {
public:
    int calculateMinimumHP(vector<vector<int>>& dungeon) {
        int m = dungeon.size();
        int n = dungeon[0].size();
        vector<vector<int> > memo(m, vector<int>(n, -1));
        return calcMinHP(0, 0, dungeon, memo) + 1;
    }
    
    int calcMinHP(int row, int col, vector<vector<int>>& dungeon, vector<vector<int>>& memo) {
        int m = dungeon.size();
        int n = dungeon[0].size();
        

        if (memo[row][col] != -1) return memo[row][col];
        if (row == m - 1 && col == n - 1) {
            memo[row][col] = dungeon[row][col] < 0 ? -dungeon[row][col] : 0;
            return memo[row][col];
        }
        
        int minHP = ~(1 << 31);
        // go down
        if (row + 1 < m) {
            int downCost = calcMinHP(row + 1, col, dungeon, memo);
            int downHP = dungeon[row][col] - downCost < 0 ? downCost - dungeon[row][col] : 0;
            if (downHP < minHP) minHP = downHP;
        }
        // go right
        if (col + 1 < n) {
            int rightCost = calcMinHP(row, col + 1, dungeon, memo);
            int rightHP = dungeon[row][col] - rightCost < 0 ? rightCost - dungeon[row][col] : 0;
            if (rightHP < minHP) minHP = rightHP;
        }
        memo[row][col] = minHP;
        return memo[row][col];
    }
};