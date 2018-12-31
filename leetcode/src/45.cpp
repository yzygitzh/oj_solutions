class Solution {
public:
    int getMax(int a, int b) {
        return a > b ? a : b;
    }
    
    int jump(vector<int>& nums) {
        int numsLen = nums.size();
        // assume we have F[i] indicating
        // how many steps to get i-th index
        // obvious that F[i] is monotously increasing
        
        vector<int> steps(numsLen, 0);
        int right = 0;
        for (int i = 0; i < numsLen; i++) {
            for (int j = right + 1; j <= i + nums[i]; j++) {
                if (j >= numsLen) break;
                steps[j] = steps[i] + 1;
            }
            right = getMax(i + nums[i], right);
        }
        return steps[numsLen - 1];
    }
};