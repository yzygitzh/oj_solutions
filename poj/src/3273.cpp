/*
 * POJ 3273 - Monthly Expense
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

int N, M;
int costs[100010];

bool isValid(int costLimit) {
    int currCost = 0, currMon = 0;
    for (int i = 0; i < N; i++) {
        if (currCost + costs[i] > costLimit) {
            currCost = 0;
            i--; // retry current cost until currMon is invalid
            currMon++;
            if (currMon == M) {
                return false;
            }
        } else {
            currCost += costs[i];
        }
    }
    return true;
}

int main() {
    int left = 0, right = 0;
    scanf("%d%d", &N, &M);
    for (int i = 0; i < N; i++) {
        scanf("%d", costs + i);
        right += costs[i];
    }
    while (left + 1 < right) {
        int mid = left + (right - left) / 2;
        if (isValid(mid)) {
            right = mid;
        } else {
            left = mid;
        }
    }
    if (isValid(left)) {
        cout << left << endl;
    } else {
        cout << right << endl;
    }
    return 0;
}

