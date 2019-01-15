class Solution {
public:
    int countComponents(int n, vector<pair<int, int>>& edges) {
        if (n <= 0) return 0;
        vector<int> parent(n);
        for (int i = 0; i < n; i++) parent[i] = i;
        for (auto itr = edges.begin(); itr != edges.end(); ++itr) {
            unionSet(itr->first, itr->second, parent);
        }
        unordered_set<int> uniqParents;
        for (int i = 0; i < n; i++) uniqParents.insert(findParent(i, parent));
        return uniqParents.size();
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