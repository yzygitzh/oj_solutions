class Solution {
public:
    vector<int> nextGreaterElements(vector<int>& nums) {
        vector<int> longNums = nums;
        longNums.resize(nums.size() * 2);
        for (int i = 0; i < nums.size(); i++) {
            longNums[nums.size() + i] = nums[i];
        }
        // val, idx
        vector<pair<int, int>> numStack;
        vector<int> result(nums.size(), -1);
        int resultFilled = 0;
        for (int i = 0; i < longNums.size() &&
                            resultFilled < result.size(); i++) {
            while (!numStack.empty() &&
                   numStack.back().first < longNums[i]) {
                if (numStack.back().second < nums.size()) {
                    result[numStack.back().second] = longNums[i];
                    resultFilled++;
                }
                numStack.pop_back();
            }
            numStack.push_back(make_pair(longNums[i], i));
        }
        return result;
    }
};