class Solution {
public:
    vector<vector<int>> combinationSum2(vector<int>& candidates, int target) {
        set<vector<int> > resultSet;
        vector<int> tmpResult;
        DFS(resultSet, tmpResult, candidates, 0, target);
        return vector<vector<int> >(resultSet.begin(), resultSet.end());
    }
    
    void DFS(set<vector<int> > &resultSet, vector<int> &tmpResult,
             vector<int> &candidates, int candiIdx, int target) {
        if (target == 0) {
            vector<int> sortedTmpResult(tmpResult.begin(), tmpResult.end());
            sort(sortedTmpResult.begin(), sortedTmpResult.end());
            resultSet.insert(sortedTmpResult);
            return;
        }
        if (candiIdx < candidates.size()) {
            // try use
            tmpResult.push_back(candidates[candiIdx]);
            if (target - candidates[candiIdx] >= 0) {
                DFS(resultSet, tmpResult, candidates, candiIdx + 1, target - candidates[candiIdx]);
            }
            tmpResult.pop_back();
            // try don't use
            DFS(resultSet, tmpResult, candidates, candiIdx + 1, target);
        }
        return;
    }
};