/*
 * POJ 2002 - Squares
 *
 */

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

int main() {
    int pointNum;
    while (true) {
        cin >> pointNum;
        if (pointNum == 0) break;
        set<pair<int, int> > points;
        for (int i = 0; i < pointNum; i++) {
            int x, y;
            cin >> x >> y;
            points.insert(make_pair(x, y));
        }
        set<vector<pair<int, int> > > squares;
        for (auto itr1 = points.begin(); itr1 != points.end(); ++itr1) {
            for (auto itr2 = next(itr1); itr2 != points.end(); ++itr2) {
                pair<int, int> p1 = *itr1, p2 = *itr2, p3, p4;
                // right-side, p1=(-1,0), p2=(0,1), p3=(0,-1), p4=(1,0)
                p3.first = p1.first + (p2.second - p1.second);
                p3.second = p1.second - (p2.first - p1.first);
                p4.first = p3.first + (p2.first - p1.first);
                p4.second = p3.second + (p2.second - p1.second);
                if (points.count(p3) && points.count(p4)) {
                    vector<pair<int, int> > square{p1, p2, p3, p4};
                    sort(square.begin(), square.end());
                    squares.insert(square);
                }
                // left-side, p1=(0,-1), p2=(1,0), p3=(-1,0), p4=(0,1)
                p3.first = p1.first - (p2.second - p1.second);
                p3.second = p1.second + (p2.first - p1.first);
                p4.first = p3.first + (p2.first - p1.first);
                p4.second = p3.second + (p2.second - p1.second);
                if (points.count(p3) && points.count(p4)) {
                    vector<pair<int, int> > square{p1, p2, p3, p4};
                    sort(square.begin(), square.end());
                    squares.insert(square);
                }
            }
        }
        cout << squares.size() << endl;
    }
    return 0;
}

