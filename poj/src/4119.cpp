/*
 * OpenJudge 4119 - 复杂的整数划分问题
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

int N, K;

int solve1() {
    // F[m][n]: m into n parts
    // F[m][n] = F[m-1][n-1] + F[m-n][n]
    // contains 1 / doesn't contain 1
    vector<vector<int>> F(N + 1, vector<int>(K + 1, 0));
    F[0][0] = 1;
    for (int i = 1; i <= N; i++) {
        for (int j = 1; j <= K; j++) {
            F[i][j] = F[i - 1][j - 1];
            if (i - j >= 0) F[i][j] += F[i - j][j];
        }
    }
    return F[N][K];
}

int solve2() {
    // F[m][n]: m using first n positive integers
    // F[m][n] = F[m][n-1] + F[m-n][n-1]
    // doesn't use n / uses n
    vector<vector<int>> F(N + 1, vector<int>(N + 1, 0));
    F[0][0] = 1;
    for (int i = 1; i <= N; i++) {
        F[0][i] = 1;
    }
    for (int i = 1; i <= N; i++) {
        for (int j = 1; j <= N; j++) {
            F[i][j] = F[i][j - 1];
            if (i - j >= 0) F[i][j] += F[i - j][j - 1];
        }
    }
    return F[N][N];
}

int solve3() {
    // F[m][n]: m using first n odd numbers
    // F[m][n] = F[m][n-1] + F[m-(2*n-1)][n]
    // doesn't use n-th / uses n-th odd number
    vector<vector<int>> F(N + 1, vector<int>((N + 1) / 2 + 1, 0));
    F[0][0] = 1;
    for (int i = 1; 2 * i - 1 <= N; i++) {
        F[0][i] = 1;
    }
    for (int i = 1; i <= N; i++) {
        for (int j = 1; 2 * j - 1 <= N; j++) {
            F[i][j] = F[i][j - 1];
            if (i - (2 * j - 1) >= 0) F[i][j] += F[i - (2 * j - 1)][j];
        }
    }
    return F[N][(N + 1) / 2];
}

int main() {
    while (cin >> N >> K) {
        cout << solve1() << endl;
        cout << solve2() << endl;
        cout << solve3() << endl;
    }
    return 0;
}

