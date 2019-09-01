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
    
    vector<vector<string>> accountsMerge(vector<vector<string>>& accounts) {
        unordered_map<string, vector<int>> emailToIndices;
        vector<int> parent(accounts.size());
        for (int i = 0; i < accounts.size(); i++) {
            parent[i] = i;
        }
        for (int i = 0; i < accounts.size(); i++) {
            for (int j = 1; j < accounts[i].size(); j++) {
                // merge indices
                if (!emailToIndices[accounts[i][j]].empty()) {
                    unionSet(i, emailToIndices[accounts[i][j]][0], parent);
                    emailToIndices[accounts[i][j]][0] = i;
                } else {
                    emailToIndices[accounts[i][j]].push_back(i);
                }
            }
        }
        unordered_map<int, set<string>> idxToEmails;
        for (int i = 0; i < accounts.size(); i++) {
            int idx = findParent(i, parent);
            for (int j = 1; j < accounts[i].size(); j++) {
                idxToEmails[idx].insert(accounts[i][j]);
            }
        }
        vector<vector<string>> result;
        for (auto& p : idxToEmails) {
            result.push_back(vector<string>{accounts[p.first][0]});
            for (auto& email : p.second) {
                result.back().push_back(email);
            }
        }
        return result;
    }
};