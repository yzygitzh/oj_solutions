class Solution {
public:
    bool found = false;
    int numsLen;
    vector<int> startIdx = vector<int>(4, 0);
    
    bool makesquare(vector<int>& nums) {
        numsLen = nums.size();
        if (numsLen < 4) return false;
        int numsSum = 0;
        for (int i = 0; i < numsLen; i++) {
            numsSum += nums[i];
        }
        if (numsSum % 4 || numsSum == 0) return false;
        int edgeLen = numsSum / 4;
        vector<int> visited(numsLen, 0);
        vector<int> partResult(4, 0);
        dfs(numsLen, 0, edgeLen, partResult, nums, visited);
        return found;
    }
    
    void dfs(int rest, int idx, int edgeLen, vector<int>& partResult,
             vector<int>& nums, vector<int>& visited) {
        if (found) return;
        if (rest == 0) {
            if (partResult[0] == partResult[1] &&
                partResult[1] == partResult[2] &&
                partResult[2] == partResult[3]) {
                found = true;
            }
        } else {
            for (int i = startIdx[idx]; i < numsLen; i++) {
                if (!visited[i]) {
                    visited[i] = 1;
                    partResult[idx] += nums[i];
                    if (partResult[idx] <= edgeLen) {
                        startIdx[idx] = i + 1;
                        dfs(rest - 1, idx, edgeLen, partResult, nums, visited);
                    }
                    if (partResult[idx] == edgeLen) {
                        startIdx[idx + 1] = 0;
                        dfs(rest - 1, idx + 1, edgeLen, partResult, nums, visited);
                    }
                    partResult[idx] -= nums[i];
                    visited[i] = 0;
                }
                if (found) return;
            }
        }
    }
};