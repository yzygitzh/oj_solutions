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
    vector<Interval> intervalIntersection(vector<Interval>& A, vector<Interval>& B) {
        int ALen = A.size(), BLen = B.size();
        int AIdx = 0, BIdx = 0;
        vector<Interval> result;
        while (AIdx < ALen && BIdx < BLen) {
            Interval intersect = Interval(max(A[AIdx].start, B[BIdx].start),
                                          min(A[AIdx].end, B[BIdx].end));
            if (intersect.start <= intersect.end) {
                result.push_back(intersect);
            }
            if (A[AIdx].end < B[BIdx].end) {
                // keep B, B may be modified
                B[BIdx].start = max(A[AIdx].end, B[BIdx].start);
                AIdx++;
            } else {
                A[AIdx].start = max(B[BIdx].end, A[AIdx].start);
                BIdx++;
            }
        }
        return result;
    }
};