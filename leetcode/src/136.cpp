class Solution {
public:
    int singleNumber(vector<int>& nums) {
        int xorResult = 0;
        for (vector<int>::iterator itr = nums.begin();
             itr != nums.end(); ++itr) {
            xorResult ^= *itr;
        }
        return xorResult;
    }
};