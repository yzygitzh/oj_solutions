class Solution {
public:
    int getDis(vector<int>& p1, vector<int>& p2) {
        return abs(p1[0] - p2[0]) + abs(p1[1] - p2[1]);
    }
    
    int result = 0x7FFFFFFF;
    
    int assignBikes(vector<vector<int>>& workers, vector<vector<int>>& bikes) {
        vector<int> bikeVisited(bikes.size(), 0);
        dfs(0, workers, bikes, bikeVisited, 0);
        return result;
    }
    
    void dfs(int idx,
             vector<vector<int>>& workers, vector<vector<int>>& bikes,
             vector<int>& bikeVisited,
             int currResult) {
        if (currResult >= result) {
            return;
        }
        if (idx == workers.size()) {
            result = min(result, currResult);
        } else {
            for (int i = 0; i < bikes.size(); i++) {
                if (!bikeVisited[i]) {
                    bikeVisited[i] = 1;
                    int dis = getDis(workers[idx], bikes[i]);
                    dfs(idx + 1, workers, bikes, bikeVisited, currResult + dis);
                    bikeVisited[i] = 0;
                }
            }
        }
    }
};