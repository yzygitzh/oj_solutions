/*
 * POJ 2828 - Buy Tickets
 *
 * Process people reversely.
 * Use suffix array to maintain number of empty slots.
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
int suffix[200010];
int vals[200010];
int people[200010][2];

int lowbit(int x) {
    return x & -x;
}

void updateSuffix(int pos, int val) {
    while (pos < 200010) {
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
    while (scanf("%d", &N) > 0) {
        for (int i = 0; i < N; i++) {
            scanf("%d%d", &people[i][0], &people[i][1]);
            suffix[i] = i;
        }
        memset(suffix, 0, sizeof(suffix));
        for (int i = 1; i <= N; i++) {
            updateSuffix(i, 1);
        }
        for (int i = N - 1; i >= 0; i--) {
            // find minimum pos that has people[i][0] + 1 empty slots
            int leftPos = 1, rightPos = N;
            while (leftPos + 1 < rightPos) {
                int midPos = leftPos + (rightPos - leftPos) / 2;
                if (getSuffix(midPos) < people[i][0] + 1) {
                    leftPos = midPos;
                } else {
                    rightPos = midPos;
                }
            }
            if (getSuffix(leftPos) == people[i][0] + 1) {
                vals[leftPos - 1] = people[i][1];
                updateSuffix(leftPos, -1);
            } else {
                vals[rightPos - 1] = people[i][1];
                updateSuffix(rightPos, -1);
            }
        }
        for (int i = 0; i < N; i++) {
            cout << vals[i];
            if (i == N - 1) {
                cout << endl;
            } else {
                cout << " ";
            }
        }
    }
    return 0;
}

