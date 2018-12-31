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
    bool hasIntersect(Interval &a, Interval &b) {
        return !(a.start > b.end || a.end < b.start);
    }
    
    Interval mergeInt(Interval &a, Interval &b) {
        return Interval(a.start < b.start ? a.start : b.start,
                        a.end > b.end ? a.end : b.end);
    }
    
    vector<Interval> insert(vector<Interval>& intervals,
                            Interval newInterval) {
        int intLen = intervals.size();
        // worst O(n) time for intervals moving
        vector<Interval> result;
        
        if (intervals.size() == 0 ||
            intervals[0].start > newInterval.end) {
            result.push_back(newInterval);
            for (int i = 0; i < intLen; i++) {
                result.push_back(intervals[i]);
            }
            return result;
        }
        
        if (intervals[intLen - 1].end < newInterval.start) {
            for (int i = 0; i < intLen; i++) {
                result.push_back(intervals[i]);
            }
            result.push_back(newInterval);
            return result;
        }
        
        int intIdx = 0;
        while (intIdx < intLen) {
            // add all intervals before intersector
            if (intervals[intIdx].end < newInterval.start) {
                result.push_back(intervals[intIdx]);
                intIdx++;
            } else {
                break;
            }
        }
        
        if (hasIntersect(intervals[intIdx], newInterval)) {
            result.push_back(mergeInt(intervals[intIdx], newInterval));
            while (true) {
                int resultLen = result.size();
                if (resultLen == 1) break;
                Interval lastInt = result[resultLen - 1];
                Interval nextLastInt = result[resultLen - 2];
                if (hasIntersect(lastInt, nextLastInt)) {
                    result.pop_back();
                    result.pop_back();
                    result.push_back(mergeInt(lastInt, nextLastInt));
                } else {
                    break;
                }
            }
            intIdx++;
            while (intIdx < intLen) {
                if (hasIntersect(intervals[intIdx], *result.rbegin())) {
                    *result.rbegin() = mergeInt(intervals[intIdx], 
                                                *result.rbegin());
                } else {
                    result.push_back(intervals[intIdx]);
                }
                intIdx++;
            }
        } else {
            result.push_back(newInterval);
            while (intIdx < intLen) {
                result.push_back(intervals[intIdx]);
                intIdx++;
            }
        }
        return result;
    }
};