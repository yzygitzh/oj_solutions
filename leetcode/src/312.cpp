class Solution {
public:
    int maxCoins(vector<int>& nums) {
        // memo[l][r]: maximum point got by eliminating [l + 1, r - 1]
        int numsLen = nums.size();
        vector<int> newNums{1};
        for (int i = 0; i < numsLen; i++) {
            if (nums[i] != 0) newNums.push_back(nums[i]);
        }
        newNums.push_back(1);
        int newNumsLen = newNums.size();
        if (newNumsLen == 2) return 0;
        vector<vector<int> > memo(newNumsLen, vector<int>(newNumsLen, -1));
        return dfs(newNums, 0, newNumsLen - 1, memo);
    }
    
    int dfs(vector<int> &nums, int left, int right, vector<vector<int> > &memo) {
        if (memo[left][right] != -1) return memo[left][right];

        int maxResult = 0;
        for (int i = left + 1; i < right; i++) {
            int leftResult = dfs(nums, left, i, memo);
            int rightResult = dfs(nums, i, right, memo);
            int totalResult = leftResult + rightResult +
                              nums[left] * nums[right] * nums[i];
            if (totalResult > maxResult) maxResult = totalResult;
        }
        memo[left][right] = maxResult;
        
        return memo[left][right];
    }
};