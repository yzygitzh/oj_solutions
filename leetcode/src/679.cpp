class Solution {
public:
    // key is sorted
    map<vector<int>, unordered_set<double>> memo;
    
    bool judgePoint24(vector<int>& nums) {
        sort(nums.begin(), nums.end());
        getResults(nums);
        auto results = memo[nums];
        for (auto num : results) {
            if (num > 24.0 - 1e-6 && num < 24.0 + 1e-6) {
                return true;
            }
        }
        return false;
    }
    
    unordered_set<double> getResults(vector<int> numbers) {
        if (!memo.count(numbers)) {
            int numCnt = numbers.size();
            unordered_set<double> results;
            if (numCnt == 1) {
                results.insert(numbers[0]);
            } else {
                for (int i = 1; i < (1 << numCnt) - 1; i++) {
                    vector<int> leftNumbers, rightNumbers;
                    for (int j = 0; j < numCnt; j++) {
                        if (i & (1 << j)) leftNumbers.push_back(numbers[j]);
                        else rightNumbers.push_back(numbers[j]);
                    }
                    auto leftResults = getResults(leftNumbers);
                    auto rightResults = getResults(rightNumbers);
                    for (auto num1 : leftResults) {
                        for (auto num2 : rightResults) {
                            results.insert(num1 + num2);
                            results.insert(num1 - num2);
                            results.insert(num1 * num2);
                            if (num2 > 1e-6 || num2 < -1e-6) results.insert(num1 / num2);
                        }
                    }
                }
            }
            memo[numbers] = results;
        }
        return memo[numbers];
    }
};