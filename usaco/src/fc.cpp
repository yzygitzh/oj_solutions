/* Use the slash-star style comments or the system won't see your
   identification information */
/*
ID: yzylive1
TASK: fc
LANG: C++
*/
/* LANG can be C++20 or C++14 for those more recent releases */
#include <iostream>
#include <sstream>
#include <iomanip>
#include <fstream>
#include <vector>
#include <algorithm>
#include <cstring>
#include <queue>
#include <set>
#include <string>
#include <map>
#include <cmath>

using namespace std;

ifstream fin ("fc.in");
ofstream fout ("fc.out");

int N;
class Point {
public:
    double x, y;
    Point(double _x, double _y): x(_x), y(_y) {}
    Point(): x(0), y(0) {}
    bool operator< (const Point& p) const {
        return atan2(y, x) < atan2(p.y, p.x);
    }
};
Point points[10010];
Point center;
int prevPoint[10010];
int nextPoint[10010];

void getCenter() {
    for (int i = 0; i < N; i++) {
        center.x += points[i].x / N;
        center.y += points[i].y / N;
    }
}

double crossProduct(Point a, Point b) {
    return a.x * b.y - a.y * b.x;
}

double getDis(Point a, Point b) {
    return sqrt(pow(a.x - b.x, 2) + pow(a.y - b.y, 2));
}

int findConvexHull() {
    for (int i = 0; i < N; i++) {
        prevPoint[i] = -1;
        nextPoint[i] = -1;
    }
    prevPoint[1] = 0;
    nextPoint[0] = 1;
    for (int i = 2; i < N; i++) {
        int p = i - 1;
        prevPoint[i] = p;
        nextPoint[p] = i;
        while (p > 0 &&
               crossProduct(Point(points[p].x - points[prevPoint[p]].x,
                                  points[p].y - points[prevPoint[p]].y),
                            Point(points[i].x - points[p].x,
                                  points[i].y - points[p].y)) < 0) {
            // delete p
            prevPoint[i] = prevPoint[p];
            nextPoint[prevPoint[p]] = i;
            prevPoint[p] = nextPoint[p] = -1;
            p = prevPoint[i];
        }
    }
    // connect last point
    prevPoint[0] = N-1;
    nextPoint[N-1] = 0;

    int p1 = N-1, p2 = 0;
    int startPoint = p2;
    // check p1 and p2 angle
    while (true) {
        double cp1 = crossProduct(Point(points[p1].x - points[prevPoint[p1]].x,
                                        points[p1].y - points[prevPoint[p1]].y),
                                  Point(points[nextPoint[p1]].x - points[p1].x,
                                        points[nextPoint[p1]].y - points[p1].y));
        double cp2 = crossProduct(Point(points[p2].x - points[prevPoint[p2]].x,
                                        points[p2].y - points[prevPoint[p2]].y),
                                  Point(points[nextPoint[p2]].x - points[p2].x,
                                        points[nextPoint[p2]].y - points[p2].y));
        if (cp1 >= -1e-6 && cp2 >= -1e-6) {
            break;
        }
        if (cp1 < -1e-6) {
            // delete p1, move clockwise
            int prevP1 = prevPoint[p1];
            prevPoint[nextPoint[p1]] = prevPoint[p1];
            nextPoint[prevPoint[p1]] = nextPoint[p1];
            prevPoint[p1] = nextPoint[p1] = -1;
            p1 = prevP1;
            startPoint = p1;
            continue;
        }
        if (cp2 < -1e-6) {
            // delete p2, move counter clockwise
            int nextP2 = nextPoint[p2];
            prevPoint[nextPoint[p2]] = prevPoint[p2];
            nextPoint[prevPoint[p2]] = nextPoint[p2];
            prevPoint[p2] = nextPoint[p2] = -1;
            p2 = nextP2;
            startPoint = p2;
            continue;
        }
    }
    return startPoint;
}

int main() {
    fin >> N;
    for (int i = 0; i < N; i++) {
        fin >> points[i].x >> points[i].y;
    }
    if (N <= 1) {
        fout << setprecision(2) << fixed << 0.0 << endl;
        return 0;
    } else if (N == 2) {
        fout << setprecision(2) << fixed << getDis(points[0], points[1]) * 2 << endl;
        return 0;
    }
    getCenter();
    for (int i = 0; i < N; i++) {
        points[i].x -= center.x;
        points[i].y -= center.y;
    }
    sort(points, points + N);
    double len = 0.0;
    int convexHullStart = findConvexHull();
    int currP = nextPoint[convexHullStart];
    while (currP != convexHullStart) {
        double cp1 = crossProduct(Point(points[currP].x - points[prevPoint[currP]].x,
                                        points[currP].y - points[prevPoint[currP]].y),
                                  Point(points[nextPoint[currP]].x - points[currP].x,
                                        points[nextPoint[currP]].y - points[currP].y));
        // cout << cp1 << endl;
        // cout << points[currP].x + center.x << " " << points[currP].y + center.y << endl;
        len += getDis(points[currP], points[prevPoint[currP]]);
        currP = nextPoint[currP];
    }
    // cout << points[currP].x + center.x << " " << points[currP].y + center.y << endl;
    len += getDis(points[currP], points[prevPoint[currP]]);
    fout << setprecision(2) << fixed << len << endl;
    return 0;
}

