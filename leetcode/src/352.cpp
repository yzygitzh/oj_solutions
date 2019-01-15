/**
 * Definition for an interval.
 * struct Interval {
 *     int start;
 *     int end;
 *     Interval() : start(0), end(0) {}
 *     Interval(int s, int e) : start(s), end(e) {}
 * };
 */
class SummaryRanges {
public:
    set<pair<int, int>> intervals;
        
    /** Initialize your data structure here. */
    SummaryRanges() {
        
    }
    
    void addNum(int val) {
        pair<int, int> upInterval, downInterval;
        
        set<pair<int, int>>::iterator upItr = intervals.lower_bound(make_pair(val, val));
        set<pair<int, int>>::iterator downItr = upItr;
        if (downItr != intervals.begin()) {
            --downItr;
        }
        else {
            downItr = intervals.end();
        }

        if (upItr != intervals.end()) upInterval = *upItr;
        if (downItr != intervals.end()) downInterval = *downItr;
        
        // do nothing if already covered
        if (upItr != intervals.end() && upInterval.first <= val ||
            downItr != intervals.end() && downInterval.second >= val) {
            return;
        }
        
        // merge two ends
        if (upItr != intervals.end() && upInterval.first == val + 1 &&
            downItr != intervals.end() && downInterval.second == val - 1) {
            intervals.erase(upInterval);
            intervals.erase(downInterval);
            intervals.insert(make_pair(downInterval.first, upInterval.second));
            return;
        }
        
        // merge only one end
        if (upItr != intervals.end() && upInterval.first == val + 1) {
            intervals.erase(upInterval);
            intervals.insert(make_pair(val, upInterval.second));
            return;
        }
        if (downItr != intervals.end() && downInterval.second == val - 1) {
            intervals.erase(downInterval);
            intervals.insert(make_pair(downInterval.first, val));
            return;
        }
        
        // plain insert
        intervals.insert(make_pair(val, val));
        return;
    }
    
    vector<Interval> getIntervals() {
        vector<Interval> result;
        for (set<pair<int, int>>::iterator itr = intervals.begin();
             itr != intervals.end(); ++itr) {
            result.push_back(Interval(itr->first, itr->second));
        }
        return result;
    }
};

/**
 * Your SummaryRanges object will be instantiated and called as such:
 * SummaryRanges* obj = new SummaryRanges();
 * obj->addNum(val);
 * vector<Interval> param_2 = obj->getIntervals();
 */