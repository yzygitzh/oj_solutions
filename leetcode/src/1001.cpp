class Solution {
public:
    vector<int> gridIllumination(int N, vector<vector<int>>& lamps, vector<vector<int>>& queries) {
        // build index for x, y, x+y, x-y
        // enumerate turn off process
        unordered_map<int, set<vector<int>>> XLamp, YLamp, XPlusYLamp, XMinusYLamp;
        for (auto& lamp : lamps) {
            XLamp[lamp[0]].insert(lamp);
            YLamp[lamp[1]].insert(lamp);
            XPlusYLamp[lamp[0] + lamp[1]].insert(lamp);
            XMinusYLamp[lamp[0] - lamp[1]].insert(lamp);
        }
        // enumerate each query
        vector<int> result;
        for (auto& query : queries) {
            if (XLamp[query[0]].size() > 0 ||
                YLamp[query[1]].size() > 0 ||
                XPlusYLamp[query[0] + query[1]].size() > 0 ||
                XMinusYLamp[query[0] - query[1]].size() > 0) {
                result.push_back(1);
            } else {
                result.push_back(0);
            }
            // do turn off
            for (int i = -1; i <= 1; i++) {
                for (int j = -1; j <= 1; j++) {
                    XLamp[query[0] + i].erase(vector<int>{query[0] + i, query[1] + j});
                    YLamp[query[1] + i].erase(vector<int>{query[0] + i, query[1] + j});
                    XPlusYLamp[query[0] + i + query[1] + j].erase(
                        vector<int>{query[0] + i, query[1] + j});
                    XMinusYLamp[query[0] + i - query[1] - j].erase(
                        vector<int>{query[0] + i, query[1] + j});
                }
            }
        }
        return result;
    }
};