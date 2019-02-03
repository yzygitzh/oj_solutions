class Solution {
public:
    int findPoisonedDuration(vector<int>& timeSeries, int duration) {
        // greedy expand poison time
        int seriesLen = timeSeries.size();
        int result = 0;
        for (int i = 0; i < seriesLen; i++) {
            if (i + 1 < seriesLen &&
                timeSeries[i] + duration >= timeSeries[i + 1]) {
                result += timeSeries[i + 1] - timeSeries[i];
            } else {
                result += duration;
            }
        }
        return result;
    }
};