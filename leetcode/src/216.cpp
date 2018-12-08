class Solution {
public:
    vector<vector<int>> combinationSum3(int k, int n) {
        vector<vector<int> > result;
        vector<int> partResult;
        genCombination(k, 1, n, partResult, result);
        return result;
    }
    
    void genCombination(int restLen, int startIdx, int n,
                        vector<int> &partResult, vector<vector<int> > &result) {
        if (restLen == 0) {
            int sum = 0;
            for (vector<int>::iterator itr = partResult.begin();
                 itr != partResult.end(); ++itr) {
                sum += *itr;
            }
            if (sum == n) result.push_back(partResult);
        } else {
            for (int i = startIdx; i + restLen - 1 <= 9; i++) {
                partResult.push_back(i);
                genCombination(restLen - 1, i + 1, n, partResult, result);
                partResult.pop_back();
            }
        }
    }
};