class Solution {
public:
    int lowbit(int x) {
        return x & (-x);
    }
    
    vector<int> countBits(int num) {
        vector<int> result(num + 1, 0);
        for (int i = 1; i <= num; i++) {
            result[i] = 1 + result[i - lowbit(i)];
        }
        return result;
    }
};