class Solution {
public:
    int lowbit(int x) {
        return (x & (-x));
    }
    
    void changeBIT(int idx, int delta, vector<int> &bitArray) {
        int bitArrayLen = bitArray.size();
        while (idx < bitArrayLen) {
            bitArray[idx] += delta;
            idx += lowbit(idx);
        }
    }
    
    int getBIT(int idx, vector<int> &bitArray) {
        int result = 0;
        while (idx) {
            result += bitArray[idx];
            idx -= lowbit(idx);
        }
        return result;
    }
    
    vector<int> countSmaller(vector<int>& nums) {
        // use BIT
        map<int, int> numsCnt;
        int numsLen = nums.size();
        for (int i = 0; i < numsLen; i++) {
            numsCnt[nums[i]]++;
        }
        map<int, int> num2Idx;
        int idx = 1;
        for (map<int, int>::iterator itr = numsCnt.begin();
             itr != numsCnt.end(); ++itr) {
            num2Idx[itr->first] = idx;
            idx++;
        }
        
        vector<int> bitArray(idx, 0);
        vector<int> result(numsLen, 0);
        
        // add from last to first
        for (int i = numsLen - 2; i >= 0; i--) {
            changeBIT(num2Idx[nums[i + 1]], 1, bitArray);
            result[i] = getBIT(num2Idx[nums[i]] - 1, bitArray);
        }
        return result;
    }
};