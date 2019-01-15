/*
 * POJ 1328 - Radar Installation
 *
 * For each island, calculate the interval in which a radar can cover it.
 * Then greedily cover these intervals.
 */

#include <cmath>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <iostream>
#include <algorithm>
#include <vector>

using namespace std;

double getAbs(double x) {
    return x < 0 ? -x : x;
}

int main() {
    int n, caseNum = 0;
    double d;
    while (true) {
        bool validCase = true;
        caseNum++;
        scanf("%d%lf", &n, &d);
        if (n == 0 && d == 0) break;

        vector<pair<double, double> > intervals;
        double x, y;
        for (int i = 0; i < n; i++) {
            scanf("%lf%lf", &x, &y);
            if (getAbs(y) > d) {
                validCase = false;
            }
            double left = x - sqrt(pow(d, 2) - pow(y, 2));
            double right = x + sqrt(pow(d, 2) - pow(y, 2));
            intervals.push_back(make_pair(right, left));
        }
        if (!validCase) {
            printf("Case %d: -1\n", caseNum);
            continue;
        }

        sort(intervals.begin(), intervals.end());

        int radarNum = 1, intervalNum = intervals.size();
        double lastRadarPos = intervals[0].first;
        for (int i = 1; i < intervalNum; i++) {
            // intervals[i].first must >= lastRadarPos
            if (lastRadarPos < intervals[i].second) {
                lastRadarPos = intervals[i].first;
                radarNum++;
            }
        }

        printf("Case %d: %d\n", caseNum, radarNum);
    }
    return 0;
}
