class Solution {
public:
    vector<int> grayCode(int n) {
        // F(n) = 0(F(n-1)), 1(reverse(F(n-1)))
        if (n == 0) return vector<int>{0};
        if (n == 1) return vector<int>{0, 1};
        vector<int> result = vector<int>{0, 1};
        for (int i = 2; i <= n; i++) {
            vector<int> newResult;
            int resultLen = result.size();
            // 0(F(n-1))
            for (int j = 0; j < resultLen; j++) {
                newResult.push_back(result[j]);
            }
            // 1(reverse(F(n-1)))
            for (int j = resultLen - 1; j >= 0; j--) {
                newResult.push_back((1 << (i - 1)) | result[j]);
            }
            result = newResult;
        }
        return result;
    }
};