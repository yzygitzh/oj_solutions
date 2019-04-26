/*
 * POJ 2531 - Network Saboteur
 *
 * Gray code?
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
#include <bitset>

using namespace std;

int N;
int C[21][21];

// 2^19 == 524288
// assume the object represented by the lost most significant bit is in group 0
int grayCode[600000] = {0};

void fillGrayCode(int power) {
    for (int i = 1; i <= power; i++) {
        int fillSegLen = (1 << (i - 1));
        int loopCnt = (1 << (power - i));
        for (int j = 0; j < loopCnt; j += 2) {
            for (int k = fillSegLen; k < fillSegLen * 2; k++) {
                grayCode[j * fillSegLen * 2 + k] |= fillSegLen;
            }
        }
        for (int j = 1; j < loopCnt; j += 2) {
            for (int k = 0; k < fillSegLen; k++) {
                grayCode[j * fillSegLen * 2 + k] |= fillSegLen;
            }
        }
    }
}

int main() {
    cin >> N;
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            cin >> C[i][j];
        }
    }
    fillGrayCode(N - 1);
    int loopCnt = (1 << (N - 1));
    int currCost = 0, maxCost = 0;
    for (int i = 1; i < loopCnt; i++) {
        int diff = grayCode[i] ^ grayCode[i - 1];
        int cid = 0;
        while (diff != 1) {
            diff >>= 1;
            cid++;
        }
        if ((1 << cid) & grayCode[i - 1]) {
            // object moving from group 1 to group 0
            for (int j = 0; j < N; j++) {
                currCost += (grayCode[i - 1] & (1 << j)) ? C[cid][j] : -C[cid][j];
            }
        } else {
            // object moving from group 0 to group 1
            for (int j = 0; j < N; j++) {
                currCost += (grayCode[i - 1] & (1 << j)) ? -C[cid][j] : C[cid][j];
            }
        }
        maxCost = max(maxCost, currCost);
    }
    cout << maxCost << endl;
    return 0;
}

