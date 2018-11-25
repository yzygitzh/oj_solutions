/**
 * Definition for an interval.
 * struct Interval {
 *     int start;
 *     int end;
 *     Interval() : start(0), end(0) {}
 *     Interval(int s, int e) : start(s), end(e) {}
 * };
 */
class Solution {
public:
    class IntervalSortFunc {
    public:
        bool operator() (const Interval &a, const Interval &b) const {
            if (a.start != b.start) return a.start < b.start;
            else return a.end < b.end;
        }
    };
    int getMax(int x, int y) {
        return x > y ? x : y;
    }
    vector<Interval> merge(vector<Interval>& intervals) {
        vector<Interval> result;
        int intervalNum = intervals.size();
        if (intervalNum == 0) return result;
        
        sort(intervals.begin(), intervals.end(), IntervalSortFunc());
        
        Interval mergedInterval = intervals[0];
        for (int i = 0; i < intervalNum; i++) {
            if (intervals[i].start <= mergedInterval.end) {
                mergedInterval.end = getMax(mergedInterval.end, intervals[i].end);
            } else {
                result.push_back(mergedInterval);
                mergedInterval = intervals[i];
            }
        }
        result.push_back(mergedInterval);
        return result;
    }
};