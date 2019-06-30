/*
 * POJ 1191 - 棋盘分割
 *
 */

#include <cstdio>
#include <cstdlib>
#include <iostream>
#include <iomanip>
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

int N;
long double prefixSum[9][9];
// F[a][b][c][d][e]: cut [a,b][c,d] board into e pieces, with minimum variance
long double minVar[9][9][9][9][20];
long double mean;

long double getSum(int a, int b, int c, int d) {
    return prefixSum[c][d] -
           prefixSum[a - 1][d] - prefixSum[c][b - 1] +
           prefixSum[a - 1][b - 1];
}

long double dfs(int a, int b, int c, int d, int e) {
    if (minVar[a][b][c][d][e] < -1e-6) {
        minVar[a][b][c][d][e] = 1e40;
        if (e == 1) {
            minVar[a][b][c][d][e] = pow(getSum(a, b, c, d) - mean, 2);
        } else if (c + d - a - b >= e - 1) {
            long double r;
            for (int i = 1; i <= c - a; i++) {
                r = dfs(a, b, a + i - 1, d, e - 1) + pow(getSum(a + i, b, c, d) - mean, 2);
                minVar[a][b][c][d][e] = min(minVar[a][b][c][d][e], r);
                r = dfs(a + i, b, c, d, e - 1) + pow(getSum(a, b, a + i - 1, d) - mean, 2);
                minVar[a][b][c][d][e] = min(minVar[a][b][c][d][e], r);
            }
            for (int i = 1; i <= d - b; i++) {
                r = dfs(a, b, c, b + i - 1, e - 1) + pow(getSum(a, b + i, c, d) - mean, 2);
                minVar[a][b][c][d][e] = min(minVar[a][b][c][d][e], r);
                r = dfs(a, b + i, c, d, e - 1) + pow(getSum(a, b, c, b + i - 1) - mean, 2);
                minVar[a][b][c][d][e] = min(minVar[a][b][c][d][e], r);
            }
        }
    }
    return minVar[a][b][c][d][e];
}

int main() {
    cin >> N;
    for (int i = 0; i <= 8; i++) {
        prefixSum[0][i] = prefixSum[i][0] = 0.;
    }
    for (int i1 = 1; i1 <= 8; i1++) {
        for (int i2 = 1; i2 <= 8; i2++) {
            cin >> prefixSum[i1][i2];
            prefixSum[i1][i2] += prefixSum[i1][i2 - 1] + prefixSum[i1 - 1][i2] -
                                 prefixSum[i1 - 1][i2 - 1];
            for (int i3 = i1; i3 <= 8; i3++) {
                for (int i4 = i2; i4 <= 8; i4++) {
                    for (int k = 1; k <= N; k++) {
                        minVar[i1][i2][i3][i4][k] = -1.;
                    }
                }
            }
        }
    }
    mean = prefixSum[8][8] / N;
    long double answer = sqrt(dfs(1, 1, 8, 8, N) / N);
    cout << setiosflags(ios::fixed) << setprecision(3) << answer << endl;
    return 0;
}

