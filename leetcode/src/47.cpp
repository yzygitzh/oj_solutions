class Solution {
public:
    vector<vector<int>> permuteUnique(vector<int>& nums) {
        int numsLen = nums.size();
        if (numsLen == 0) return vector<vector<int> >();
        
        sort(nums.begin(), nums.end());
        vector<vector<int> > uniqResults;
        vector<int> visited(numsLen, 0), partResult;
        genPermute(numsLen, nums, visited, partResult, uniqResults);
        return uniqResults;
    }
    
    void genPermute(int len,
                    vector<int>& nums, vector<int>& visited,
                    vector<int>& partResult, vector<vector<int> >& result) {
        if (len == 0) {
            result.push_back(partResult);
        } else {
            int numsLen = nums.size();
            for (int i = 0; i < numsLen; i++) {
                if (!visited[i]) {
                    visited[i] = 1;
                    partResult.push_back(nums[i]);
                    genPermute(len - 1, nums, visited, partResult, result);
                    partResult.pop_back();
                    visited[i] = 0;
                    while (i + 1 < numsLen && nums[i] == nums[i + 1]) i++;
                }
            }
        }
    }
};