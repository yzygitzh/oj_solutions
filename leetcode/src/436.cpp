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
    vector<int> findRightInterval(vector<Interval>& intervals) {
        int intervalsNum = intervals.size();
        map<int, int> endToIdx;
        for (int i = 0; i < intervalsNum; i++) {
            endToIdx[intervals[i].start] = i;
        }
        vector<int> result(intervalsNum);
        for (int i = 0; i < intervalsNum; i++) {
            auto itr = endToIdx.lower_bound(intervals[i].end);
            if (itr != endToIdx.end()) {
                result[i] = itr->second;
            } else {
                result[i] = -1;
            }
        }
        return result;
    }
};