class Solution {
public:
    int getAbs(int x, int y){
        return x < y ? y - x : x - y;
    }
    
    int threeSumClosest(vector<int>& nums, int target) {
        // nums's length must >= 3
        int numsLen = nums.size();
        sort(nums.begin(), nums.end());
        
        int closest = nums[0] + nums[1] + nums[2];
        for (int i = 1; i + 1 < numsLen; i++) {
            int left = i - 1;
            int right = i + 1;
            while (true) {
                int sum = nums[left] + nums[i] + nums[right];
                if (sum > target) {
                    if (getAbs(sum, target) < getAbs(closest, target)) {
                        closest = sum;
                    }
                    left--;
                } else if (sum < target) {
                    if (getAbs(sum, target) < getAbs(closest, target)) {
                        closest = sum;
                    }
                    right++;
                } else {
                    return target;
                }
                if (left == -1 || right == numsLen) break;
            }
        }
        return closest;
    }
};