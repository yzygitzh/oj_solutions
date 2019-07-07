/*
 * POJ 2411 - Mondriaan's Dream
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

int H, W;
long long planNum[2][2048];
int validFirstRowCache[2048];
int validRowPairCache[2048][2048];

bool isValidFirstRow(int row) {
    if (validFirstRowCache[row]) {
        return validFirstRowCache[row] == 1;
    }
    // 1-bits come in pairs
    for (int i = 0; i < W; i++) {
        if (row & (1 << i)) {
            if (row & (1 << (i + 1))) {
                i++;
            } else {
                validFirstRowCache[row] = 2;
                return false;
            }
        }
    }
    validFirstRowCache[row] = 1;
    return true;
}

bool isValidRowPair(int row1, int row2) {
    if (validRowPairCache[row1][row2]) {
        return validRowPairCache[row1][row2] == 1;
    }
    for (int i = 0; i < W; i++) {
        if (row1 & (1 << i)) {
            if (row2 & (1 << i)) {
                // must be horizon brick, four 1-bits
                if ((row1 & (1 << (i + 1))) &&
                    (row2 & (1 << (i + 1)))) {
                    i++;
                } else {
                    validRowPairCache[row1][row2] = 2;
                    return false;
                }
            }
        } else {
            if (!(row2 & (1 << i))) {
                validRowPairCache[row1][row2] = 2;
                return false;
            }
        }
    }
    validRowPairCache[row1][row2] = 1;
    return true;
}

int main() {
    while (true) {
        scanf("%d%d", &H, &W);
        if (H == 0 && W == 0) {
            break;
        }
        memset(validFirstRowCache, 0, sizeof(validFirstRowCache));
        memset(validRowPairCache, 0, sizeof(validRowPairCache));
        for (int i = 0; i < H; i++) {
            memset(planNum[i % 2], 0, sizeof(planNum[i % 2]));
            for (int j = 0; j < (1 << W); j++) {
                if (i == 0) {
                    if (isValidFirstRow(j)) {
                        planNum[i % 2][j] = 1;
                    }
                } else {
                    for (int k = 0; k < (1 << W); k++) {
                        if (isValidRowPair(j, k)) {
                            planNum[i % 2][k] += planNum[(i - 1) % 2][j];
                        }
                    }
                }
            }
        }
        printf("%lld\n", planNum[(H - 1) % 2][(1 << W) - 1]);
    }
    return 0;
}

