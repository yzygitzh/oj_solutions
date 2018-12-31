class Solution {
public:
    
    int longestConsecutive(vector<int>& nums) {
        int numsLen = nums.size();
        if (numsLen <= 1) return numsLen;
        
        unordered_set<int> numsSet;
        for (int i = 0; i < numsLen; i++) numsSet.insert(nums[i]);
        
        int maxLen = 0;
        while (numsSet.size() > 0) {
            int seed = *numsSet.begin();
            numsSet.erase(seed);
            int left = seed, right = seed;
            bool changed = true;
            while (changed) {
                changed = false;
                if (numsSet.find(left - 1) != numsSet.end()) {
                    changed = true;
                    numsSet.erase(left--);
                }
                if (numsSet.find(right + 1) != numsSet.end()) {
                    changed = true;
                    numsSet.erase(right++);
                }
            }
            if (right - left + 1 > maxLen) maxLen = right - left + 1;
        }
        
        return maxLen;
    }
};