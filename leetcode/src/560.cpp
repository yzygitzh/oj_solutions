class Solution {
public:
    int subarraySum(vector<int>& nums, int k) {
        unordered_map<int, int> prefixSumCnt;
        prefixSumCnt[0] = 1;
        int prefixSum = 0, result = 0;
        for (auto num : nums) {
            prefixSum += num;
            result += prefixSumCnt[prefixSum - k];
            prefixSumCnt[prefixSum]++;
        }
        return result;
    }
};