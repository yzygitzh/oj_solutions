class Solution {
public:
    int majorityElement(vector<int>& nums) {
        int numsLen = nums.size();
        int result = nums[0], resultCnt = 1;
        for (int i = 1; i < numsLen; i++) {
            if (nums[i] == result) {
                resultCnt++;
            } else {
                if (resultCnt == 0) {
                    result = nums[i];
                    resultCnt = 1;
                } else {
                    resultCnt--;
                }
            }
        }
        return result;
    }
};