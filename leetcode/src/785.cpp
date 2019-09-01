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
    
    bool isBipartite(vector<vector<int>>& graph) {
        vector<int> parent(graph.size());
        for (int i = 0; i < graph.size(); i++) {
            parent[i] = i;
        }
        for (int i = 0; i < graph.size(); i++) {
            for (int j = 1; j < graph[i].size(); j++) {
                unionSet(graph[i][0], graph[i][j], parent);
            }
        }
        for (int i = 0; i < graph.size(); i++) {
            for (int j = 1; j < graph[i].size(); j++) {
                if (findParent(i, parent) == findParent(graph[i][j], parent)) {
                    return false;
                }
            }
        }
        return true;
    }
};