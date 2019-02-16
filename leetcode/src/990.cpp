class Solution {
public:
    bool equationsPossible(vector<string>& equations) {
        // divide equations into == and != parts
        vector<string> equalEqs, nonEqualEqs;
        for (auto itr = equations.begin(); itr != equations.end(); ++itr) {
            if ((*itr)[1] == '!') nonEqualEqs.push_back(*itr);
            else equalEqs.push_back(*itr);
        }
        
        vector<int> parent(26);
        for (int i = 0; i < 26; i++) {
            parent[i] = i;
        }
        
        for (auto itr = equalEqs.begin(); itr != equalEqs.end(); ++itr) {
            unionSet((*itr)[0] - 'a', (*itr)[3] - 'a', parent);
        }
        for (auto itr = nonEqualEqs.begin(); itr != nonEqualEqs.end(); ++itr) {
            if (findParent((*itr)[0] - 'a', parent) ==
                findParent((*itr)[3] - 'a', parent)) {
                return false;
            }
        }
        return true;
    }
    
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
};