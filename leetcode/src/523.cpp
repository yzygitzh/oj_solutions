class Solution {
public:
    bool checkSubarraySum(vector<int>& nums, int k) {
        if (k < 0) {
            k = -k;
        }
        unordered_map<int, int> prefixSumToMinIdx;
        prefixSumToMinIdx[0] = 0;
        int prefixSum = 0;
        for (int i = 1; i <= nums.size(); i++) {
            prefixSum += nums[i - 1];
            if (k > 0) {
                prefixSum %= k;
            }
            if (prefixSumToMinIdx.find(prefixSum) == prefixSumToMinIdx.end()) {
                prefixSumToMinIdx[prefixSum] = i;
            }
            if (prefixSumToMinIdx.find(prefixSum) != prefixSumToMinIdx.end() &&
                prefixSumToMinIdx[prefixSum] + 2 <= i) {
                return true;
            }
        }
        return false;
    }
};