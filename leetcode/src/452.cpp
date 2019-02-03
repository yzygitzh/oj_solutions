class Solution {
public:
    int findMinArrowShots(vector<pair<int, int>>& points) {
        // greedy shoot ballon groups
        int pointsLen = points.size();
        if (pointsLen == 0) return 0;
        sort(points.begin(), points.end());
        int shots = 0;
        pair<int, int> currInterval = points[0];
        for (int i = 1; i < pointsLen; i++) {
            if (points[i].first > currInterval.second) {
                shots++;
                currInterval = points[i];
            } else {
                currInterval = make_pair(points[i].first,
                                         min(points[i].second,
                                             currInterval.second));
            }
        }
        shots++;
        return shots;
    }
};