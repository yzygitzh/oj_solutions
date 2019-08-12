/*
 * POJ 3254 - Corn Fields
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

int M, N;
int rows[15];
int totalPlans[2][4096];

int main() {
    memset(rows, 0, sizeof(rows));
    scanf("%d%d", &M, &N);
    for (int i = 1; i <= M; i++) {
        for (int j = 0; j < N; j++) {
            int plant;
            scanf("%d", &plant);
            rows[i] <<= 1;
            rows[i] += plant;
        }
    }
    memset(totalPlans, 0, sizeof(totalPlans));
    totalPlans[0 % 2][0] = 1;
    for (int i = 1; i <= M; i++) {
        for (int j = 0; j < (1 << N); j++) {
            totalPlans[i % 2][j] = 0;
        }
        for (int j = 0; j <= rows[i]; j++) {
            if (!((j & (j << 1)) == 0) || !((j | rows[i]) == rows[i])) {
                continue;
            }
            for (int k = 0; k <= rows[i - 1]; k++) {
                if ((j & k) == 0 &&
                    (k & (k << 1)) == 0 &&
                    (k | rows[i - 1]) == rows[i - 1]) {
                    totalPlans[i % 2][j] += totalPlans[(i - 1) % 2][k];
                    totalPlans[i % 2][j] %= 100000000;
                }
            }
        }
    }
    int answer = 0;
    for (int i = 0; i < (1 << N); i++) {
        answer += totalPlans[M % 2][i];
        answer %= 100000000;
    }
    printf("%d\n", answer);
    return 0;
}

