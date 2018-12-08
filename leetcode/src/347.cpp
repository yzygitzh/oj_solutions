class Solution {
public:
    vector<int> topKFrequent(vector<int>& nums, int k) {
        int numsLen = nums.size();
        unordered_map<int, int> num2count;
        for (int i = 0; i < numsLen; i++) {
            num2count[nums[i]]++;
        }
        priority_queue
            <pair<int, int>,
             vector<pair<int, int> >,
             greater<pair<int, int> > > minHeap;
        for (unordered_map<int, int>::iterator itr = num2count.begin();
             itr != num2count.end(); ++itr) {
            if (minHeap.size() < k) {
                minHeap.push(make_pair(itr->second, itr->first));
            } else if (itr->second > minHeap.top().first) {
                minHeap.pop();
                minHeap.push(make_pair(itr->second, itr->first));
            }
        }
        vector<int> result;
        while (minHeap.size() > 0) {
            result.push_back(minHeap.top().second);
            minHeap.pop();
        }
        return result;
    }
};