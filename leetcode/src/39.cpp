class Solution {
public:    
    int **F;
    vector<vector<int>> combinationSum(vector<int>& candidates, int target) {
        int candiNum = candidates.size();
        
        // F[M][N]: target N can be combined from first M candidates
        // F[M][N] = F[M-1][N] || F[M][N-candidates(M)]
        F = new int*[candiNum + 10];
        for (int i = 0; i < candiNum + 10; i++) {
            F[i] = new int[target + 10];
            memset(F[i], 0, sizeof(int) * (target + 10));
        }
        
        for (int i = 1; i <= candiNum; i++){
            F[i][0] = 1;
        }
        
        for (int i = 1; i <= candiNum; i++) {
            for (int j = 1; j <= target; j++) {
                F[i][j] = F[i - 1][j];
                if (j - candidates[i - 1] >= 0) {
                    F[i][j] |= F[i][j - candidates[i - 1]];
                }
            }
        }
        
        set<vector<int> > resultSet;
        vector<int> tmpResult;
        
        /*
        if (F[2][7]) {
            result.push_back(vector<int>{10});
            return result;
        }
        */
        
        DFS(resultSet, tmpResult, candidates, candiNum, target);
        
        for (int i = 0; i < candiNum + 10; i++) {
            delete F[i];
        }
        delete F;
        
        return vector<vector<int> >(resultSet.begin(), resultSet.end());
    }
    
    void DFS(set<vector<int> > &resultSet, vector<int> &tmpResult,
             vector<int> &candidates, int candiIdx, int target) {
        if (target == 0) {
            vector<int> sortedTmpResult(tmpResult.begin(), tmpResult.end());
            sort(sortedTmpResult.begin(), sortedTmpResult.end());
            resultSet.insert(sortedTmpResult);
        } else if (F[candiIdx][target]) {            
            if (candiIdx > 1 && F[candiIdx - 1][target]) {
                // first try no candiIdx candidate
                DFS(resultSet, tmpResult, candidates, candiIdx - 1, target);
            }
            // then try non-zero candiIdx candidates
            for (int i = 1; i * candidates[candiIdx - 1] <= target; i++) {
                int rest = target - i * candidates[candiIdx - 1];
                tmpResult.push_back(candidates[candiIdx - 1]);
                if (F[candiIdx][rest]) {
                    DFS(resultSet, tmpResult, candidates, candiIdx, rest);
                }
            }
            for (int i = 1; i * candidates[candiIdx - 1] <= target; i++) {
                tmpResult.pop_back();
            }
        }
    }
};