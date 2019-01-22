class Solution {
public:
    int largestComponentSize(vector<int>& A) {
        int ALen = A.size();
        unordered_map<int, vector<int>> facToIndices;
        for (int i = 0; i < ALen; i++) {
            for (int j = 2; A[i] > 1; j++) {
                if ((long long)j * (long long)j > (long long)A[i]) break;
                if (!(A[i] % j)) {
                    facToIndices[j].push_back(i);
                    while (!(A[i] % j)) A[i] /= j;
                }
            }
            if (A[i] != 1) {
                facToIndices[A[i]].push_back(i);
            }
        }
        
        vector<int> parent(ALen, 0);
        for (int i = 0; i < ALen; i++) {
            parent[i] = i;
        }
        
        for (auto itr = facToIndices.begin(); itr != facToIndices.end(); ++itr) {
            vector<int>& nodes = itr->second;
            int nodesLen = nodes.size();
            for (int i = 1; i < nodesLen; i++) {
                unionSet(nodes[i - 1], nodes[i], parent);
            }
        }
        
        int maxCnt = 1;
        unordered_map<int, int> parentCnt;
        for (int i = 0; i < ALen; i++) {
            int currParent = findParent(i, parent);
            parentCnt[currParent]++;
            maxCnt = max(maxCnt, parentCnt[currParent]);
        }
        return maxCnt;
    }
    
    void unionSet(int idx1, int idx2, vector<int>& parent) {
        int parent1 = findParent(idx1, parent);
        int parent2 = findParent(idx2, parent);
        parent[parent1] = parent2;
    }
    
    int findParent(int idx, vector<int>& parent) {
        if (parent[idx] != idx) {
            parent[idx] = findParent(parent[idx], parent);
        }
        return parent[idx];
    }
};