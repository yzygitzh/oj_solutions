class Solution {
public:
    int combinationSum4(vector<int>& nums, int target) {
        int numsLen = nums.size();
        if (numsLen == 0) return 0;
        sort(nums.begin(), nums.end());
        // F[M]: number of sequences by which M can be summed
        // F[M] = F[M-val(1)] + F[M-val(2)] + ... + F[M-val(N)]
        vector<int> sums(target + 1, 0);
        sums[0] = 1;
        for (int i = 1; i <= target; i++) {
            for (int j = 0; j < numsLen; j++) {
                if (i - nums[j] >= 0) {
                    sums[i] += sums[i - nums[j]];
                }
            }
        }
        return sums[target];
    }
};