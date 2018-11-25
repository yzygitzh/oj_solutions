class Solution {
public:
    vector<vector<int>> fourSum(vector<int>& nums, int target) {
        vector<vector<int> > result;
        int numsLen = nums.size();
        if (numsLen <= 3) return result; 
        
        set<vector<int> > resultSet;        
        sort(nums.begin(), nums.end());
        
        // Generate possible two-number sums, O(n^2)
        map<int, vector<vector<int> > > sumToPairs;
        set<int> sumSet;
        for (int i = 0; i < numsLen - 1; i++) {
            for (int j = i + 1; j < numsLen; j++) {
                int sum = nums[i] + nums[j];
                sumSet.insert(sum);
                if (sumToPairs.find(sum) == sumToPairs.end()) {
                    vector<vector<int> > sumVec;
                    sumToPairs[sum] = sumVec;
                }
                vector<int> numPair{i, j};
                sumToPairs[sum].push_back(numPair);
            }
        }
        
        // Do 2-sum on sumSet, O(n^2)
        vector<int> sumVec(sumSet.begin(), sumSet.end());        
        int sumLen = sumVec.size();
        int left = 0, right = sumLen - 1;
        while (left <= right) {
            int leftSum = sumVec[left];
            int rightSum = sumVec[right];
            int fourSum = leftSum + rightSum;
            if (fourSum < target) {
                left++;
            } else if (fourSum > target) {
                right--;
            } else {
                vector<vector<int> > leftPairs = sumToPairs[leftSum];
                vector<vector<int> > rightPairs = sumToPairs[rightSum];
                for (vector<vector<int> >::iterator itr1 = leftPairs.begin();
                     itr1 != leftPairs.end(); ++itr1) {
                    for (vector<vector<int> >::iterator itr2 = rightPairs.begin();
                         itr2 != rightPairs.end(); ++itr2) {
                        if ((*itr1)[0] == (*itr2)[0] ||
                            (*itr1)[0] == (*itr2)[1] ||
                            (*itr1)[1] == (*itr2)[0] ||
                            (*itr1)[1] == (*itr2)[1]) continue;
                        vector<int> answer{nums[(*itr1)[0]], nums[(*itr1)[1]],
                                           nums[(*itr2)[0]], nums[(*itr2)[1]]};
                        sort(answer.begin(), answer.end());
                        resultSet.insert(answer);
                    }
                }
                left++;
                right--;
            }
        }
        
        result = vector<vector<int> >(resultSet.begin(), resultSet.end());
        return result;
    }
};