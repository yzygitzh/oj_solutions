class Solution {
public:
    int findOffset(string& timePoint) {
        int hours = 10 * (timePoint[0] - '0') + (timePoint[1] - '0');
        int minutes = 10 * (timePoint[3] - '0') + (timePoint[4] - '0');
        return hours * 60 + minutes;
    }
    
    int findMinDifference(vector<string>& timePoints) {
        sort(timePoints.begin(), timePoints.end(), [=] (string& a, string& b) {
            return findOffset(a) < findOffset(b);
        });
        int result = 0x7FFFFFFF;
        for (int i = 0; i < timePoints.size() - 1; i++) {
            result = min(result, findOffset(timePoints[i + 1]) - findOffset(timePoints[i]));
        }
        result = min(result, 24 * 60 - findOffset(timePoints.back()) + findOffset(timePoints.front()));
        return result;
    }
};