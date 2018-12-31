/**
 * Definition for a point.
 * struct Point {
 *     int x;
 *     int y;
 *     Point() : x(0), y(0) {}
 *     Point(int a, int b) : x(a), y(b) {}
 * };
 */
class Solution {
public:
    bool isOnTheSameLine(Point &a, Point &b, Point &c) {
        long long x1 = (long long)a.x - (long long)b.x;
        long long y1 = (long long)a.y - (long long)b.y;
        long long x2 = (long long)a.x - (long long)c.x;
        long long y2 = (long long)a.y - (long long)c.y;
        long long crossProd = x1 * y2 - x2 * y1;
        return crossProd == 0;
    }
        
    int maxPoints(vector<Point>& points) {
        int pointsLen = points.size();
        map<pair<int, int>, int> pointCnt;
        vector<Point> uniqPoints;
        for (int i = 0; i < pointsLen; i++) {
            pointCnt[make_pair(points[i].x, points[i].y)]++;
        }
        for (map<pair<int, int>, int>::iterator itr = pointCnt.begin();
             itr != pointCnt.end(); ++itr) {
            uniqPoints.push_back(Point(itr->first.first, itr->first.second));
        }
        int uniqPointsLen = uniqPoints.size();
        if (uniqPointsLen == 1) return pointsLen;

        // for each uniqPoint pair, check other points
        int maxPoints = 0;
        for (int i = 0; i < uniqPointsLen; i++) {
            for (int j = i + 1; j < uniqPointsLen; j++) {
                Point p1 = uniqPoints[i], p2 = uniqPoints[j];
                int currPoints = pointCnt[make_pair(p1.x, p1.y)] +
                                 pointCnt[make_pair(p2.x, p2.y)];
                for (int k = j + 1; k < uniqPointsLen; k++) {
                    Point p3 = uniqPoints[k];
                    if (isOnTheSameLine(p1, p2, p3)) {
                        currPoints += pointCnt[make_pair(p3.x, p3.y)];
                    }
                }
                if (currPoints > maxPoints) maxPoints = currPoints;
            }
        }
        return maxPoints;
    }
};