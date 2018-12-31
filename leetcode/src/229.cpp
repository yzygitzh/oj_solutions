class Solution {
public:
    vector<int> majorityElement(vector<int>& nums) {
        int numsLen = nums.size();
        map<int, int> result;
        for (int i = 0; i < numsLen; i++) {
            // invariant: result never have >= 3 different keys
            result[nums[i]]++;
            
            if (result.size() == 3) {
                vector<int> toDel;
                for (map<int, int>::iterator itr = result.begin();
                     itr != result.end(); ++itr) {
                    toDel.push_back(itr->first);
                }
                for (vector<int>::iterator itr = toDel.begin();
                     itr != toDel.end(); ++itr) {
                    result[*itr]--;
                    if (result[*itr] == 0) result.erase(*itr);
                }
            }
        }
        vector<int> resultVec;
        for (map<int, int>::iterator itr = result.begin();
             itr != result.end(); ++itr) {
            // count them
            int count = 0;
            for (int i = 0; i < numsLen; i++) {
                if (nums[i] == itr->first) count++;
            }
            if (count > numsLen / 3) resultVec.push_back(itr->first);
        }
        return resultVec;
    }
};