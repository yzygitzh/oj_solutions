class Solution {
public:
    unordered_set<int> islands;
    
    vector<int> numIslands2(int m, int n, vector<pair<int, int>>& positions) {
        vector<int> filled(m * n, 0);
        vector<int> parents(m * n);
        for (int i = 0; i < m * n; i++) {
            parents[i] = i;
        }
        
        int queryLen = positions.size();
        vector<int> result(queryLen);
        for (int i = 0; i < queryLen; i++) {
            pair<int, int> pos = positions[i];
            int x = pos.first, y = pos.second;
            filled[n * x + y] = 1;
            islands.insert(n * x + y);
            if (x - 1 >= 0 && filled[n * (x - 1) + y]) {
                unionSet(n * x + y, n * (x - 1) + y, parents);
            }
            if (x + 1 < m && filled[n * (x + 1) + y]) {
                unionSet(n * x + y, n * (x + 1) + y, parents);
            }
            if (y - 1 >= 0 && filled[n * x + y - 1]) {
                unionSet(n * x + y, n * x + y - 1, parents);
            }
            if (y + 1 < n && filled[n * x + y + 1]) {
                unionSet(n * x + y, n * x + y + 1, parents);
            }
            result[i] = islands.size();
        }
        return result;
    }
    
    int findParent(int idx, vector<int>& parents) {
        if (idx != parents[idx]) {
            parents[idx] = findParent(parents[idx], parents);
        }
        return parents[idx];
    }
    
    void unionSet(int idx1, int idx2, vector<int>& parents) {
        int parent1 = findParent(idx1, parents);
        int parent2 = findParent(idx2, parents);
        parents[parent1] = parent2;
        islands.erase(parent1);
        islands.insert(parent2);
    }
};