class Solution {
public:
    int reversePairs(vector<int>& nums) {
        // do merge sort
        int numsLen = nums.size();
        if (numsLen == 0) return 0;
        return mergeSort(nums, 0, numsLen - 1);
    }
    
    int mergeSort(vector<int>& nums, int left, int right) {
        if (left == right) {
            return 0;
        } else {
            int mid = (left + right) / 2;
            int leftCnt = mergeSort(nums, left, mid);
            int rightCnt = mergeSort(nums, mid + 1, right);
            // calculate cross-left-right pairs
            int crossCnt = 0;
            int lIdx = left, rIdx = mid + 1;
            while (lIdx <= mid) {
                while (rIdx <= right &&
                       (long long)nums[lIdx] > (long long)nums[rIdx] * 2LL) {
                    rIdx++;
                }
                crossCnt += rIdx - mid - 1;
                lIdx++;
            }
            // merge array
            vector<int> merged;
            lIdx = left, rIdx = mid + 1;
            while (lIdx <= mid || rIdx <= right) {
                if (lIdx == mid + 1) merged.push_back(nums[rIdx++]);
                else if (rIdx == right + 1) merged.push_back(nums[lIdx++]);
                else if (nums[lIdx] < nums[rIdx]) merged.push_back(nums[lIdx++]);
                else merged.push_back(nums[rIdx++]);
            }
            for (int i = 0; i < right - left + 1; i++) {
                nums[left + i] = merged[i];
            }
            return leftCnt + rightCnt + crossCnt;
        }
    }
};