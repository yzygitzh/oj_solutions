class Solution {
public:
    vector<vector<int>> combine(int n, int k) {
        vector<vector<int>> finalResult;
        if (n <= 0 || k <= 0 || k > n) return finalResult;
        vector<int> partResult;
        genCombine(n, k, 1, partResult, finalResult);
        return finalResult;
    }
    
    void genCombine(int n, int k, int firstTry,
                    vector<int> &partResult, vector<vector<int>> &result) {
        if (k == 0) {
            result.push_back(partResult);
        } else {
            for (int i = firstTry; i + k - 1 <= n; i++) {
                partResult.push_back(i);
                genCombine(n, k - 1, i + 1, partResult, result);
                partResult.pop_back();
            }
        }
    }
};