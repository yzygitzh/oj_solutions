class Solution {
public:
    vector<vector<int>> threeSum(vector<int>& nums) {
        set<vector<int> > resultSet;
        vector<vector<int> > result;
        int numsLen = nums.size();
        if (numsLen <= 2) return result;

        sort(nums.begin(), nums.end());

        for (int i = 1; i < numsLen - 1; i++) {
            int left = i - 1;
            int right = i + 1;
            while (true) {
                int sum = nums[i] + nums[left] + nums[right];
                if (sum < 0) {
                    while (right <= numsLen - 2 && nums[right] == nums[right + 1]) right++;
                    right++;
                } else if (sum > 0) {
                    while (left >= 1 && nums[left] == nums[left - 1]) left--;
                    left--;                    
                } else {
                    vector<int> answer;
                    answer.push_back(nums[left]);
                    answer.push_back(nums[i]);
                    answer.push_back(nums[right]);
                    resultSet.insert(answer);
                    while (right <= numsLen - 2 && nums[right] == nums[right + 1]) right++;
                    right++;
                    while (left >= 1 && nums[left] == nums[left - 1]) left--;
                    left--;
                }
                if (left == -1 || right == numsLen) break;
            }
        }
        
        for (set<vector<int> >::iterator itr = resultSet.begin();
             itr != resultSet.end(); ++itr) {
            result.push_back(*itr);
        }
        
        return result;
    }
};