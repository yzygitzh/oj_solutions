/*
 * POJ 1942 - Paths on a Grid
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
    while (true) {
        unsigned m, n;
        cin >> m >> n;
        if (m == 0 && n == 0) {
            break;
        }
        if (m < n) swap(m, n);
        // n is the smaller one. be careful with small n
        if (n <= 2) {
            unsigned long long result = 1;
            for (int i = 0; i < n; i++) {
                result *= m + n - i;
            }
            for (int i = 0; i < n; i++) {
                result /= i + 1;
            }
            cout << result << endl;
        } else {
            unsigned *paths = new unsigned[n + 1];
            for (int i = 0; i <= n; i++) {
                paths[i] = 1;
            }
            for (int i = 1; i <= m; i++) {
                for (int j = 1; j <= n; j++) {
                    paths[j] += paths[j - 1];
                }
            }
            cout << paths[n] << endl;
        }
    }

    return 0;
}

