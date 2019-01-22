class Solution {
public:
    unordered_map<int, vector<int>> valToIdx;
    Solution(vector<int> nums) {
        int numsLen = nums.size();
        for (int i = 0; i < numsLen; i++) {
            valToIdx[nums[i]].push_back(i);
        }
    }
    
    int pick(int target) {
        int idxLen = valToIdx[target].size();
        int idx = (double)rand() / ((double)RAND_MAX + 1) * idxLen;
        return valToIdx[target][idx];
    }
};

/**
 * Your Solution object will be instantiated and called as such:
 * Solution obj = new Solution(nums);
 * int param_1 = obj.pick(target);
 */