/*
 * POJ 2948 - Martian Mining
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

int N, M;
int yeyenum[510][510];
int bloggium[510][510];
int result[510][510];

int main() {
    while (true) {
        scanf("%d%d", &N, &M);
        if (N == 0 && M == 0) {
            break;
        }
        memset(yeyenum, 0, sizeof(yeyenum));
        memset(bloggium, 0, sizeof(bloggium));
        for (int i = 1; i <= N; i++) {
            for (int j = 1; j <= M; j++) {
                scanf("%d", &yeyenum[i][j]);
            }
        }
        for (int i = 1; i <= N; i++) {
            for (int j = 1; j <= M; j++) {
                scanf("%d", &bloggium[i][j]);
            }
        }
        // calc prefix
        for (int i = N; i >= 1; i--) {
            for (int j = M; j >= 1; j--) {
                yeyenum[i][j] += yeyenum[i + 1][j] + yeyenum[i][j + 1] -
                                 yeyenum[i + 1][j + 1];
                bloggium[i][j] += bloggium[i + 1][j] + bloggium[i][j + 1] -
                                  bloggium[i + 1][j + 1];
            }
        }
        // calc result
        memset(result, 0, sizeof(result));
        for (int i = N; i >= 1; i--) {
            for (int j = M; j >= 1; j--) {
                // the leftmost column
                // [k, N + 1) x [j + 1, M + 1) stays the same
                // [i, k) x [j, M + 1) goes to bloggium
                // [k, N + 1) x [j, j + 1) goes to yeyenum
                for (int k = i; k <= N + 1; k++) {
                    result[i][j] = max(result[i][j],
                                       result[k][j + 1] +
                                       bloggium[i][j] - bloggium[k][j] -
                                       bloggium[i][M + 1] + bloggium[k][M + 1] +
                                       yeyenum[k][j] - yeyenum[N + 1][j] -
                                       yeyenum[k][j + 1] + yeyenum[N + 1][j + 1]);
                }
                // the top row
                // [i + 1, N + 1) x [k, M + 1) stays the same
                // [i, N + 1) x [j, k) goes to yeyenum
                // [i, i + 1) x [k, M + 1) goes to bloggium
                for (int k = j; k <= M + 1; k++) {
                    result[i][j] = max(result[i][j],
                                       result[i + 1][k] +
                                       yeyenum[i][j] - yeyenum[i][k] -
                                       yeyenum[N + 1][j] + yeyenum[N + 1][k] +
                                       bloggium[i][k] - bloggium[i][M + 1] -
                                       bloggium[i + 1][k] + bloggium[i + 1][M + 1]);
                }
            }
        }
        printf("%d\n", result[1][1]);
    }
    return 0;
}

