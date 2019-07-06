/*
 * POJ 1185 - 炮兵阵地
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
int rows[110];
int maxCnt[2][1024][1024];
vector<int> shapes;
vector<int> prevRow1, prevRow2;

int main() {
    scanf("%d%d", &N, &M);
    for (int i = 2; i <= N + 1; i++) {
        char rowStr[20];
        scanf("%s", rowStr);
        for (int j = 0; j < M; j++) {
            rows[i] <<= 1;
            rows[i] += rowStr[j] == 'P' ? 1 : 0;
        }
    }
    // pre calculate possible shapes
    shapes.reserve(1024);
    for (int i = 0; i < (1 << M); i++) {
        if ((i & (i << 1)) == 0 && (i & (i << 2)) == 0) {
            shapes.push_back(i);
        }
    }
    for (int i = 0; i < shapes.size(); i++) {
        for (int j = 0; j < shapes.size(); j++) {
            maxCnt[0][shapes[i]][shapes[j]] = 
            maxCnt[1][shapes[i]][shapes[j]] = 0;
        }
    }
    prevRow1.reserve(1024);
    prevRow2.reserve(1024);
    for (int i = 2; i <= N + 1; i++) {
        for (int i1 = 0; i1 < shapes.size(); i1++) {
            for (int i2 = 0; i2 < shapes.size(); i2++) {
                maxCnt[i % 2][shapes[i1]][shapes[i2]] = 0;
            }
        }
        for (int j = 0; j < shapes.size(); j++) {
            if ((shapes[j] | rows[i]) != rows[i]) {
                continue;
            }
            int bitCnt = 0, tmpShape = shapes[j];
            while (tmpShape) {
                bitCnt += (tmpShape & 1);
                tmpShape >>= 1;
            }
            prevRow1.clear();
            prevRow2.clear();
            for (int k = 0; k < shapes.size(); k++) {
                if ((shapes[j] & shapes[k]) == 0 &&
                    (shapes[k] | rows[i - 1]) == rows[i - 1]) {
                    prevRow1.push_back(shapes[k]);
                }
                if ((shapes[j] & shapes[k]) == 0 &&
                    (shapes[k] | rows[i - 2]) == rows[i - 2]) {
                    prevRow2.push_back(shapes[k]);
                }
            }
            for (int prev1 = 0; prev1 < prevRow1.size(); prev1++) {
                for (int prev2 = 0; prev2 < prevRow2.size(); prev2++) {
                    int shape1 = prevRow1[prev1];
                    int shape2 = prevRow2[prev2];
                    maxCnt[i % 2][shapes[j]][shape1] = max(
                        maxCnt[i % 2][shapes[j]][shape1],
                        maxCnt[(i - 1) % 2][shape1][shape2] + bitCnt);
                }
            }
        }
    }
    int answer = 0;
    for (int i = 0; i < shapes.size(); i++) {
        for (int j = 0; j < shapes.size(); j++) {
            answer = max(answer, maxCnt[(N + 1) % 2][shapes[i]][shapes[j]]);
        }
    }
    printf("%d\n", answer);
    return 0;
}

