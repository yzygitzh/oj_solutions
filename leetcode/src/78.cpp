class Solution {
public:
    vector<vector<int>> subsets(vector<int>& nums) {
        vector<vector<int>> finalResult;
        vector<int> partResult;
        int numsLen = nums.size();
        genSubset(numsLen, 0, nums, partResult, finalResult);
        return finalResult;
    }
    
    void genSubset(int restLen, int firstTry, vector<int> &nums,
                   vector<int> &partResult, vector<vector<int>> &result) {
        result.push_back(partResult);
        if (restLen > 0) {
            int numsLen = nums.size();
            for (int i = firstTry; i < numsLen; i++) {
                partResult.push_back(nums[i]);
                genSubset(restLen - 1, i + 1, nums, partResult, result);
                partResult.pop_back();
            }
        }
    }
};