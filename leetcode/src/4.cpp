class Solution {
public:
    double findMedianSortedArrays(vector<int>& nums1, vector<int>& nums2) {
        int len1 = nums1.size();
        int len2 = nums2.size();
        if (len1 > len2) {
            return findMedianSortedArrays(nums2, nums1);
        } else if (len1 == 0) {
            return (double)(nums2[len2 / 2] + nums2[(len2 - 1) / 2]) / 2;
        }
        
        // bin search idx in nums1
        int left = 0, right = len1;
        while (left + 1 < right) {
            // nums1[<mid1] and nums2[<mid2] is at left part
            int mid1 = (left + right) / 2;
            int mid2 = (len1 + len2) / 2 - mid1;
            if (mid1 - 1 >= 0 && mid2 < len2 && nums1[mid1 - 1] > nums2[mid2]) {
                right = mid1;
            } else {
                left = mid1;
            }
        }
        
        // first try left
        int idx1 = left, idx2 = (len1 + len2) / 2 - idx1;
        if ((idx1 - 1 < 0 || idx2 >= len2 || nums1[idx1 - 1] <= nums2[idx2]) &&
            (idx2 - 1 < 0 || idx1 >= len1 || nums2[idx2 - 1] <= nums1[idx1])) {
            idx1 = left, idx2 = (len1 + len2) / 2 - idx1;
        } else {
            idx1 = right, idx2 = (len1 + len2) / 2 - idx1;
        }
        
        if ((len1 + len2) % 2) {
            if (idx1 == len1) return nums2[idx2];
            return min(nums1[idx1], nums2[idx2]);
        } else {
            if (len1 == len2 && idx1 == 0) {
                return (double)(nums2[idx2 - 1] + nums1[idx1]) / 2;
            }
            if (len1 == len2 && idx1 == len1) {
                return (double)(nums1[idx1 - 1] + nums2[idx2]) / 2;
            }
            if (len1 < len2 && idx1 == 0) {
                return (double)(nums2[idx2 - 1] + min(nums1[idx1], nums2[idx2])) / 2;
            }
            if (len1 < len2 && idx1 == len1) {
                return (double)(max(nums1[idx1 - 1], nums2[idx2 - 1]) + nums2[idx2]) / 2;
            }
            // idx1 != 0 && idx1 != len1 && idx2 != 0 && idx2 != len2
            return (double)(max(nums1[idx1 - 1], nums2[idx2 - 1]) +
                            min(nums1[idx1], nums2[idx2])) / 2;
        }
    }
};