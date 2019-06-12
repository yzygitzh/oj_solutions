/*
 * POJ 3258 - River Hopscotch
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

int L, M, N;
int rocks[50010];

bool validate(int minStep) {
    int removed = 0, currPos = 0;
    for (int i = 0; i < N; i++) {
        // invariant: <= currPos is valid.
        // greedily remove the latter rock.

        // the last rock might be removed.
        // this is the same as removing second last rock.

        if (currPos + minStep > rocks[i]) {
            // remove the (i+1)-th rock
            removed++;
        } else {
            currPos = rocks[i];
        }
    }
    return removed <= M;
}

int main() {
    scanf("%d%d%d", &L, &N, &M);
    for (int i = 0; i < N; i++) {
        scanf("%d", rocks + i);
    }
    sort(rocks, rocks + N);
    rocks[N++] = L;
    int left = 0, right = L;
    while (left + 1 < right) {
        int mid = left + (right - left) / 2;
        if (validate(mid)) {
            left = mid;
        } else {
            right = mid;
        }
    }
    if (validate(right)) {
        cout << right << endl;
    } else {
        cout << left << endl;
    }
    return 0;
}

