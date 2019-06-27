/*
 * POJ 1703 - Find them, Catch them
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
int parent[100010];
int enemy[100010];

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
        for (int i = 1; i <= N; i++) {
            parent[i] = i;
            enemy[i] = -1;
        }
        if (N == 2) {
            enemy[1] = 2;
            enemy[2] = 1;
        }
        for (int i = 0; i < M; i++) {
            char cmd[10];
            int idx1, idx2;
            scanf("%s %d %d", cmd, &idx1, &idx2);
            if (cmd[0] == 'A') {
                // Note that we cannot use "no enemy" to judge "not sure" case
                // because cases are where two both have enemies, but the enemies
                // themselves have no relationship.
                if (findParent(idx1) == findParent(idx2)) {
                    printf("In the same gang.\n");
                } else if (enemy[idx2] != -1 && findParent(idx1) == findParent(enemy[idx2]) ||
                           enemy[idx1] != -1 && findParent(idx2) == findParent(enemy[idx1])) {
                    printf("In different gangs.\n");
                } else {
                    printf("Not sure yet.\n");
                }
            } else if (cmd[0] == 'D') {
                if (enemy[idx1] == -1) {
                    enemy[idx1] = findParent(idx2);
                } else {
                    mergeSet(enemy[idx1], idx2);
                }
                if (enemy[idx2] == -1) {
                    enemy[idx2] = findParent(idx1);
                } else {
                    mergeSet(enemy[idx2], idx1);
                }
            }
        }
    }
    return 0;
}

