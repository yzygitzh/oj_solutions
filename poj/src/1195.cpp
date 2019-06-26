/*
 * POJ 1195 - Mobile phones
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

int S;
int suffix[1100][1100];

int lowbit(int x) {
    return x & -x;
}

void updateSuffix(int row, int col, int val) {
    for (int i = row; i < 1100; i += lowbit(i)) {
        for (int j = col; j < 1100; j += lowbit(j)) {
            suffix[i][j] += val;
        }
    }
}

int getSuffix(int row, int col) {
    int result = 0;
    for (int i = row; i > 0; i -= lowbit(i)) {
        for (int j = col; j > 0; j -= lowbit(j)) {
            result += suffix[i][j];
        }
    }
    return result;
}

int main() {
    int command;
    memset(suffix, 0, sizeof(suffix));
    bool terminated = false;
    while (!terminated) {
        scanf("%d", &command);
        switch (command) {
        case 0:
            scanf("%d", &S);
            break;
        case 1:
            int row, col, val;
            scanf("%d%d%d", &row, &col, &val);
            updateSuffix(row + 1, col + 1, val);
            break;
        case 2:
            int row1, col1, row2, col2;
            scanf("%d%d%d%d", &row1, &col1, &row2, &col2);
            printf("%d\n", getSuffix(row2 + 1, col2 + 1) -
                           getSuffix(row2 + 1, col1) -
                           getSuffix(row1, col2 + 1) +
                           getSuffix(row1, col1));
            break;
        case 3:
            terminated = true;
            break;
        default:
            break;
        }
    }
    return 0;
}

