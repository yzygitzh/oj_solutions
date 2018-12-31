class Solution {
public:
    int longestValidParentheses(string s) {
        // <valid-seq> := (<valid-seq>) | <valid-seq><valid-seq> | eps
        // greedy expand () seeds
        int sLen = s.size();
        if (sLen < 2) return 0;
        set<pair<int, int> > intervals;
        for (int i = 0; i < sLen; i++) {
            if (i + 1 < sLen && s[i] == '(' && s[i + 1] == ')') {
                intervals.insert(make_pair(i, i + 1));
            }
        }
        if (intervals.size() == 0) return 0;
    
        pair<int, int> currInterval = *intervals.begin();
        while (true) {
            // try expand by 1st rule
            if (currInterval.first - 1 >= 0 && currInterval.second + 1 < sLen &&
                s[currInterval.first - 1] == '(' && s[currInterval.second + 1] == ')') {
                intervals.erase(currInterval);
                currInterval.first -= 1;
                currInterval.second += 1;
                intervals.insert(currInterval);
                continue;
            }

            // try expand by 2st rule
            // try left
            if (intervals.lower_bound(currInterval) != intervals.begin()) {
                pair<int, int> leftInterval = *(--intervals.lower_bound(currInterval));
                if (leftInterval.second + 1 == currInterval.first) {
                    intervals.erase(currInterval);
                    intervals.erase(leftInterval);
                    currInterval.first = leftInterval.first;
                    intervals.insert(currInterval);
                    continue;
                }
            }
   
            // try right
            if (intervals.upper_bound(currInterval) != intervals.end()) {
                pair<int, int> rightInterval = *intervals.upper_bound(currInterval);
                if (rightInterval.first == currInterval.second + 1) {
                    intervals.erase(currInterval);
                    intervals.erase(rightInterval);
                    currInterval.second = rightInterval.second;
                    intervals.insert(currInterval);
                    continue;
                }
            }

            // no change, insert origin interval, find upper_bound
            if (intervals.upper_bound(currInterval) == intervals.end()) {
                break;
            } else {
                currInterval = *intervals.upper_bound(currInterval);
            }
        }
        int maxLen = 0;
        for (set<pair<int, int> >::iterator itr = intervals.begin();
             itr != intervals.end(); ++itr) {
            if (itr->second - itr->first + 1 > maxLen) {
                maxLen = itr->second - itr->first + 1;
            }
        }
        return maxLen;
    }
};