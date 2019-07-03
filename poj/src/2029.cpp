/*
 * POJ 2029 - Get Many Persimmon Trees
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

int N, W, H, S, T;
int field[110][110];

int main() {
    while (true) {
        scanf("%d", &N);
        if (N == 0) break;
        scanf("%d%d", &W, &H);
        memset(field, 0, sizeof(field));
        for (int i = 0; i < N; i++) {
            int x, y;
            scanf("%d%d", &x, &y);
            field[y][x] = 1;
        }
        scanf("%d%d", &S, &T);
        for (int i = 1; i <= H; i++) {
            for (int j = 1; j <= W; j++) {
                field[i][j] += field[i - 1][j] + field[i][j - 1] -
                               field[i - 1][j - 1];
            }
        }
        int maxTrees = 0;
        for (int i = 1; i <= H; i++) {
            for (int j = 1; j <= W; j++) {
                if (T <= i && S <= j) {
                    maxTrees = max(maxTrees,
                                   field[i][j] -
                                   field[i - T][j] - field[i][j - S] +
                                   field[i - T][j - S]);
                }
            }
        }
        printf("%d\n", maxTrees);
    }
    return 0;
}

