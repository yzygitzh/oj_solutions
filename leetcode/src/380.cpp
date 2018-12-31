class RandomizedSet {
public:
    vector<int> nums;
    unordered_map<int, int> num2idx;
    
    /** Initialize your data structure here. */
    RandomizedSet() {
        
    }
    
    /** Inserts a value to the set. Returns true if the set did not already contain the specified element. */
    bool insert(int val) {
        if (num2idx.find(val) != num2idx.end()) {
            return false;
        } else {
            num2idx[val] = nums.size();
            nums.push_back(val);
            return true;
        }
    }
    
    /** Removes a value from the set. Returns true if the set contained the specified element. */
    bool remove(int val) {
        if (num2idx.find(val) != num2idx.end()) {
            // swap this element with the last one
            int valIdx = num2idx[val];
            if (valIdx != nums.size() - 1) {
                nums[valIdx] = *nums.rbegin();
                num2idx[nums[valIdx]] = valIdx;
            }
            nums.pop_back();
            num2idx.erase(val);
            return true;
        } else {
            return false;
        }
    }
    
    /** Get a random element from the set. */
    int getRandom() {
        return nums[(int)((double)rand() / (RAND_MAX + 1u) * nums.size())];
    }
};

/**
 * Your RandomizedSet object will be instantiated and called as such:
 * RandomizedSet obj = new RandomizedSet();
 * bool param_1 = obj.insert(val);
 * bool param_2 = obj.remove(val);
 * int param_3 = obj.getRandom();
 */