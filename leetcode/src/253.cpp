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
    int minMeetingRooms(vector<Interval>& intervals) {
        // segment cover, line sweep
        // time, start/end
        vector<pair<int, int>> timePoints;
        int intervalsLen = intervals.size();
        for (int i = 0; i < intervalsLen; i++) {
            // make end appear before start
            timePoints.push_back(make_pair(intervals[i].start, 1));
            timePoints.push_back(make_pair(intervals[i].end, -1));
        }
        sort(timePoints.begin(), timePoints.end());
        int maxRoom = 0, currRoom = 0, timePointsLen = timePoints.size();
        for (int i = 0; i < timePointsLen; i++) {
            int currPos = i;
            while (i < timePointsLen &&
                   timePoints[currPos].first == timePoints[i].first) {
                currRoom += timePoints[i].second;
                if (currRoom > maxRoom) maxRoom = currRoom;
                i++;
            }
            i--;
        }
        return maxRoom;
    }
};