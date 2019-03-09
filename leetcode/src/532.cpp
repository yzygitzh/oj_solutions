class Solution {
public:
    int findPairs(vector<int>& nums, int k) {
        if (k < 0) return 0;
        unordered_map<int, int> numCnt;
        for (auto i : nums) {
            numCnt[i]++;
        }
        int result = 0;
        for (auto itr = numCnt.begin(); itr != numCnt.end(); ++itr) {
            if (numCnt.count(itr->first - k) &&
                (k == 0 && itr->second > 1 || k != 0)) result++;
        }
        return result;
    }
};