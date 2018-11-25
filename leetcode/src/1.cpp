class Solution {
public:
    vector<int> twoSum(vector<int>& nums, int target) {
        unordered_map<int, vector<int> > numMap;
        int idx = 0;
        for (vector<int>::iterator itr = nums.begin();
             itr != nums.end(); ++itr) {
            if (numMap.find(*itr) == numMap.end()) {
                numMap[*itr] = vector<int>();
            }
            numMap[*itr].push_back(idx);
            idx++;
        }
        idx = 0;
        for (vector<int>::iterator itr = nums.begin();
             itr != nums.end(); ++itr) {
            if (numMap.find(target - *itr) != numMap.end()) {
                if (idx != numMap[target - *itr][0]) {
                    return vector<int>{idx, numMap[target - *itr][0]};   
                }
            }
            idx++;
        }
    }
};