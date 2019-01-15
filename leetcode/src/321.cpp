class Solution {
public:
    vector<int> maxNumber(vector<int>& nums1, vector<int>& nums2, int k) {
        // mono stack
        
        int nums1Len = nums1.size();
        int nums2Len = nums2.size();
        
        vector<int> result;
        for (int i = 0; i <= k; i++) {
            int len1 = i, len2 = k - i;
            if (len1 > nums1Len || len2 > nums2Len) continue;
            vector<int> stack1, stack2;
            for (int j = 0; j < nums1Len; j++) {
                while (stack1.size() + nums1Len - j > len1 && !stack1.empty()
                       && nums1[j] > *stack1.rbegin()) {
                    stack1.pop_back();
                }
                stack1.push_back(nums1[j]);
            }
            for (int j = 0; j < nums2Len; j++) {
                while (stack2.size() + nums2Len - j > len2 && !stack2.empty()
                       && nums2[j] > *stack2.rbegin()) {
                    stack2.pop_back();
                }
                stack2.push_back(nums2[j]);
            }
            stack1.push_back(-1);
            stack2.push_back(-1);
            vector<int> tmpResult;
            int idx1 = 0, idx2 = 0;
            while (idx1 + idx2 < len1 + len2) {
                if (idx2 == len2 || stack1[idx1] > stack2[idx2]) {
                    tmpResult.push_back(stack1[idx1]);
                    idx1++;
                } else if (idx1 == len1 || stack1[idx1] < stack2[idx2]) {
                    tmpResult.push_back(stack2[idx2]);
                    idx2++;
                } else {
                    int tmpIdx1 = idx1, tmpIdx2 = idx2;
                    while (stack1[tmpIdx1] == stack2[tmpIdx2]) {
                        tmpIdx1++;
                        tmpIdx2++;
                    }
                    if (stack1[tmpIdx1] > stack2[tmpIdx2]) {
                        tmpResult.push_back(stack1[idx1]);
                        idx1++;
                    } else {
                        tmpResult.push_back(stack2[idx2]);
                        idx2++;
                    }
                }
            }
            if (i == 0) {
                result = tmpResult;
            } else if (tmpResult > result) {
                result = tmpResult;
            }
        }
        
        return result;
    }
};