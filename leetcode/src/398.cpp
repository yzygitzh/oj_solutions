class Solution {
public:
    vector<int> nums;
    Solution(vector<int> _nums) {
        nums = move(_nums);
    }
    
    double normRand() {
        return (double)rand() / (RAND_MAX + 1u);
    }
    
    int pick(int target) {
        int count = 0;
        int idx = -1;
        for (int i = 0; i < nums.size(); i++) {
            if (nums[i] == target) {
                count++;
                if (normRand() * count < 1) {
                    idx = i;
                }
            }
        }
        return idx;
    }
};

/**
 * Your Solution object will be instantiated and called as such:
 * Solution obj = new Solution(nums);
 * int param_1 = obj.pick(target);
 */