class Solution {
public:
    int minPatches(vector<int>& nums, int n) {
        // greedy
        int numsLen = nums.size();
        int count = 0;
        long long seqEnd = 1, lN = (long long)n;
        
        int idx = 0;
        while (seqEnd <= lN) {
            if (idx < numsLen && (long long)nums[idx] <= seqEnd) {
                seqEnd += (long long)nums[idx];
                idx++;
            } else {
                count++;
                seqEnd += seqEnd;
            }
        }
        
        return count;
    }
};