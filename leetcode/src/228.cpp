class Solution {
public:
    vector<string> summaryRanges(vector<int>& nums) {
        vector<string> result;
        int numsLen = nums.size();
        if (numsLen == 0) return result;
        
        int left = nums[0], right = nums[0];
        for (int i = 1; i < numsLen; i++) {
            if (nums[i] == nums[i - 1] + 1) {
                right = nums[i];
            } else {
                string rangeStr;
                if (left == right) {
                    rangeStr += to_string(left);
                } else {
                    rangeStr += to_string(left);
                    rangeStr += "->";
                    rangeStr += to_string(right);
                }
                result.push_back(rangeStr);
                left = right = nums[i];
            }
        }
        string rangeStr;
        if (left == right) {
            rangeStr += to_string(left);
        } else {
            rangeStr += to_string(left);
            rangeStr += "->";
            rangeStr += to_string(right);
        }
        result.push_back(rangeStr);
        return result;
    }
};