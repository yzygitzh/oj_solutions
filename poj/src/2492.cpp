/*
 * POJ 2492 - A Bug's Life
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

int T, N, M;
int parent[2010];
int partner[2010];

int findParent(int idx) {
    if (idx != parent[idx]) {
        parent[idx] = findParent(parent[idx]);
    }
    return parent[idx];
}

void mergeSet(int idx1, int idx2) {
    int parent1 = findParent(idx1);
    int parent2 = findParent(idx2);
    parent[parent1] = parent2;
}

int main() {
    scanf("%d", &T);
    for (int i = 0; i < T; i++) {
        scanf("%d%d", &N, &M);
        for (int j = 1; j <= N; j++) {
            parent[j] = j;
            partner[j] = -1;
        }
        bool suspicious = false;
        for (int j = 0; j < M; j++) {
            int idx1, idx2;
            scanf("%d %d", &idx1, &idx2);
            if (suspicious) {
                continue;
            }
            if (partner[idx1] == -1) {
                partner[idx1] = findParent(idx2);
            } else {
                if (findParent(idx1) == findParent(idx2) ||
                    partner[idx2] != -1 &&
                    findParent(partner[idx1]) == findParent(partner[idx2])) {
                    suspicious = true;
                    continue;
                }
                mergeSet(partner[idx1], idx2);
            }
            if (partner[idx2] == -1) {
                partner[idx2] = findParent(idx1);
            } else {
                if (findParent(idx1) == findParent(idx2) ||
                    partner[idx1] != -1 &&
                    findParent(partner[idx1]) == findParent(partner[idx2])) {
                    suspicious = true;
                    continue;
                }
                mergeSet(partner[idx2], idx1);
            }
        }
        printf("Scenario #%d:\n", i + 1);
        if (suspicious) {
            printf("Suspicious bugs found!\n");
        } else {
            printf("No suspicious bugs found!\n");
        }
        printf("\n");
    }
    return 0;
}

