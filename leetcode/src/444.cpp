class Solution {
public:
    bool sequenceReconstruction(vector<int>& org, vector<vector<int>>& seqs) {
        // all (org[i], org[i+1]) can be found in seqs
        // and there should be no circle
        
        int n = org.size();
        if (n == 0) return false;
        
        vector<int> inDegree(n + 1, 0);
        unordered_map<int, unordered_set<int>> adjList;
        unordered_set<int> nodeCheck;
        for (int i = 1; i <= n; i++) nodeCheck.insert(i);
        for (auto itr = seqs.begin(); itr != seqs.end(); ++itr) {
            int seqLen = itr->size();
            if (seqLen > 0) {
                if ((*itr)[0] <= 0 || (*itr)[0] > n) return false;
                nodeCheck.erase((*itr)[0]);
            }
            for (int i = 0; i + 1 < seqLen; i++) {
                if ((*itr)[i + 1] <= 0 || (*itr)[i + 1] > n) return false;
                nodeCheck.erase((*itr)[i + 1]);
                if (!adjList[(*itr)[i]].count((*itr)[i + 1])) {
                    adjList[(*itr)[i]].insert((*itr)[i + 1]);
                    inDegree[(*itr)[i + 1]]++;
                }
            }
        }
        
        // all nodes are present, and all sequences contain only valid nodes
        if (nodeCheck.size() > 0) return false;

        // first if all org edges are present
        for (int i = 0; i + 1 < n; i++) {
            if (!adjList[org[i]].count(org[i + 1])) return false;
        }
        
        // check circle by topological sort
        queue<int> topoSortQ;
        for (int i = 1; i <= n; i++) {
            if (!inDegree[i]) topoSortQ.push(i);
        }
        
        while (!topoSortQ.empty()) {
            int currP = topoSortQ.front();
            topoSortQ.pop();
            for (auto itr = adjList[currP].begin();
                 itr != adjList[currP].end(); ++itr) {
                inDegree[*itr]--;
                if (!inDegree[*itr]) topoSortQ.push(*itr);
            }
            adjList.erase(currP);
        }
        
        return adjList.size() == 0;
    }
};