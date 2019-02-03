class Solution {
public:
    bool circularArrayLoop(vector<int>& nums) {
        int numsLen = nums.size();
        for (int i = 0; i < numsLen; i++) {
            int slowIdx = i, fastIdx = slowIdx;
            long long firstNum = nums[slowIdx];
            if (firstNum == 0) continue;
            while (true) {
                slowIdx = (slowIdx + nums[slowIdx] + numsLen) % numsLen;
                if (firstNum * nums[slowIdx] <= 0) break;
                
                for (int j = 0; j < 2; j++) {
                    fastIdx = (fastIdx + nums[fastIdx] + numsLen) % numsLen;
                    if (firstNum * nums[fastIdx] <= 0) break;
                }
                
                if (slowIdx == fastIdx) {
                    if (slowIdx != (slowIdx + nums[slowIdx] + numsLen) % numsLen) {
                        return true;
                    } else {
                        break;
                    }
                }
            }
            slowIdx = i;
            while (nums[slowIdx] != 0) {
                int oldSlowIdx = slowIdx;
                slowIdx = (slowIdx + nums[slowIdx] + numsLen) % numsLen;
                nums[oldSlowIdx] = 0;
            }
        }
        return false;
    }
};