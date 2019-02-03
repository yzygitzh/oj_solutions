class Solution {
public:
    int minCostII(vector<vector<int>>& costs) {
        int houseNum = costs.size();
        if (houseNum == 0) return 0;
        int colorNum = costs[0].size();
        if (colorNum == 0) return 0;
        
        // there must be only one house
        if (colorNum == 1) return costs[0][0];
        
        // F[M][N]: minimum cost when M-th house is painted with color N
        vector<vector<int>> minCost(2, vector<int>(colorNum));
        for (int i = 0; i < colorNum; i++) {
            minCost[0][i] = costs[0][i];
        }

        // use mono queue
        for (int i = 1; i < houseNum; i++) {
            deque<pair<int, int>> monoQ; // val, index
            // init mono queue
            for (int j = 1; j < colorNum; j++) {
                while (monoQ.size() > 0 &&
                       monoQ.back().first >= minCost[(i - 1) % 2][j]) {
                    monoQ.pop_back();
                }
                monoQ.push_back(make_pair(minCost[(i - 1) % 2][j], j));
            }
            for (int j = 0; j < colorNum; j++) {
                // update next house
                minCost[i % 2][j] = monoQ.front().first + costs[i][j];
                // update mono queue, at most pop one from front
                if (monoQ.size() > 0 && monoQ.front().second == (j + 1) % colorNum) {
                    monoQ.pop_front();
                }
                while (monoQ.size() > 0 && monoQ.back().first >= minCost[(i - 1) % 2][j]) {
                    monoQ.pop_back();
                }
                monoQ.push_back(make_pair(minCost[(i - 1) % 2][j], j));
            }
        }
        
        int result = ~(1 << 31);
        for (int i = 0; i < colorNum; i++) {
            result = min(result, minCost[(houseNum - 1) % 2][i]);
        }
        return result;
    }
};