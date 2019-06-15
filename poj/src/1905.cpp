/*
 * POJ 1905 - Expanding Rods
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

int main() {
    double L, n, C;
    while (true) {
        scanf("%lf%lf%lf", &L, &n, &C);
        if (L < 0) break;
        double newL = (1. + n * C) * L;
        // binary search radius
        double left = L / 2., right = 1e100;
        while ((right - left) / min(left, right) > 1e-12) {
            double mid = left + (right - left) / 2.;
            if (sin(newL / mid / 2.) > L / mid / 2.) {
                right = mid;
            } else {
                left = mid;
            }
        }
        printf("%.3f\n", left - sqrt(left * left - L * L / 4.));
    }
    return 0;
}

