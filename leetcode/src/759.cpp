/*
// Definition for an Interval.
class Interval {
public:
    int start;
    int end;

    Interval() {}

    Interval(int _start, int _end) {
        start = _start;
        end = _end;
    }
};
*/
class Solution {
public:
    class IntervalCmp {
    public:
        bool operator() (const Interval* a, const Interval* b) {
            if (a->start != b->start) {
                return a->start < b->start;
            }
            return a->end < b->end;
        }
    };
    
    vector<Interval*> employeeFreeTime(vector<vector<Interval*>> schedule) {
        vector<Interval*> sortedIntervals;
        for (auto& personSched : schedule) {
            for (auto p : personSched) {
                sortedIntervals.push_back(p);
            }
        }
        sort(sortedIntervals.begin(), sortedIntervals.end(), IntervalCmp());
        int lastEnd = sortedIntervals[0]->start;
        vector<Interval*> result;
        for (auto p : sortedIntervals) {
            if (p->start > lastEnd) {
                result.push_back(new Interval(lastEnd, p->start));
            }
            lastEnd = max(lastEnd, p->end);
        }
        return result;
    }
};