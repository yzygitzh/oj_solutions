class Solution {
public:
    vector<vector<int>> insert(vector<vector<int>>& intervals, vector<int>& newInterval) {
        vector<vector<int>> result;
        // invariant: result is valid
        bool newInserted = false;
        for (int i = 0; i < intervals.size(); i++) {
            if (!newInserted && newInterval[0] < intervals[i][0]) {
                appendInterval(result, newInterval);
                i--;
                newInserted = true;
            } else {
                appendInterval(result, intervals[i]);
            }
        }
        if (!newInserted) {
            appendInterval(result, newInterval);
        }
        return result;
    }
    
    void appendInterval(vector<vector<int>>& intervals, vector<int> &newInterval) {
        if (intervals.size() == 0 || intervals.back()[1] < newInterval[0]) {
            intervals.push_back(newInterval);
        } else {
            intervals.back()[1] = max(intervals.back()[1], newInterval[1]);
        }
    }
};