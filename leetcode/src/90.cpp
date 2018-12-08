class Solution {
public:
    vector<vector<int>> subsetsWithDup(vector<int>& nums) {
        int numsLen = nums.size();
        vector<vector<int> > result;
        vector<int> partResult;
        sort(nums.begin(), nums.end());
        genSubset(numsLen, 0, nums, partResult, result);
        return result;
    }
    
    void genSubset(int restLen, int startIdx, vector<int> &nums,
                   vector<int> &partResult, vector<vector<int> > &result) {
        result.push_back(partResult);
        if (restLen > 0) {
            int numsLen = nums.size();
            for (int i = startIdx; i < numsLen; i++) {
                partResult.push_back(nums[i]);
                genSubset(restLen - 1, i + 1, nums, partResult, result);
                partResult.pop_back();
                while (i + 1 < numsLen && nums[i] == nums[i + 1]) i++;
            }
        }
    }
};