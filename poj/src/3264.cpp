/*
 * POJ 3264 - Balanced Lineup
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
    int segMin, segMax;
};

SegNode segNodes[200100];

void buildSegTree() {
    memset(segNodes, 0, sizeof(segNodes));
}

void updateSeg(int nodeIdx, int nodeLeft, int nodeRight, int idx, int val) {
    if (nodeLeft == nodeRight) {
        segNodes[nodeIdx].segMin = val;
        segNodes[nodeIdx].segMax = val;
    } else {
        int mid = nodeLeft + (nodeRight - nodeLeft) / 2;
        if (idx <= mid) {
            updateSeg(nodeIdx * 2, nodeLeft, mid, idx, val);
        } else {
            updateSeg(nodeIdx * 2 + 1, mid + 1, nodeRight, idx, val);
        }
        segNodes[nodeIdx].segMin = min(segNodes[nodeIdx * 2].segMin, segNodes[nodeIdx * 2 + 1].segMin);
        segNodes[nodeIdx].segMax = max(segNodes[nodeIdx * 2].segMax, segNodes[nodeIdx * 2 + 1].segMax);
    }
}

void querySeg(int nodeIdx, int nodeLeft, int nodeRight,
                 int left, int right, int& segMin, int& segMax) {
    if (nodeLeft == left && nodeRight == right) {
        segMin = min(segMin, segNodes[nodeIdx].segMin);
        segMax = max(segMax, segNodes[nodeIdx].segMax);
    } else {
        int mid = nodeLeft + (nodeRight - nodeLeft) / 2;
        if (left <= mid) {
            querySeg(nodeIdx * 2, nodeLeft, mid,
                     left, min(mid, right), segMin, segMax);
        }
        if (right >= mid + 1) {
            querySeg(nodeIdx * 2 + 1, mid + 1, nodeRight,
                     max(mid + 1, left), right, segMin, segMax);
        }
    }
}

int main() {
    int N, Q, height;
    scanf("%d%d", &N, &Q);
    buildSegTree();
    for (int i = 1; i <= N; i++) {
        scanf("%d", &height);
        updateSeg(1, 1, N, i, height);
    }
    for (int i = 0; i < Q; i++) {
        int left, right;
        scanf("%d%d", &left, &right);
        int minH = 1000010, maxH = 0;
        querySeg(1, 1, N, left, right, minH, maxH);
        printf("%d\n", maxH - minH);
    }
    return 0;
}

