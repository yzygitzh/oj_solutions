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
    int getAbs(int x) {
        return x < 0 ? -x : x;
    }
    
    int gcd(int a, int b) {
        if (a == 0) return max(1, b);
        if (b == 0) return max(1, a);
        return gcd(b, a % b);
    }
    
    pair<int, int> normalizedVec(Point a, Point b) {
        int deltaX = a.x - b.x;
        int deltaY = a.y - b.y;
        if (deltaX < 0 || deltaX == 0 && deltaY < 0) {
            deltaX = -deltaX;
            deltaY = -deltaY;
        }
        int divider = gcd(getAbs(deltaX), getAbs(deltaY));
        deltaX /= divider;
        deltaY /= divider;
        return make_pair(deltaX, deltaY);
    }
    
    int maxPoints(vector<Point>& points) {
        int maxCnt = 0;
        for (auto itr1 = points.begin(); itr1 != points.end(); ++itr1) {
            map<pair<int, int>, int> pointCnt;
            int selfPnts = 0;
            for (auto itr2 = points.begin(); itr2 != points.end(); ++itr2) {
                if (itr1->x == itr2->x && itr1->y == itr2->y) {
                    selfPnts++;
                    continue;
                }
                pair<int, int> vec = normalizedVec(*itr1, *itr2);
                pointCnt[vec]++;
            }
            maxCnt = max(maxCnt, selfPnts);
            for (auto itr2 = pointCnt.begin();
                 itr2 != pointCnt.end(); ++itr2) {
                maxCnt = max(maxCnt, selfPnts + itr2->second);
            }
        }
        return maxCnt;
    }
};