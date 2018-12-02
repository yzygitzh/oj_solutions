class Solution {
public:
    vector<int> largestDivisibleSubset(vector<int>& nums) {
        // set {p1, p2, p3...} must satisify that
        // p1 | p2 | p3 | ...
        int numsLen = nums.size();
        if (numsLen <= 1) return nums;
        sort(nums.begin(), nums.end());
        vector<int> setSize(numsLen, 0);
        vector<int> prevIdx(numsLen, 0);
        setSize[0] = 1;
        prevIdx[0] = -1;
        int maxIdx = 0;
        for (int i = 1; i < numsLen; i++) {
            int maxSize = 1;
            int currMaxIdx = -1;
            for (int j = 0; j < i; j++) {
                if (nums[i] % nums[j] == 0) {
                    int currSize = setSize[j] + 1;
                    if (currSize > maxSize) {
                        maxSize = currSize;
                        currMaxIdx = j;
                    }
                }
            }
            setSize[i] = maxSize;
            prevIdx[i] = currMaxIdx;
            if (setSize[i] > setSize[maxIdx]) maxIdx = i;
        }
        
        vector<int> answer;
        int currIdx = maxIdx;
        while (currIdx >= 0) {
            answer.push_back(nums[currIdx]);
            currIdx = prevIdx[currIdx];
        }
        sort(answer.begin(), answer.end());
        return answer;
    }
};