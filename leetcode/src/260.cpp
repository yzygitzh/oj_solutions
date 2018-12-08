class Solution {
public:
    vector<int> singleNumber(vector<int>& nums) {
        int xorResult = 0;
        for (vector<int>::iterator itr = nums.begin();
             itr != nums.end(); ++itr) {
            xorResult ^= *itr;
        }
        
        // find first 1-bit
        int mask = 1;
        while (!(mask & xorResult)) mask <<= 1;
        
        int result1 = 0, result2 = 0;
        for (vector<int>::iterator itr = nums.begin();
             itr != nums.end(); ++itr) {
            if (mask & (*itr)) result1 ^= *itr;
            else result2 ^= *itr;
        }
        
        return vector<int>{result1, result2};
    }
};