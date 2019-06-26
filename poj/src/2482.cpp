/*
 * POJ 2482 - Stars in Your Window
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

struct SegNode {
    int segMax, cachedVal;
};

class Star {
public:
    int x, y, brightness;
    bool operator< (const Star& s) const {
        return x < s.x || x == s.x && y <= s.y;
    }
};

SegNode segNodes[100100];
Star stars[10010];
int N, W, H;

void buildSegTree() {
    memset(segNodes, 0, sizeof(segNodes));
}

void updateSeg(int nodeIdx, int nodeLeft, int nodeRight,
               int left, int right, int val) {
    if (nodeLeft == left && nodeRight == right) {
        segNodes[nodeIdx].segMax += val;
        segNodes[nodeIdx].cachedVal += val;
    } else {
        int mid = nodeLeft + (nodeRight - nodeLeft) / 2;
        if (segNodes[nodeIdx].cachedVal) {
            updateSeg(nodeIdx * 2, nodeLeft, mid, nodeLeft, mid, segNodes[nodeIdx].cachedVal);
            updateSeg(nodeIdx * 2 + 1, mid + 1, nodeRight, mid + 1, nodeRight, segNodes[nodeIdx].cachedVal);
            segNodes[nodeIdx].cachedVal = 0;
        }
        if (left <= mid) {
            updateSeg(nodeIdx * 2, nodeLeft, mid, left, min(mid, right), val);
        }
        if (right >= mid + 1) {
            updateSeg(nodeIdx * 2 + 1, mid + 1, nodeRight, max(mid + 1, left), right, val);
        }
        segNodes[nodeIdx].segMax = max(segNodes[nodeIdx * 2].segMax, segNodes[nodeIdx * 2 + 1].segMax);
    }
}

int main() {
    while (scanf("%d%d%d", &N, &W, &H) > 0) {
        buildSegTree();
        map<long long, int> posToId;
        int maxId = 0;
        for (int i = 0; i < N; i++) {
            scanf("%d%d%d", &stars[i].x, &stars[i].y, &stars[i].brightness);
            posToId[((long long)stars[i].y) * 100 - (long long)H * 100 / 2 + 1LL] = 0;
            posToId[((long long)stars[i].y) * 100 + (long long)H * 100 / 2 - 1LL] = 0;
        }
        sort(stars, stars + N);
        for (map<long long, int>::iterator itr = posToId.begin();
             itr != posToId.end(); ++itr) {
            itr->second = ++maxId;
        }
        int maxBrightness = 0, left = 0, right = 0;
        while (right != N) {
            // expand right
            do {
                int lower = posToId[((long long)stars[right].y) * 100 - (long long)H * 100 / 2 + 1LL];
                int upper = posToId[((long long)stars[right].y) * 100 + (long long)H * 100 / 2 - 1LL];
                updateSeg(1, 1, maxId, lower, upper, stars[right].brightness);
            } while (++right != N && stars[right].x == stars[right - 1].x);
            // shrink left
            while (stars[right - 1].x - stars[left].x >= W) {
                int lower = posToId[((long long)stars[left].y) * 100 - (long long)H * 100 / 2 + 1LL];
                int upper = posToId[((long long)stars[left].y) * 100 + (long long)H * 100 / 2 - 1LL];
                updateSeg(1, 1, maxId, lower, upper, -stars[left].brightness);
                left++;
            }
            maxBrightness = max(maxBrightness, segNodes[1].segMax);
        }
        printf("%d\n", maxBrightness);
    }
    return 0;
}

