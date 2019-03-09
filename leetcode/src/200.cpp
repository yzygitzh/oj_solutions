class Solution {
public:
    int findParent(int idx, vector<int>& parent) {
        if (idx != parent[idx]) {
            parent[idx] = findParent(parent[idx], parent);
        }
        return parent[idx];
    }
    
    void unionSet(int idx1, int idx2, vector<int>& parent) {
        int parent1 = findParent(idx1, parent);
        int parent2 = findParent(idx2, parent);
        parent[parent1] = parent2;
    }
    
    int numIslands(vector<vector<char>>& grid) {
        int m = grid.size();
        if (m == 0) return 0;
        int n = grid[0].size();
        if (n == 0) return 0;
        
        vector<int> parent(m * n);
        for (int i = 0; i < m; i++) {
            for (int j = 0; j < n; j++) {
                parent[i * n + j] = i * n + j;
                if (grid[i][j] == '1') {
                    if (i - 1 >= 0 && grid[i - 1][j] == '1') {
                        unionSet(i * n + j, (i - 1) * n + j, parent);
                    }
                    if (j - 1 >= 0 && grid[i][j - 1] == '1') {
                        unionSet(i * n + j, i * n + j - 1, parent);
                    }
                }
            }
        }
        unordered_set<int> parentCnt;
        for (int i = 0; i < m; i++) {
            for (int j = 0; j < n; j++) {
                if (grid[i][j] == '1') parentCnt.insert(findParent(i * n + j, parent));
            }
        }
        return parentCnt.size();
    }
};