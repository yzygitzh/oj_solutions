class Solution {
public:
    vector<int> nums;
    
    Solution(vector<int> _nums) {
        nums = _nums;
    }
    
    /** Resets the array to its original configuration and return it. */
    vector<int> reset() {
        return nums;
    }
    
    /** Returns a random shuffling of the array. */
    vector<int> shuffle() {
        vector<int> result = nums;
        int resultLen = result.size();
        for (int i = 0; i < resultLen; i++) {
            int poolLen = resultLen - i;
            int chgIdx = i +
                         (int)((double)rand() / (RAND_MAX + 1u) * poolLen);
            int swap = result[i];
            result[i] = result[chgIdx];
            result[chgIdx] = swap;
        }
        return result;
    }
};

/**
 * Your Solution object will be instantiated and called as such:
 * Solution obj = new Solution(nums);
 * vector<int> param_1 = obj.reset();
 * vector<int> param_2 = obj.shuffle();
 */