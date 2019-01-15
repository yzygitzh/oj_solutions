class Solution {
public:
    int maxSubArrayLen(vector<int>& nums, int k) {
        int numsLen = nums.size();
        if (numsLen == 0) return 0;
        
        unordered_map<int, vector<int>> prefixSumToIdx;
        vector<int> prefixSums(numsLen + 1, 0);
        int sum = 0;
        prefixSumToIdx[0].push_back(0);
        for (int i = 0; i < numsLen; i++) {
            sum += nums[i];
            prefixSums[i + 1] = sum;
            prefixSumToIdx[sum].push_back(i + 1);
        }
        
        int maxLen = 0;
        for (auto itr = prefixSumToIdx.begin(); itr != prefixSumToIdx.end(); ++itr) {
            if (prefixSumToIdx.find(itr->first - k) != prefixSumToIdx.end()) {
                maxLen = max(maxLen,
                             *itr->second.rbegin() -
                             *prefixSumToIdx[itr->first - k].begin());
            }
        }
        return maxLen;
    }
};