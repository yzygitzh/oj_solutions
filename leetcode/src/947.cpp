class Solution {
public:
    int removeStones(vector<vector<int>>& stones) {
        int stonesLen = stones.size();
        if (stonesLen == 0) return 0;
        
        vector<int> parent(stonesLen, 0);
        for (int i = 0; i < stonesLen; i++) {
            parent[i] = i;
        }
        
        // union rows
        map<int, int> row2point;
        for (int i = 0; i < stonesLen; i++) {
            if (row2point.find(stones[i][0]) == row2point.end()) {
                row2point[stones[i][0]] = i;
            }
            unionPoints(parent, row2point[stones[i][0]], i);
        }
        
        // pick col represents
        map<int, int> col2point;
        for (int i = 0; i < stonesLen; i++) {
            if (col2point.find(stones[i][1]) == col2point.end()) {
                col2point[stones[i][1]] = i;
            }
            unionPoints(parent, col2point[stones[i][1]], i);
        }
        
        map<int, int> setCount;
        for (int i = 0; i < stonesLen; i++) {
            setCount[findParent(parent, i)]++;
        }
        int sum = 0;
        for (map<int, int>::iterator itr = setCount.begin();
             itr != setCount.end(); ++itr) {
            sum += itr->second - 1;
        }
        return sum;
    }
    
    void unionPoints(vector<int> &parent, int idx1, int idx2) {
        int parent1 = findParent(parent, idx1); 
        int parent2 = findParent(parent, idx2); 
        parent[parent1] = parent2;
    }
    
    int findParent(vector<int> &parent, int idx) {
        if (parent[idx] == idx) {
            return idx;
        } else {
            parent[idx] = findParent(parent, parent[idx]);
            return parent[idx];
        }
    }
};