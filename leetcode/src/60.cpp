class Solution {
public:
    vector<int> bitArray;
    
    int lowbit(int x) {
        return x & -x;
    }
    
    int bitGetPrefix(int idx) {
        int result = 0;
        while (idx > 0) {
            result += bitArray[idx];
            idx -= lowbit(idx);
        }
        return result;
    }
    
    void bitDelta(int idx, int delta) {
        while (idx < bitArray.size()) {
            bitArray[idx] += delta;
            idx += lowbit(idx);
        }
    }
    
    int findNth(int idx) {
        int left = 1, right = bitArray.size() - 1;
        while (left + 1 < right) {
            int mid = left + (right - left) / 2;
            if (bitGetPrefix(mid) < idx) {
                left = mid;
            } else {
                right = mid;
            }
        }
        if (idx == bitGetPrefix(left)) {
            return left;
        } else {
            return right;
        }
    }
    
    string getPermutation(int n, int k) {
        string result;
        bitArray.resize(n + 1, 0);
        for (int i = 1; i <= n; i++) {
            bitDelta(i, 1);
        }
        vector<int> factor(n + 1, 1);
        for (int i = 2; i <= n; i++) {
            factor[i] = factor[i - 1] * i;
        }
        for (int i = 0; i + 1 < n; i++) {
            int restLen = n - i - 1;
            int currOrder = (k + factor[restLen] - 1) / factor[restLen];
            int digit = findNth(currOrder);
            bitDelta(digit, -1);
            result += to_string(digit);
            k -= (currOrder - 1) * factor[restLen];
        }
        for (int i = 1; i <= n; i++) {
            if (bitGetPrefix(i)) {
                result += to_string(i);
                break;
            }
        }
        return result;
    }
};