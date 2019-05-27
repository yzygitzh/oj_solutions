/*
 * POJ 3252 - Round Numbers
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

// F[m][n]: number of ways to pick at least n from m
unsigned long long F[40][40] = {0};

// get round number <= n
unsigned long long roundN(unsigned long long n) {
    if (n == 0) return 0;
    unsigned long long tmp = n;
    int restLen = 0;
    while (tmp) {
        restLen++;
        tmp >>= 1;
    }
    int zeroCnt = 0, nLen = restLen;
    unsigned long long result = 0;

    // for round numbers with length < nLen, except 0
    if (restLen) {
        for (int len = 1; len < restLen; len++) {
            // the highest bit is 1
            result += F[len - 1][(len + 1) / 2];
        }
    }

    // for round numbers with length == nLen
    // skip highest bit
    restLen--;
    while (restLen) {
        if (n & (1 << (restLen - 1))) {
            // turning 1 << (restLen - 1) to 0. eg. 1(1)00 -> 10xx.
            int zeroNeeded = max(0, (nLen + 1) / 2 - (zeroCnt + 1));
            result += F[restLen - 1][zeroNeeded];
        } else {
            zeroCnt++;
        }
        restLen--;
    }

    // add self if possible
    if (zeroCnt * 2 >= nLen) {
        result++;
    }

    return result;
}

int main() {
    // calc F
    for (int i = 0; i <= 32; i++) {
        F[i][0] = F[i][i] = 1;
    }
    for (int i = 1; i <= 32; i++) {
        for (int j = 1; j < i; j++) {
            F[i][j] = F[i - 1][j] + F[i - 1][j - 1];
        }
    }
    for (int i = 1; i <= 32; i++) {
        for (int j = i - 1; j >= 0; j--) {
            F[i][j] += F[i][j + 1];
        }
    }
    unsigned long long start, finish;
    cin >> start >> finish;
    cout << roundN(finish) - roundN(start - 1) << endl;

    return 0;
}

