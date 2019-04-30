/*
 * POJ 1836 - Alignment
 *
 * Find LIS from both sides
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

double heights[1010];
int LISLeft[1010] = {0}, LISRight[1010] = {0};
double LISMinHeightLeft[1010] = {0}, LISMinHeightRight[1010] = {0};
int maxLeftLen, maxRightLen;
int personNum;

int main() {
    cin >> personNum;
    for (int i = 0; i < personNum; i++) {
        cin >> heights[i];
    }
    LISLeft[0] = LISRight[personNum - 1] = 1;
    maxLeftLen = maxRightLen = 1;
    LISMinHeightLeft[0] = LISMinHeightRight[0] = -1.0;
    LISMinHeightLeft[1] = heights[0];
    LISMinHeightRight[1] = heights[personNum - 1];
    for (int i = 1; i < personNum; i++) {
        // binary search for maximum IS length before i
        int left, right, maxLen;
        // from left
        left = 0, right = maxLeftLen;
        while (left + 1 < right) {
            int mid = left + (right - left) / 2;
            if (heights[i] - 1e-6 > LISMinHeightLeft[mid]) left = mid;
            else right = mid;
        }
        if (heights[i] - 1e-6 > LISMinHeightLeft[right]) maxLen = right;
        else maxLen = left;
        LISMinHeightLeft[maxLen + 1] = heights[i];
        LISLeft[i] = maxLen + 1;
        maxLeftLen = max(maxLeftLen, maxLen + 1);
        // from right
        left = 0, right = maxRightLen;
        while (left + 1 < right) {
            int mid = left + (right - left) / 2;
            if (heights[personNum - 1 - i] - 1e-6 > LISMinHeightRight[mid]) left = mid;
            else right = mid;
        }
        if (heights[personNum - 1 - i] - 1e-6 > LISMinHeightRight[right]) maxLen = right;
        else maxLen = left;
        LISMinHeightRight[maxLen + 1] = heights[personNum - 1 - i];
        LISRight[personNum - 1 - i] = maxLen + 1;
        maxRightLen = max(maxRightLen, maxLen + 1);
    }
    for (int i = 0; i < personNum - 1; i++) {
        LISLeft[i + 1] = max(LISLeft[i], LISLeft[i + 1]);
        LISRight[personNum - i - 2] = max(LISRight[personNum - i - 1], LISRight[personNum - i - 2]);
    }
    int answer = personNum;
    for (int i = 0; i < personNum - 1; i++) {
        answer = min(answer, personNum - LISLeft[i] - LISRight[i + 1]);
    }
    cout << answer << endl;
    return 0;
}

