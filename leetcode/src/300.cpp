class Solution {
public:
    int lengthOfLIS(vector<int>& nums) {
        int numsLen = nums.size();
        if (numsLen == 0) return 0;
        
        vector<int> seqLen(numsLen, 0);
        int maxNum = 0;
        for (int i = 0; i < numsLen; i++) {
            if (nums[i] > maxNum) maxNum = nums[i];
        }
        vector<int> len2MinNum(numsLen, maxNum + 1);

        seqLen[0] = 1;
        len2MinNum[0] = nums[0];

        for (int i = 1; i < numsLen; i++) {
            // bin search in len2MinNum
            int left = 0, right = i - 1;
            while (left + 1 < right) {
                int mid = (left + right) / 2;
                if (len2MinNum[mid] <= nums[i]) {
                    left = mid;
                } else {
                    right = mid;
                }
            }
            // update seqLen
            if (nums[i] > len2MinNum[right]) {
                seqLen[i] = right + 2;
            } else if (nums[i] > len2MinNum[left]) {
                seqLen[i] = left + 2;
            } else {
                seqLen[i] = 1;
            }
            // update len2MinNum
            if (len2MinNum[seqLen[i] - 1] > nums[i]) {
                len2MinNum[seqLen[i] - 1] = nums[i];
            }
        }
        
        int maxLen = 1;
        for (int i = 0; i < numsLen; i++) {
            if (seqLen[i] > maxLen) maxLen = seqLen[i];
        }
        
        return maxLen;
    }
};