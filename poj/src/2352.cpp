/*
 * POJ 2352 - Stars
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

int N;
int suffix[15010];

class Point {
public:
    int x, y;
    bool operator<(const Point& p) const {
        return y < p.y || y == p.y && x < p.x;
    }
};
Point points[15010];
int levelCnt[15010];

map<int, int> posToId;
int maxId;

int lowbit(int x) {
    return x & -x;
}

void updateSuffix(int pos, int val) {
    while (pos < 15010) {
        suffix[pos] += val;
        pos += lowbit(pos);
    }
}

int getSuffix(int pos) {
    int result = 0;
    while (pos) {
        result += suffix[pos];
        pos -= lowbit(pos);
    }
    return result;
}

int main() {
    scanf("%d", &N);
    for (int i = 0; i < N; i++) {
        scanf("%d%d", &points[i].x, &points[i].y);
        posToId[points[i].x] = 0;
    }
    sort(points, points + N);
    maxId = 0;
    for (map<int, int>::iterator itr = posToId.begin();
         itr != posToId.end(); ++itr) {
        itr->second = ++maxId;
    }
    memset(suffix, 0, sizeof(suffix));
    memset(levelCnt, 0, sizeof(levelCnt));
    for (int i = 0; i < N; i++) {
        int xId = posToId[points[i].x];
        levelCnt[getSuffix(xId)]++;
        updateSuffix(xId, 1);
    }
    for (int i = 0; i < N; i++) {
        printf("%d\n", levelCnt[i]);
    }
    return 0;
}

