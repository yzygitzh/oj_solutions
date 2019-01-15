class Solution {
public:
    vector<int> sortTransformedArray(vector<int>& nums, int a, int b, int c) {
        // the root is -b/2a.
        int numsLen = nums.size();
        vector<int> result;
        
        if (a == 0) {
            if (b < 0) {
                for (int i = numsLen - 1; i >= 0; i--) {
                    result.push_back(b * nums[i] + c);
                }
            } else {
                for (int i = 0; i < numsLen; i++) {
                    result.push_back(b * nums[i] + c);
                }
            }
        } else {
            double root = -(double)b / a / 2;
            // find root index
            int rootIdx = 0;
            while (rootIdx < numsLen && nums[rootIdx] < root) rootIdx++;
            int left = rootIdx - 1, right = rootIdx;
            while (left >= 0 || right < numsLen) {
                if (left < 0) {
                    result.push_back(a * nums[right] * nums[right] + b * nums[right] + c);
                    right++;
                } else if (right >= numsLen) {
                    result.push_back(a * nums[left] * nums[left] + b * nums[left] + c);
                    left--;
                } else {
                    if (nums[left] + nums[right] < 2 * root) {
                        result.push_back(a * nums[right] * nums[right] + b * nums[right] + c);
                        right++;
                    } else {
                        result.push_back(a * nums[left] * nums[left] + b * nums[left] + c);
                        left--;
                    }
                }
            }
            if (a < 0) {
                reverse(result.begin(), result.end());
            }
        }
        
        return result;
    }
};