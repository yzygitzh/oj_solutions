class Solution {
public:
    bool increasingTriplet(vector<int>& nums) {
        int numsLen = nums.size();
        if (numsLen < 3) return false;
        int currMin = nums[0];
        
        bool validTwoSeq = false;
        int twoSeqEnd;
        
        for (int i = 1; i < numsLen; i++) {
            // invariant: twoSeq.size() == 2 with minimum end
            
            // first see if there is valid 3-seq
            if (validTwoSeq && twoSeqEnd < nums[i]) return true;
            
            // second try update twoSeq
            if (!validTwoSeq) {
                if (currMin < nums[i]) {
                    validTwoSeq = true;
                    twoSeqEnd = nums[i];
                }
            } else {
                if (currMin < nums[i] && nums[i] < twoSeqEnd) {
                    twoSeqEnd = nums[i];
                }
            }
            
            // third update currMin
            if (nums[i] < currMin) currMin = nums[i];
        }
        
        return false;
    }
};