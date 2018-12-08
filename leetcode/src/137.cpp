class Solution {
public:
    int singleNumber(vector<int>& nums) {
        // use bit DFA
        // bit1,bit2  incoming  result
        //        00         0      00
        //        01         0      01   *
        //        10         0      10 *
        //        00         1      01   *
        //        01         1      10 *
        //        10         1      00
        
        int bit1 = 0, bit2 = 0;
        int numsLen = nums.size();
        for (int i = 0; i < numsLen; i++) {
            int tmpBit1 = (bit1 & (~bit2) & (~nums[i])) | ((~bit1) & bit2 & nums[i]);
            int tmpBit2 = ((~bit1) & bit2 & (~nums[i])) | ((~bit1) & (~bit2) & nums[i]);
            bit1 = tmpBit1;
            bit2 = tmpBit2;
        }
        return bit2;
    }
};