/*
 * POJ 2777 - Count Color
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

unsigned segNodeColor[400100]; // total color for segment
unsigned char segNodeValid[400100]; // all nodes are colored as segNodeColor
int L, T, O;

void buildSegTree() {
    for (int i = 0; i < 400100; i++) {
        segNodeColor[i] = 0x1;
        segNodeValid[i] = 1;
    }
}

void updateSeg(int nodeIdx, int nodeLeft, int nodeRight,
               int left, int right, int color) {
    if (nodeLeft == left && nodeRight == right) {
        segNodeColor[nodeIdx] = color;
        segNodeValid[nodeIdx] = 1;
    } else {
        int mid = nodeLeft + (nodeRight - nodeLeft) / 2;
        if (segNodeValid[nodeIdx]) {
            updateSeg(nodeIdx * 2, nodeLeft, mid, nodeLeft, mid, segNodeColor[nodeIdx]);
            updateSeg(nodeIdx * 2 + 1, mid + 1, nodeRight, mid + 1, nodeRight, segNodeColor[nodeIdx]);
            segNodeValid[nodeIdx] = 0;
        }
        if (left <= mid) {
            updateSeg(nodeIdx * 2, nodeLeft, mid, left, min(mid, right), color);
        }
        if (right >= mid + 1) {
            updateSeg(nodeIdx * 2 + 1, mid + 1, nodeRight, max(mid + 1, left), right, color);
        }
        segNodeColor[nodeIdx] = segNodeColor[nodeIdx * 2] | segNodeColor[nodeIdx * 2 + 1];
    }
}

int querySeg(int nodeIdx, int nodeLeft, int nodeRight, int left, int right) {
    if (segNodeValid[nodeIdx] || nodeLeft == left && nodeRight == right) {
        return segNodeColor[nodeIdx];
    } else {
        int result = 0;
        int mid = nodeLeft + (nodeRight - nodeLeft) / 2;
        if (left <= mid) {
            result |= querySeg(nodeIdx * 2, nodeLeft, mid, left, min(mid, right));
        }
        if (right >= mid + 1) {
            result |= querySeg(nodeIdx * 2 + 1, mid + 1, nodeRight, max(mid + 1, left), right);
        }
        return result;
    }
}

int main() {
    scanf("%d%d%d", &L, &T, &O);
    buildSegTree();
    int left, right, color;
    char command[10];
    for (int i = 0; i < O; i++) {
        scanf("%s", command);
        if (command[0] == 'C') {
            scanf("%d%d%d", &left, &right, &color);
            updateSeg(1, 1, L, left, right, (1 << (color - 1)));
        } else {
            scanf("%d%d", &left, &right);
            color = querySeg(1, 1, L, left, right);
            // printf("color %d\n", color);
            int colorNum = 0;
            while (color) {
                colorNum += (color & 1);
                color >>= 1;
            }
            printf("%d\n", colorNum);
        }
    }
    return 0;
}

