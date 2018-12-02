class Solution {
public:
    vector<vector<int>> permute(vector<int>& nums) {
        vector<vector<int> > result;
        int numsLen = nums.size();
        if (numsLen == 0) return result;
        vector<int> visited(numsLen, 0);
        vector<int> partResult;
        genPermute(numsLen, nums, visited, partResult, result);
        return result;
    }
    
    void genPermute(int len, vector<int>& nums, vector<int>& visited,
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
                }
            }
        }
    }
};