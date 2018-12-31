class Solution {
public:
    vector<int> productExceptSelf(vector<int>& nums) {
        int numsLen = nums.size();
        if (numsLen <= 1) return vector<int>();
        
        vector<int> result(numsLen, 1);
        
        int currProd;
        // 1,2,3,4 -> 1,1,2,6
        currProd = 1;
        for (int i = 1; i < numsLen; i++) {
            currProd *= nums[i - 1];
            result[i] *= currProd;
        }
        // 1,2,3,4 -> 24,12,4,1
        currProd = 1;
        for (int i = numsLen - 2; i >= 0; i--) {
            currProd *= nums[i + 1];
            result[i] *= currProd;
        }
        
        return result;
    }
};