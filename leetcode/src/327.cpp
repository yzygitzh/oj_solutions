class Solution {
public:
    vector<int> bitArray;
    
    int lowbit(int x) {
        return x & -x;
    }
    
    int getPrefix(int idx) {
        int result = 0;
        while (idx) {
            result += bitArray[idx];
            idx -= lowbit(idx);
        }
        return result;
    }
    
    void updateBit(int idx, int delta) {
        while (idx < bitArray.size()) {
            bitArray[idx] += delta;
            idx += lowbit(idx);
        }
    }
    
    int countRangeSum(vector<int>& nums, int lower, int upper) {
        vector<long long> prefixSum(nums.size() + 1, 0);
        set<long long> uniqueSums;
        uniqueSums.insert(0);
        for (int i = 0; i < nums.size(); i++) {
            prefixSum[i + 1] = prefixSum[i] + nums[i];
            uniqueSums.insert(prefixSum[i + 1]);
        }
        unordered_map<int, long long> idToSum;
        unordered_map<long long, int> sumToId;
        int sumId = 1;
        for (auto s : uniqueSums) {
            sumToId[s] = sumId;
            idToSum[sumId] = s;
            sumId++;
        }
        
        int result = 0;
        bitArray = vector<int>(sumToId.size() + 1, 0);
        updateBit(sumToId[prefixSum[0]], 1);
        for (int i = 1; i < prefixSum.size(); i++) {
            // lower_bound <= prefix[j] - prefix[i] <= upper_bound
            
            // prefix[j] - lower_bound >= prefix[i]
            int lower_idx = 0;
            {
                int left = 1, right = sumToId.size();
                while (left + 1 < right) {
                    int mid = left + (right - left) / 2;
                    if (prefixSum[i] - lower < idToSum[mid]) {
                        right = mid;
                    } else {
                        left = mid;
                    }
                }
                if (prefixSum[i] - lower >= idToSum[right]) {
                    lower_idx = right;
                } else if (prefixSum[i] - lower >= idToSum[left]) {
                    lower_idx = left;
                }
            }

            // prefix[j] - upper_bound <= prefix[i]
            int upper_idx = 0;
            {
                int left = 1, right = sumToId.size();
                while (left + 1 < right) {
                    int mid = left + (right - left) / 2;
                    if (prefixSum[i] - upper > idToSum[mid]) {
                        left = mid;
                    } else {
                        right = mid;
                    }
                }
                if (prefixSum[i] - upper <= idToSum[left]) {
                    upper_idx = left;
                } else if (prefixSum[i] - upper <= idToSum[right]) {
                    upper_idx = right;
                }
            }
            
            if (lower_idx >= upper_idx && upper_idx > 0) {
                result += getPrefix(lower_idx) - getPrefix(upper_idx - 1);
            }
            
            updateBit(sumToId[prefixSum[i]], 1);
        }
        
        return result;
    }
};