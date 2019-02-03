class Solution {
public:
    map<pair<int, int>, int> memo;
    vector<int> prefixSum;
    
    bool PredictTheWinner(vector<int>& nums) {
        int numsLen = nums.size();
        if (numsLen == 0) return false;
        prefixSum.push_back(0);
        for (int i = 0; i < numsLen; i++) {
            prefixSum.push_back(prefixSum[i] + nums[i]);
        }
        int player1Score = maxScore(nums, 0, numsLen - 1);
        return player1Score * 2 >= prefixSum[numsLen];
    }
    
    int maxScore(vector<int>&nums, int left, int right) {
        if (!memo.count(make_pair(left, right))) {
            if (left == right) {
                memo[make_pair(left, right)] = nums[left];
            } else {
                int totalScore = prefixSum[right + 1] - prefixSum[left];
                // minimize opponent's maximum
                int leftOppoMaxScore = maxScore(nums, left + 1, right);
                int rightOppoMaxScore = maxScore(nums, left, right - 1);

                memo[make_pair(left, right)] =
                    max(totalScore - leftOppoMaxScore,
                        totalScore - rightOppoMaxScore);
            }
            
        }
        return memo[make_pair(left, right)];
    }
};