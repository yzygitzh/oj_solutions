class Solution {
public:
    long long getAbs(long long x) {
        return x < 0 ? -x : x;
    }
    
    bool containsNearbyAlmostDuplicate(vector<int>& nums, int k, int t) {
        int numsLen = nums.size();
        if (numsLen == 0) return false;
        if (k <= 0 || t < 0) return false;
        
        int left = 0, right = 0;
        set<long long> window{nums[0]};
        for (int i = 1; i < numsLen; i++) {
            right = i;
            if (right - left > k) {
                window.erase(nums[left]);
                left++;
            }
            
            set<long long>::iterator itr = window.lower_bound(nums[right]);
            
            if (itr != window.end() && getAbs(nums[right] - *itr) <= (long long)t) return true;
            --itr;
            if (itr != window.end() && getAbs(nums[right] - *itr) <= (long long)t) return true;
            if (getAbs(nums[right] - *window.rbegin()) <= (long long)t) return true;
            
            window.insert(nums[right]);
        }
        
        return false;
    }
};