class Solution {
public:
    bool validTree(int n, vector<pair<int, int>>& edges) {
        // tree: n - 1 edges and connected
        int edgesLen = edges.size();
        if (edgesLen != n - 1) return false;
        
        vector<int> parent(n);
        for (int i = 0; i < n; i++) parent[i] = i;
        
        for (int i = 0; i < edgesLen; i++) {
            unionSet(edges[i].first, edges[i].second, parent);
        }
        
        for (int i = 1; i < n; i++) {
            if (findParent(i, parent) != findParent(i - 1, parent)) return false;
        }
        return true;
    }
    
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
};