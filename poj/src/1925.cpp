/*
 * POJ 1925 - Spiderman
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

int minStep[1000010];
int towers[5010][2];
int towerNum;

int main() {
    int caseNum;
    scanf("%d", &caseNum);
    while (caseNum--) {
        scanf("%d", &towerNum);
        for (int i = 0; i < towerNum; i++) {
            scanf("%d%d", &towers[i][0], &towers[i][1]);
        }
        for (int i = towers[0][0]; i <= towers[towerNum - 1][0]; i++) {
            minStep[i] = 0x7FFFFFFF;
        }
        minStep[towers[0][0]] = 0;
        int startX = towers[0][0];
        int finalX = towers[towerNum - 1][0];
        for (int i = 1; i < towerNum; i++) {
            int dis = (int)sqrt(pow(towers[i][1], 2) - pow(towers[i][1] - towers[0][1], 2));
            for (int j = 1; j <= dis; j++) {
                int leftX = towers[i][0] - j;
                if (leftX < startX) {
                    break;
                }
                int rightX = towers[i][0] + j;
                if (finalX < rightX) {
                    rightX = finalX;
                }
                if (minStep[leftX] < 0x7FFFFFFF &&
                    minStep[rightX] > minStep[leftX] + 1) {
                    minStep[rightX] = minStep[leftX] + 1;
                }
            }
        }
        if (minStep[finalX] == 0x7FFFFFFF) {
            printf("-1\n");
        } else {
            printf("%d\n", minStep[finalX]);
        }
    }
    return 0;
}

