/*
 * POJ 2750 - Potted Flower
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
    int sum;
    int minSeg, maxSeg;
    int minSegLeft, minSegRight, maxSegLeft, maxSegRight;
};

SegNode segNodes[400100];
int N, M;

void buildSegTree() {
    memset(segNodes, 0, sizeof(segNodes));
}

void updateSeg(int nodeIdx, int nodeLeft, int nodeRight,
               int idx, int val) {
    SegNode *p = &segNodes[nodeIdx];
    if (nodeLeft == nodeRight) {
        p->sum = p->minSeg = p->maxSeg =
        p->minSegLeft = p->minSegRight = p->maxSegLeft = p->maxSegRight = val;
    } else {
        int mid = nodeLeft + (nodeRight - nodeLeft) / 2;
        if (idx <= mid) {
            updateSeg(nodeIdx * 2, nodeLeft, mid, idx, val);
        }
        if (idx >= mid + 1) {
            updateSeg(nodeIdx * 2 + 1, mid + 1, nodeRight, idx, val);
        }
        SegNode *pLeft = &segNodes[nodeIdx * 2],
                *pRight = &segNodes[nodeIdx * 2 + 1];

        p->sum = pLeft->sum + pRight->sum;
        p->minSeg = min(min(pLeft->minSeg, pRight->minSeg), pLeft->minSegRight + pRight->minSegLeft);
        p->maxSeg = max(max(pLeft->maxSeg, pRight->maxSeg), pLeft->maxSegRight + pRight->maxSegLeft);
        p->minSegLeft = min(pLeft->minSegLeft, pLeft->sum + pRight->minSegLeft);
        p->maxSegLeft = max(pLeft->maxSegLeft, pLeft->sum + pRight->maxSegLeft);
        p->minSegRight = min(pRight->minSegRight, pRight->sum + pLeft->minSegRight);
        p->maxSegRight = max(pRight->maxSegRight, pRight->sum + pLeft->maxSegRight);
    }
}

int main() {
    scanf("%d", &N);
    buildSegTree();
    for (int i = 1; i <= N; i++) {
        int val;
        scanf("%d", &val);
        updateSeg(1, 1, N, i, val);
    }
    scanf("%d", &M);
    for (int i = 0; i < M; i++) {
        int idx, val;
        scanf("%d%d", &idx, &val);
        updateSeg(1, 1, N, idx, val);
        if (segNodes[1].maxSeg == segNodes[1].sum && segNodes[1].sum > 0) {
            printf("%d\n", segNodes[1].sum - segNodes[1].minSeg);
        } else {
            printf("%d\n", max(segNodes[1].maxSeg, segNodes[1].sum - segNodes[1].minSeg));
        }
    }
    return 0;
}

