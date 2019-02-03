class Solution {
public:
    vector<int> findMinHeightTrees(int n, vector<pair<int, int>>& edges) {
        vector<int> result;
        if (n == 0) return result;
        if (n == 1) return vector<int>{0};
        
        // topo sort
        unordered_map<int, unordered_set<int>> adjList;
        vector<int> degrees(n, 0);
        for (auto itr = edges.begin(); itr != edges.end(); ++itr) {
            adjList[itr->first].insert(itr->second);
            adjList[itr->second].insert(itr->first);
            degrees[itr->first]++;
            degrees[itr->second]++;
        }
        
        queue<int> bfsQ;
        for (int i = 0; i < n; i++) {
            if (degrees[i] == 1) bfsQ.push(i);
        }
        while (adjList.size() > 2) {
            queue<int> newBfsQ;
            while (!bfsQ.empty()) {
                int node = bfsQ.front();
                bfsQ.pop();
                // delete edges (should be only 1 edge)
                for (auto itr = adjList[node].begin();
                     itr != adjList[node].end(); ++itr) {
                    degrees[*itr]--;
                    if (degrees[*itr] == 1) newBfsQ.push(*itr);
                }
                // delete node
                adjList.erase(node);
            }
            bfsQ = newBfsQ;
        }
        
        for (auto itr = adjList.begin(); itr != adjList.end(); ++itr) {
            result.push_back(itr->first);
        }
        return result;
    }
};