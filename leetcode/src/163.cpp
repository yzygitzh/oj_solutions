class Solution {
public:
    string genInterval(long long lower, long long upper) {
        if (lower == upper) return to_string(lower);
        else return to_string(lower) + "->" + to_string(upper);
    }
    
    vector<string> findMissingRanges(vector<int>& nums, int lower, int upper) {
        int numsLen = nums.size();
        if (numsLen == 0) return vector<string>{genInterval(lower, upper)};
        vector<string> result;
        for (int i = 0; i < numsLen; i++) {
            if (i == 0) {
                if (nums[i] > lower) {
                    result.push_back(genInterval(lower,
                                                 (long long)nums[i] - 1));
                }
            } else if ((long long)nums[i] > (long long)nums[i - 1] + 1) {
                result.push_back(genInterval((long long)nums[i - 1] + 1,
                                             (long long)nums[i] - 1));
            }
            if (i + 1 == numsLen) {
                if (nums[i] < upper) {
                    result.push_back(genInterval((long long)nums[i] + 1,
                                                 upper));
                }
            }
        }
        return result;
    }
};