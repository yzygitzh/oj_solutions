class Solution {
public:
    bool canPartitionKSubsets(vector<int>& nums, int k) {
        sort(nums.begin(), nums.end(), [] (int a, int b) {return a > b;});
        int numsSum = 0;
        for (auto num : nums) {
            numsSum += num;
        }
        if (numsSum % k) {
            return false;
        }
        vector<int> visited(nums.size(), 0);
        return dfs(nums, visited, 0, numsSum / k, k);
    }
    
    bool dfs(vector<int>& nums, vector<int>& visited, int currSum, int target, int rest) {
        if (rest == 0) {
            return true;
        }
        bool firstTry = true;
        for (int i = 0; i < nums.size(); i++) {
            if (!visited[i]) {
                visited[i] = 1;
                if (currSum + nums[i] < target) {
                    if (dfs(nums, visited, currSum + nums[i], target, rest)) {
                        visited[i] = 0;
                        return true;
                    }
                } else if (currSum + nums[i] == target) {
                    if (dfs(nums, visited, 0, target, rest - 1)) {
                        visited[i] = 0;
                        return true;
                    } else {
                        visited[i] = 0;
                        return false; // in complete case, largest stick fails, can never success again 
                    }
                }
                visited[i] = 0;
                if (firstTry && currSum == 0) {
                    return false;
                }
                firstTry = false;
            }
        }
        return false;
    }
};