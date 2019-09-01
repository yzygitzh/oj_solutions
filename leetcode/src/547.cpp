class Solution {
public:
    int findParent(int idx, vector<int>& parent) {
        if (parent[idx] != idx) {
            parent[idx] = findParent(parent[idx], parent);
        }
        return parent[idx];
    }
    
    void unionSet(int idx1, int idx2, vector<int>& parent) {
        int parent1 = findParent(idx1, parent);
        int parent2 = findParent(idx2, parent);
        parent[parent1] = parent2;
    }
    
    int findCircleNum(vector<vector<int>>& M) {
        vector<int> parent(M.size(), 0);
        for (int i = 0; i < M.size(); i++) {
            parent[i] = i;
        }
        for (int i = 0; i < M.size(); i++) {
            for (int j = 0; j < i; j++) {
                if (M[i][j]) {
                    unionSet(i, j, parent);
                }
            }
        }
        unordered_set<int> uniqueCircles;
        for (int i = 0; i < M.size(); i++) {
            uniqueCircles.insert(findParent(i, parent));
        }
        return uniqueCircles.size();
    }
};