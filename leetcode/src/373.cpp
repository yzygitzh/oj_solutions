class Solution {
public:
    class PairClass {
    public:
        int num1, num2, idx1, idx2;
        PairClass(int _n1, int _n2, int _i1, int _i2)
            : num1(_n1), num2(_n2), idx1(_i1), idx2(_i2) {}
        bool operator< (const PairClass &p) const {
            return num1 + num2 > p.num1 + p.num2;
        }
    };
    
    vector<pair<int, int>> kSmallestPairs(vector<int>& nums1,
                                          vector<int>& nums2, int k) {
        vector<pair<int, int>> result;
        int nums1Len = nums1.size();
        int nums2Len = nums2.size();
        if (nums1Len == 0 || nums2Len == 0) return result;
        priority_queue<PairClass> minHeap;
        minHeap.push(PairClass(nums1[0], nums2[0], 0, 0));
        set<pair<int, int>> visited{make_pair(0, 0)};
        while (result.size() < k && !minHeap.empty()) {
            PairClass currMin = minHeap.top();
            minHeap.pop();
            result.push_back(make_pair(currMin.num1, currMin.num2));
            if (currMin.idx1 + 1 < nums1Len &&
                !visited.count(make_pair(currMin.idx1 + 1, currMin.idx2))) {
                visited.insert(make_pair(currMin.idx1 + 1, currMin.idx2));
                minHeap.push(PairClass(nums1[currMin.idx1 + 1], nums2[currMin.idx2],
                                       currMin.idx1 + 1, currMin.idx2));
            }
            if (currMin.idx2 + 1 < nums2Len &&
                !visited.count(make_pair(currMin.idx1, currMin.idx2 + 1))) {
                visited.insert(make_pair(currMin.idx1, currMin.idx2 + 1));
                minHeap.push(PairClass(nums1[currMin.idx1], nums2[currMin.idx2 + 1],
                                       currMin.idx1, currMin.idx2 + 1));
            }
        }
        return result;
    }
};