class Solution {
public:
    double findMedianSortedArrays(vector<int>& nums1, vector<int>& nums2) {
        // binary search in nums1
        // nums2's position is determined by nums1's index
        
        int nums1Len = nums1.size();
        int nums2Len = nums2.size();
        if (nums1Len == nums2Len && nums1Len == 0) return 0.0;
        if (nums1Len == 0) return nums2Len % 2 ?
                                  nums2[nums2Len / 2] :
                                  (double)(nums2[nums2Len / 2 - 1] +
                                           nums2[nums2Len / 2]) / 2;
        if (nums2Len == 0) return nums1Len % 2 ?
                                  nums1[nums1Len / 2] :
                                  (double)(nums1[nums1Len / 2 - 1] +
                                           nums1[nums1Len / 2]) / 2;
        
        if (nums1Len >= nums2Len) {
            return doFind(nums2, nums1);
        } else {
            return doFind(nums1, nums2);
        }
    }
    
    double getMax(double a, double b) {
        return a > b ? a : b;
    }
    
    double getMin(double a, double b) {
        return a < b ? a : b;
    }
    
    double doFind(vector<int>& nums1, vector<int>& nums2) {
        // nusm1Len <= nums2Len
        int nums1Len = nums1.size();
        int nums2Len = nums2.size();
        
        // min(nums1) >= max(nums2) or vice versa.
        if (nums1[nums1Len - 1] <= nums2[0]) {
            if (nums1Len == nums2Len) return (double)(nums1[nums1Len - 1] + nums2[0]) / 2;
            return (nums1Len + nums2Len) % 2 ?
                   nums2[(nums1Len + nums2Len) / 2 - nums1Len] :
                   (double)(nums2[(nums1Len + nums2Len) / 2 - nums1Len - 1] +
                            nums2[(nums1Len + nums2Len) / 2 - nums1Len]) / 2;
        }
        if (nums2[nums2Len - 1] <= nums1[0]) {
            if (nums1Len == nums2Len) return (double)(nums2[nums2Len - 1] + nums1[0]) / 2;
            return (nums1Len + nums2Len) % 2 ?
                   nums2[(nums1Len + nums2Len) / 2] :
                   (double)(nums2[(nums1Len + nums2Len) / 2 - 1] +
                            nums2[(nums1Len + nums2Len) / 2]) / 2;
        }
        
        int left = 0, right = nums1Len - 1;
        int nums1Idx, nums2Idx;
        while (left + 1 < right) {
            // [2,3], [4,5,6]
            // [2,3,4], [5,6,7]
            nums1Idx = (left + right) / 2;
            nums2Idx = (nums1Len + nums2Len) / 2 - nums1Idx - 1;
            // ensure that numbers being left of these two numbers
            // all <= right numbers
            if ((nums1Idx + 1 == nums1Len || nums1[nums1Idx + 1] >= nums2[nums2Idx]) &&
                (nums2Idx + 1 == nums2Len || nums2[nums2Idx + 1] >= nums1[nums1Idx])) {
                if ((nums1Len + nums2Len) % 2) {
                    return getMax(nums1[nums1Idx], nums2[nums2Idx]);
                }
                else {
                    double max1 = getMax(nums1[nums1Idx], nums2[nums2Idx]);
                    double max2 = getMin(nums1[nums1Idx], nums2[nums2Idx]);
                    if (nums1Idx - 1 >= 0) max2 = getMax(nums1[nums1Idx - 1], max2);
                    if (nums2Idx - 1 >= 0) max2 = getMax(nums2[nums2Idx - 1], max2);
                    return (max1 + max2) / 2;
                }
            }
            if (nums1[nums1Idx + 1] < nums2[nums2Idx]) left = nums1Idx;
            if (nums2[nums2Idx + 1] < nums1[nums1Idx]) right = nums1Idx;
        }

        // try left
        nums1Idx = left;
        nums2Idx = (nums1Len + nums2Len) / 2 - nums1Idx - 1;
        if ((nums1Idx + 1 == nums1Len || nums1[nums1Idx + 1] >= nums2[nums2Idx]) &&
            (nums2Idx + 1 == nums2Len || nums2[nums2Idx + 1] >= nums1[nums1Idx])) {
            if ((nums1Len + nums2Len) % 2) {
                return getMax(nums1[nums1Idx], nums2[nums2Idx]);
            }
            else {
                double max1 = getMax(nums1[nums1Idx], nums2[nums2Idx]);
                double max2 = getMin(nums1[nums1Idx], nums2[nums2Idx]);
                if (nums1Idx - 1 >= 0) max2 = getMax(nums1[nums1Idx - 1], max2);
                if (nums2Idx - 1 >= 0) max2 = getMax(nums2[nums2Idx - 1], max2);
                return (max1 + max2) / 2;
            }
        }
        // try right
        nums1Idx = right;
        nums2Idx = (nums1Len + nums2Len) / 2 - nums1Idx - 1;
        if ((nums1Idx + 1 == nums1Len || nums1[nums1Idx + 1] >= nums2[nums2Idx]) &&
            (nums2Idx + 1 == nums2Len || nums2[nums2Idx + 1] >= nums1[nums1Idx])) {
            if ((nums1Len + nums2Len) % 2) {
                return getMax(nums1[nums1Idx], nums2[nums2Idx]);
            }
            else {
                double max1 = getMax(nums1[nums1Idx], nums2[nums2Idx]);
                double max2 = getMin(nums1[nums1Idx], nums2[nums2Idx]);
                if (nums1Idx - 1 >= 0) max2 = getMax(nums1[nums1Idx - 1], max2);
                if (nums2Idx - 1 >= 0) max2 = getMax(nums2[nums2Idx - 1], max2);
                return (max1 + max2) / 2;
            }
        }
        // minimum in shorter array is too large
        return (nums1Len + nums2Len) % 2 ?
                nums2[(nums1Len + nums2Len) / 2 ] :
                (double)(nums2[(nums1Len + nums2Len) / 2 - 1] +
                         nums2[(nums1Len + nums2Len) / 2]) / 2;
    }
};