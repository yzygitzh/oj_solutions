class Solution {
public:
    inline unsigned long long getLampHash(int x, int y) {
        unsigned long long result = 0;
        result = x;
        result <<= 32;
        result += y;
        return result;
    }
    
    vector<int> gridIllumination(int N, vector<vector<int>>& lamps, vector<vector<int>>& queries) {
        // build count for x, y, x+y, x-y
        // enumerate turn off process
        unordered_map<int, int> XLamp, YLamp, XPlusYLamp, XMinusYLamp;
        unordered_set<unsigned long long> lampsOn;
        for (auto& lamp : lamps) {
            XLamp[lamp[0]]++;
            YLamp[lamp[1]]++;
            XPlusYLamp[lamp[0] + lamp[1]]++;
            XMinusYLamp[lamp[0] - lamp[1]]++;
            lampsOn.insert(getLampHash(lamp[0], lamp[1]));
        }
        // enumerate each query
        vector<int> result;
        result.reserve(queries.size());
        for (auto& query : queries) {
            if (XLamp[query[0]] > 0 || YLamp[query[1]] > 0 ||
                XPlusYLamp[query[0] + query[1]] > 0 ||
                XMinusYLamp[query[0] - query[1]] > 0) {
                result.push_back(1);
            } else {
                result.push_back(0);
            }
            // do turn off
            for (int i = -1; i <= 1; i++) {
                for (int j = -1; j <= 1; j++) {
                    if (lampsOn.count(getLampHash(query[0] + i, query[1] + j))) {
                        lampsOn.erase(getLampHash(query[0] + i, query[1] + j));
                        XLamp[query[0] + i]--;
                        YLamp[query[1] + i]--;
                        XPlusYLamp[query[0] + i + query[1] + j]--;
                        XMinusYLamp[query[0] + i - query[1] - j]--;
                    }
                }
            }
        }
        return result;
    }
};