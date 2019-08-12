/*
 * POJ 3034 - Whac-a-Mole
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

int N, D, M;
struct Mole {
    int x, y, t;
    Mole() {}
    bool operator< (const Mole& m) const {
        return t < m.t;
    }
};
vector<Mole> moles[11];
int moleMap[35][35];
int maxScore[35][35][2];

bool validDis(double x1, double y1, double x2, double y2) {
    return pow(x2 - x1, 2) + pow(y2 - y1, 2) < pow(D, 2) + 1e-6;
}

int gcd(int a, int b) {
    return b == 0 ? max(a, 1) : gcd(b, a % b);
}

int main() {
    for (int i = 0; i <= 10; i++) {
        moles[i].reserve(1010);
    }
    while (true) {
        scanf("%d%d%d", &N, &D, &M);
        if (N == 0 && D == 0 && M == 0) {
            break;
        }
        N += 2 * D;
        for (int i = 0; i <= 10; i++) {
            moles[i].clear();
        }
        for (int i = 0; i < M; i++) {
            Mole mole;
            scanf("%d%d%d", &mole.x, &mole.y, &mole.t);
            mole.x += D;
            mole.y += D;
            moles[mole.t].push_back(mole);
        }
        memset(maxScore, 0, sizeof(maxScore));
        for (int i = 1; i <= 10; i++) {
            memset(moleMap, 0, sizeof(moleMap));
            for (int j = 0; j < moles[i].size(); j++) {
                moleMap[moles[i][j].x][moles[i][j].y] = 1;
            }
            for (int j = 0; j < N; j++) {
                for (int k = 0; k < N; k++) {
                    maxScore[j][k][i % 2] = 0;
                }
            }
            for (int startX = 0; startX < N; startX++) {
                for (int startY = 0; startY < N; startY++) {
                    for (int endX = max(0, startX - D);
                         endX <= min(N - 1, startX + D); endX++) {
                        for (int endY = max(0, startY - D);
                             endY <= min(N - 1, startY + D); endY++) {
                            if (validDis(startX, startY, endX, endY)) {
                                int intPntNum = gcd((int)abs(startX - endX),
                                                    (int)abs(startY - endY));
                                int dX = (endX - startX) / intPntNum;
                                int dY = (endY - startY) / intPntNum;
                                int newMaxScore = 0;
                                for (int currX = startX, currY = startY;
                                     currX != endX || currY != endY;
                                     currX += dX, currY += dY) {
                                    newMaxScore += moleMap[currX][currY];
                                }
                                newMaxScore += moleMap[endX][endY];
                                maxScore[endX][endY][i % 2] = max(
                                    maxScore[endX][endY][i % 2],
                                    maxScore[startX][startY][(i - 1) % 2] + newMaxScore);
                            }
                        }
                    }
                }
            }
        }
        int totalMaxScore = 0;
        for (int i = 0; i < N; i++) {
            for (int j = 0; j < N; j++) {
                totalMaxScore = max(totalMaxScore, maxScore[i][j][10 % 2]);
            }
        }
        printf("%d\n", totalMaxScore);
    }
    return 0;
}

