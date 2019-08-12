/*
 * POJ 1054 - The Troublesome Frog
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

int R, C, N;
struct Point {
public:
    int r, c;
    Point() {}
    bool operator<(const Point& p) const {
        return r < p.r || r == p.r && c < p.c;
    }
};
Point points[5010];
unsigned char isPoint[5010][5010];

int main() {
    memset(isPoint, 0, sizeof(isPoint));
    scanf("%d%d%d", &R, &C, &N);
    for (int i = 0; i < N; i++) {
        scanf("%d%d", &points[i].r, &points[i].c);
        isPoint[points[i].r][points[i].c] = 1;
    }
    sort(points, points + N);
    int maxPath = 0;
    for (int i = 0; i < N; i++) {
        Point p = points[i];
        for (int j = i - 1; j >= 0; j--) {
            Point q = points[j];
            int dr = q.r - p.r, dc = q.c - p.c;
            int leastR = p.r + dr * maxPath, leastC = p.c + dc * maxPath;
            if (1 <= leastR && leastR <= R && 1 <= leastC && leastC <= C) {
                int currPath = -1;
                // p to q
                while (1 <= q.r && q.r <= R && 1 <= q.c && q.c <= C &&
                       isPoint[q.r][q.c]) {
                    currPath++;
                    q.r += dr;
                    q.c += dc;
                }
                if (1 <= q.r && q.r <= R && 1 <= q.c && q.c <= C) {
                    continue;
                }
                // q to p
                Point p2 = p;
                while (1 <= p2.r && p2.r <= R && 1 <= p2.c && p2.c <= C &&
                       isPoint[p2.r][p2.c]) {
                    currPath++;
                    p2.r -= dr;
                    p2.c -= dc;
                }
                if (1 <= p2.r && p2.r <= R && 1 <= p2.c && p2.c <= C) {
                    continue;
                }
                maxPath = max(maxPath, currPath);
            }
        }
    }
    if (maxPath >= 2) {
        printf("%d\n", maxPath + 1);
    } else {
        printf("0\n");
    }

    return 0;
}

