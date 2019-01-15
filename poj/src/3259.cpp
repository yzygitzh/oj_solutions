/*
 * POJ 3259 - Wormholes
 *
 * Seems bellman-ford cannot solve the problem
 */

#include <cmath>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <iostream>
#include <algorithm>
#include <vector>
#include <map>
#include <set>

using namespace std;

int minDis[510][510];

bool floyd(int N) {
    // do floyd
    for (int k = 1; k <= N; k++) {
        for (int i = 1; i <= N; i++) {
            for (int j = 1; j <= N; j++) {
                int newDis = minDis[i][k] + minDis[k][j];
                if (newDis < minDis[i][j]) minDis[i][j] = newDis;
            }
            if (minDis[i][i] < 0) return true;
        }
    }
    return false;
}

int main() {
    int F;
    scanf("%d", &F);
    for (int i = 0; i < F; i++) {
        int N, M, W;
        scanf("%d%d%d", &N, &M, &W);
        memset(minDis, 0x3f, sizeof(minDis));
        for (int i = 0; i < N; i++) minDis[i][i] = 0;

        int src, tgt, weight;
        for (int j = 0; j < M; j++) {
            scanf("%d%d%d", &src, &tgt, &weight);
            if (weight < minDis[src][tgt]) minDis[src][tgt] = minDis[tgt][src] = weight;
        }
        for (int j = 0; j < W; j++) {
            scanf("%d%d%d", &src, &tgt, &weight);
            if (-weight < minDis[src][tgt]) minDis[src][tgt] = -weight;
        }

        printf(floyd(N) ? "YES\n" : "NO\n");
    }

    return 0;
}
