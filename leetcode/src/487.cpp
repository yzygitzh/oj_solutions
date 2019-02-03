class Solution {
public:
    int findMaxConsecutiveOnes(vector<int>& nums) {
        deque<int> oneCnt;
        int numsLen = nums.size();
        int maxOneLen = 1, currOneLen = 0;
        for (int i = 0; i < numsLen; i++) {
            if (nums[i] == 0) {
                if (currOneLen > 0) {
                    maxOneLen = max(maxOneLen, currOneLen + 1);
                    oneCnt.push_back(currOneLen);
                    if (oneCnt.size() > 2) oneCnt.pop_front();
                    if (oneCnt.size() == 2) {
                        maxOneLen = max(maxOneLen,
                                        oneCnt.front() + oneCnt.back() + 1);
                    }
                    currOneLen = 0;
                } else {
                    oneCnt.clear();
                }
            } else {
                currOneLen++;
            }
        }
        
        if (currOneLen > 0) {
            int needOne = currOneLen < numsLen ? 1 : 0;
            maxOneLen = max(maxOneLen, currOneLen + needOne);
            oneCnt.push_back(currOneLen);
            if (oneCnt.size() > 2) oneCnt.pop_front();
            if (oneCnt.size() == 2) {
                maxOneLen = max(maxOneLen,
                                oneCnt.front() + oneCnt.back() + 1);
            }
        }
        
        return maxOneLen;
    }
};