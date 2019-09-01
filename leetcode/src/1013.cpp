class Solution {
public:
    bool canThreePartsEqualSum(vector<int>& A) {
        // first get sum
        int ASum = 0;
        for (int i : A) ASum += i;
        if (ASum % 3) return false;
        int target = ASum / 3;
        // then get prefix sum and postfix sum
        int ALen = A.size();
        int preSum = 0, postSum = 0, preIdx = 0, postIdx = ALen - 1;
        for (; preIdx < ALen; preIdx++) {
            preSum += A[preIdx];
            if (preSum == target) break;
        }
        for (; postIdx >= 0; postIdx--) {
            postSum += A[postIdx];
            if (postSum == target) break;
        }
        return preIdx + 1 < postIdx;
    }
};