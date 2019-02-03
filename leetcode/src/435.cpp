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
    int eraseOverlapIntervals(vector<Interval>& intervals) {
        // greedily remove longer intervals with same end
        // then dp
        int intervalsNum = intervals.size();
        if (intervalsNum <= 1) return 0;
        int preDel = 0;
        map<int, int> endToStart;
        for (auto itr = intervals.begin(); itr != intervals.end(); ++itr) {
            if (endToStart.find(itr->end) == endToStart.end()) {
                endToStart[itr->end] = itr->start;
            } else {
                endToStart[itr->end] = max(endToStart[itr->end],
                                           itr->start);
                preDel++;
            }
        }
        vector<int> ends, starts;
        for (auto itr = endToStart.begin(); itr != endToStart.end(); ++itr) {
            ends.push_back(itr->first);
            starts.push_back(itr->second);
        }
        int endsNum = ends.size();
        vector<int> minDel(endsNum, 0);
        for (int i = 1; i < endsNum; i++) {
            minDel[i] = minDel[i - 1] + 1;
            // bin search in before ends
            int left = 0, right = i - 1;
            while (left + 1 < right) {
                int mid = (left + right) / 2;
                if (ends[mid] < starts[i]) {
                    left = mid;
                } else {
                    right = mid;
                }
            }
            if (ends[right] <= starts[i]) {
                minDel[i] = min(minDel[i], minDel[right] + i - right - 1);
            } else if (ends[left] <= starts[i]) {
                minDel[i] = min(minDel[i], minDel[left] + i - left - 1);
            }
        }
        return minDel[endsNum - 1] + preDel;
    }
};