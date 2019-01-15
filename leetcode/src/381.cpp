class RandomizedCollection {
public:
    unordered_map<int, unordered_set<int>> val2idx;
    vector<int> vals;
    
    /** Initialize your data structure here. */
    RandomizedCollection() {
        
    }
    
    /** Inserts a value to the collection. Returns true if the collection did not already contain the specified element. */
    bool insert(int val) {
        bool existing = false;
        if (val2idx.find(val) != val2idx.end()) existing = true;
        val2idx[val].insert(vals.size());
        vals.push_back(val);
        return !existing;
    }
    
    /** Removes a value from the collection. Returns true if the collection contained the specified element. */
    bool remove(int val) {
        if (val2idx.find(val) != val2idx.end()) {
            int idxToDel = *val2idx[val].begin();
            int lastVal = *vals.rbegin();
            int lastIdx = vals.size() - 1;
            
            // swap two vals and their value-index pairs
            val2idx[val].erase(idxToDel);
            val2idx[val].insert(lastIdx);
            val2idx[lastVal].erase(lastIdx);
            val2idx[lastVal].insert(idxToDel);
            vals[idxToDel] = lastVal;
            vals[lastIdx] = val;
            
            // delete the last element
            val2idx[val].erase(lastIdx);
            if (!val2idx[val].size()) val2idx.erase(val);
            vals.pop_back();
            
            return true;
        } else {
            return false;
        }
    }
    
    /** Get a random element from the collection. */
    int getRandom() {
        return vals[(int)((double)rand() / (RAND_MAX + 1u) * vals.size())];
    }
};

/**
 * Your RandomizedCollection object will be instantiated and called as such:
 * RandomizedCollection obj = new RandomizedCollection();
 * bool param_1 = obj.insert(val);
 * bool param_2 = obj.remove(val);
 * int param_3 = obj.getRandom();
 */