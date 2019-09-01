class Solution {
public:
    bool increasingTriplet(vector<int>& nums) {
        if (nums.size() == 0) {
            return false;
        }
        
        int k = 3;
        vector<int> currMin(k + 1, 0x7FFFFFFF); // min end of length k
        currMin[0] = (1 << 31);
        
        for (int i = 0; i < nums.size(); i++) {
            for (int j = k; j >= 1; j--) {
                if (currMin[j - 1] < nums[i]) {
                    currMin[j] = min(currMin[j], nums[i]);
                }
            }
            if (currMin[k] < 0x7FFFFFFF) {
                return true;
            }
        }
        return false;
    }
};