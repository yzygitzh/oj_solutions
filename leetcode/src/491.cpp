class Solution {
public:
    
    vector<vector<int>> findSubsequences(vector<int>& nums) {
        int numsLen = nums.size();
        vector<vector<int>> nextIdx(numsLen);
        set<vector<int>> result;
        for (int i = 0; i < numsLen; i++) {
            for (int j = i + 1; j < numsLen; j++) {
                if (nums[i] <= nums[j]) {
                    nextIdx[i].push_back(j);
                }
            }
        }
        vector<int> partResult;
        for (int i = 0; i < numsLen; i++) {
            dfs(i, nums, nextIdx, partResult, result);
        }
        return vector<vector<int>>(result.begin(), result.end());
    }
    
    void dfs(int idx, vector<int>& nums, vector<vector<int>>& nextIdx,
             vector<int>& partResult, set<vector<int>>& result) {
        partResult.push_back(nums[idx]);
        if (partResult.size() >= 2) result.insert(partResult);
        for (auto itr = nextIdx[idx].begin(); itr != nextIdx[idx].end(); ++itr) {
            dfs(*itr, nums, nextIdx, partResult, result);
        }
        partResult.pop_back();
    }
};