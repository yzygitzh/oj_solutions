class Solution {
public:
    vector<int> maxSlidingWindow(vector<int>& nums, int k) {
        int numsLen = nums.size();
        deque<pair<int, int> > monoQueue;
        vector<int> result;
        for (int i = 0; i < numsLen; i++) {
            if (!monoQueue.empty() && monoQueue.front().second <= i - k) {
                monoQueue.pop_front();
            }
            while (!monoQueue.empty() && nums[i] >= monoQueue.back().first) {
                monoQueue.pop_back();
            }
            monoQueue.push_back(make_pair(nums[i], i));
            if (i >= k - 1) result.push_back(monoQueue.front().first);
        }
        return result;
    }
};