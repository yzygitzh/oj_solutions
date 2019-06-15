/*
 * POJ 3122 - Pie
 *
 */

#include <cstdio>
#include <cstdlib>
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

int N, F;
double radii[10010];
const double mPi = 3.141592653589;

bool validate(double vol) {
    int currPieIdx = 0;
    double currPieRest = mPi * radii[0] * radii[0];
    for (int i = 0; i < F; i++) {
        while (currPieRest < vol) {
            currPieIdx++;
            if (currPieIdx == N) return false;
            currPieRest = mPi * radii[currPieIdx] * radii[currPieIdx];
        }
        currPieRest -= vol;
    }
    return true;
}

int main() {
    int caseNum;
    scanf("%d", &caseNum);
    while (caseNum--) {
        scanf("%d%d", &N, &F);
        F++;
        double maxR = 0;
        for (int i = 0; i < N; i++) {
            scanf("%lf", radii + i);
            maxR = max(maxR, radii[i]);
        }
        double left = 0, right = mPi * maxR * maxR;
        while (left + 1e-5 < right) {
            double mid = left + (right - left) / 2;
            if (validate(mid)) {
                left = mid;
            } else {
                right = mid;
            }
        }
        printf("%.4f\n", left);
    }
    return 0;
}

