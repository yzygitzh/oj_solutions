class Solution {
public:
    vector<pair<int, int>> kSmallestPairs(vector<int>& nums1, vector<int>& nums2, int k) {
        vector<pair<int, int> > result;
        int nums1Len = nums1.size();
        int nums2Len = nums2.size();
        if (k == 0 || nums1Len == 0 || nums2Len == 0) return result;
        if (k > nums1Len * nums2Len) k = nums1Len * nums2Len;
        
        // <nums1Idx, nums2Idx>
        unordered_map<int, int> nums2Idx;
        // <sum, nums1Idx>
        priority_queue<pair<int, int>, vector<pair<int, int> >,
                       greater<pair<int, int> > > minHeap;
        
        for (int i = 0; i < nums1Len; i++) {
            minHeap.push(make_pair(nums1[i] + nums2[0], i));
        }
        
        while (result.size() < k) {
            pair<int, int> minSum = minHeap.top();
            minHeap.pop();
            result.push_back(make_pair(nums1[minSum.second],
                                       nums2[nums2Idx[minSum.second]]));
            nums2Idx[minSum.second]++;
            if (nums2Idx[minSum.second] < nums2Len) {
                minHeap.push(make_pair(nums1[minSum.second] +
                                       nums2[nums2Idx[minSum.second]],
                                       minSum.second));
            }
        }
        
        return result;
    }
};