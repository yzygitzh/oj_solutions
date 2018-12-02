class Solution {
public:
    int maxProduct(vector<int>& nums) {
        int numsLen = nums.size();
        if (numsLen == 0) return 0;
        
        // split nums by 0
        vector<vector<int> > nonZeroNums;
        vector<int> currNums;
        for (int i = 0; i < numsLen; i++) {
            if (nums[i] == 0) {
                if (currNums.size() > 0) {
                    nonZeroNums.push_back(currNums);
                }
                currNums.clear();
            } else {
                currNums.push_back(nums[i]);
            }
        }
        if (currNums.size() > 0) {
            nonZeroNums.push_back(currNums);
        }
        
        int arrayNum = nonZeroNums.size();
        int maxProduct;
        if (arrayNum == 0) {
            return 0;
        } else if (arrayNum == 1) {
            maxProduct = nums[0];
        } else {
            maxProduct = 0;
        }
        
        for (int i = 0; i < arrayNum; i++) {
            vector<int> currArray = nonZeroNums[i];
            int arraySize = currArray.size();
            int arrayProduct = 1;
            for (int j = 0; j < arraySize; j++) {
                arrayProduct *= currArray[j];
            }
            if (arrayProduct > maxProduct) maxProduct = arrayProduct;
            if (arrayProduct < 0 && arraySize > 1) {
                int idx, currProduct;
                // from front
                idx = 0;
                currProduct = arrayProduct;
                while (currArray[idx] > 0) currProduct /= currArray[idx++];
                currProduct /= currArray[idx];
                if (currProduct > maxProduct) maxProduct = currProduct;
                // from end
                idx = arraySize - 1;
                currProduct = arrayProduct;
                while (currArray[idx] > 0) currProduct /= currArray[idx--];
                currProduct /= currArray[idx];
                if (currProduct > maxProduct) maxProduct = currProduct;
            }
        }
        
        return maxProduct;
    }
};