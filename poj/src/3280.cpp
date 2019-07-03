/*
 * POJ 3280 - Cheapest Palindrome
 *
 * F[M][N]: lowest cost to transfer s[M:N] into palindrome
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

int N, M;
char inputStr[2010];
int F[2010][2010];
int cost[26][2];

int findCost(int left, int right) {
    if (F[left][right] == -1) {
        if (left == right) {
            F[left][right] = 0;
        } else {
            int minCost = 0x7FFFFFFF;
            minCost = min(minCost, cost[inputStr[left] - 'a'][0] + findCost(left + 1, right));
            minCost = min(minCost, cost[inputStr[left] - 'a'][1] + findCost(left + 1, right));
            minCost = min(minCost, cost[inputStr[right] - 'a'][0] + findCost(left, right - 1));
            minCost = min(minCost, cost[inputStr[right] - 'a'][1] + findCost(left, right - 1));
            if (inputStr[left] == inputStr[right]) {
                if (left + 1 < right) {
                    minCost = min(minCost, findCost(left + 1, right - 1));
                } else {
                    minCost = 0;
                }
            }
            F[left][right] = minCost;
        }
    }
    return F[left][right];
}

int main() {
    scanf("%d%d", &N, &M);
    scanf("%s", inputStr);
    for (int i = 0; i < M; i++) {
        for (int j = 0; j < M; j++) {
            F[i][j] = -1;
        }
    }
    for (int i = 0; i < N; i++) {
        char chr[1];
        int addCost, delCost;
        scanf("%s %d %d", chr, &addCost, &delCost);
        cost[chr[0] - 'a'][0] = addCost;
        cost[chr[0] - 'a'][1] = delCost;
    }
    printf("%d\n", findCost(0, M - 1));
    return 0;
}

