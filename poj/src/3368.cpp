/*
 * POJ 3368 - Frequent values 
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
    int segMaxCnt;
    int segLeft, segLeftCnt;
    int segRight, segRightCnt;
};

SegNode segNodes[400010];
int vals[100010];
vector<int> sortedVals(100010);

void buildSegTree(int nodeIdx, int nodeLeft, int nodeRight) {
    if (nodeLeft == nodeRight) {
        segNodes[nodeIdx].segLeft = segNodes[nodeIdx].segRight = vals[nodeLeft];
        segNodes[nodeIdx].segLeftCnt = segNodes[nodeIdx].segRightCnt = 
        segNodes[nodeIdx].segMaxCnt = 1;
    } else {
        int mid = nodeLeft + (nodeRight - nodeLeft) / 2;
        buildSegTree(nodeIdx * 2, nodeLeft, mid);
        buildSegTree(nodeIdx * 2 + 1, mid + 1, nodeRight);
        sortedVals.clear();
        for (int i = nodeLeft; i <= nodeRight; i++) {
            sortedVals.push_back(vals[i]);
        }
        sort(sortedVals.begin(), sortedVals.end());
        segNodes[nodeIdx].segMaxCnt = 0;
        for (int i = 0; i < sortedVals.size();) {
            int currNumCnt = 0;
            do {
                currNumCnt++;
            } while (++i < sortedVals.size() && sortedVals[i] == sortedVals[i - 1]);
            if (i == currNumCnt) {
                segNodes[nodeIdx].segLeft = sortedVals[i - 1];
                segNodes[nodeIdx].segLeftCnt = currNumCnt;
            }
            if (i == sortedVals.size()) {
                segNodes[nodeIdx].segRight = sortedVals[i - 1];
                segNodes[nodeIdx].segRightCnt = currNumCnt;
            }
            segNodes[nodeIdx].segMaxCnt = max(segNodes[nodeIdx].segMaxCnt, currNumCnt);
        }
    }
}

SegNode querySeg(int nodeIdx, int nodeLeft, int nodeRight, int left, int right) {
    if (nodeLeft == left && nodeRight == right) {
        return segNodes[nodeIdx];
    } else {
        SegNode result, sLeft, sRight;
        result.segMaxCnt = 0;
        int mid = nodeLeft + (nodeRight - nodeLeft) / 2;
        if (left <= mid) {
            sLeft = querySeg(nodeIdx * 2, nodeLeft, mid, left, min(mid, right));
            result.segMaxCnt = max(result.segMaxCnt, sLeft.segMaxCnt);
            result.segLeft = sLeft.segLeft;
            result.segLeftCnt = sLeft.segLeftCnt;
            if (right < mid + 1) {
                result.segRight = sLeft.segRight;
                result.segRightCnt = sLeft.segRightCnt;
            }
        }
        if (right >= mid + 1) {
            sRight = querySeg(nodeIdx * 2 + 1, mid + 1, nodeRight, max(mid + 1, left), right);
            result.segMaxCnt = max(result.segMaxCnt, sRight.segMaxCnt);
            result.segRight = sRight.segRight;
            result.segRightCnt = sRight.segRightCnt;
            if (left > mid) {
                result.segLeft = sRight.segLeft;
                result.segLeftCnt = sRight.segLeftCnt;
            }
        }
        if (left <= mid && right >= mid + 1 &&
            sLeft.segRight == sRight.segLeft) {
            result.segMaxCnt = max(result.segMaxCnt, sLeft.segRightCnt + sRight.segLeftCnt);
            if (sLeft.segLeft == sLeft.segRight) {
                result.segLeftCnt = sLeft.segMaxCnt + sRight.segLeftCnt;
            }
            if (sRight.segLeft == sRight.segRight) {
                result.segRightCnt = sRight.segMaxCnt + sLeft.segRightCnt;
            }
        }
        return result;
    }
}

int main() {
    int N, Q;
    while (true) {
        scanf("%d", &N);
        if (N == 0) break;
        scanf("%d", &Q);
        for (int i = 1; i <= N; i++) {
            scanf("%d", vals + i);
        }
        buildSegTree(1, 1, N);
        for (int i = 0; i < Q; i++) {
            int left, right;
            scanf("%d%d", &left, &right);
            printf("%d\n", querySeg(1, 1, N, left, right).segMaxCnt);
        }
    }
    return 0;
}

