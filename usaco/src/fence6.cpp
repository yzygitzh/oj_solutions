/* Use the slash-star style comments or the system won't see your
   identification information */
/*
ID: yzylive1
TASK: fence6
LANG: C++
*/
/* LANG can be C++20 or C++14 for those more recent releases */
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

ifstream fin ("fence6.in");
ofstream fout ("fence6.out");

/*
 * For each edge, break it and calculate shortest path
 * between its two endpoints, O(N^3)
 */

int N;
int W[110];
int tmpG[110][2][110] = {0};
int G[110][2][110][2] = {0};

int dijkDis[110][2];
int vis[110][2];

int dijk(int edgeId) {
    for (int i = 1; i <= N; i++) {
        dijkDis[i][0] = dijkDis[i][1] = 1000000000;
        vis[i][0] = vis[i][1] = 0;
    }
    G[edgeId][0][edgeId][1] = G[edgeId][1][edgeId][0] = 1000000000;
    dijkDis[edgeId][0] = 0;

    int rest = N * 2;
    while (rest) {
        int currEdgeId, currEnd, minDis = 1000000000;
        // find smallest dijkDis
        for (int i = 1; i <= N; i++) {
            for (int j = 0; j < 2; j++) {
                if (!vis[i][j] && dijkDis[i][j] < minDis) {
                    minDis = dijkDis[i][j];
                    currEdgeId = i;
                    currEnd = j;
                }
            }
        }
        // cout << currEdgeId << " " << currEnd << " " << minDis << endl;
        // update dijkDis using current node
        for (int i = 1; i <= N; i++) {
            for (int j = 0; j < 2; j++) {
                if (!vis[i][j] &&
                    dijkDis[currEdgeId][currEnd] +
                    G[currEdgeId][currEnd][i][j] < dijkDis[i][j]) {
                    // cout << currEdgeId << " " << currEnd << " "
                    //      << i << " " << j << " " << G[currEdgeId][currEnd][i][j] << endl;
                    dijkDis[i][j] = dijkDis[currEdgeId][currEnd] +
                                    G[currEdgeId][currEnd][i][j];
                }
            }
        }
        vis[currEdgeId][currEnd] = 1;
        rest--;
    }
    G[edgeId][0][edgeId][1] = G[edgeId][1][edgeId][0] = W[edgeId];
    // cout << dijkDis[edgeId][1] << endl;
    return dijkDis[edgeId][1] + W[edgeId];
}

int main() {
    fin >> N;
    for (int i = 1; i <= N; i++) {
        G[i][0][i][0] = G[i][1][i][1] = 0;
        for (int j = 1; j <= N; j++) {
            if (i != j) G[i][0][j][0] = G[i][0][j][1] = G[i][1][j][0] = G[i][1][j][1] = 1000000000;
        }
    }
    for (int i = 0; i < N; i++) {
        int edgeId;
        fin >> edgeId;
        fin >> W[edgeId];
        int N1, N2, tgt;
        fin >> N1 >> N2;
        for (int j = 0; j < N1; j++) {
            fin >> tgt;
            tmpG[edgeId][0][tgt] = 1;
        }
        for (int j = 0; j < N2; j++) {
            fin >> tgt;
            tmpG[edgeId][1][tgt] = 1;
        }
        G[edgeId][0][edgeId][1] = G[edgeId][1][edgeId][0] = W[edgeId];
    }
    for (int i = 1; i <= N; i++) {
        for (int j = 1; j <= N; j++) {
            // j1--Wj--j0:i0--Wi--i1
            if (tmpG[i][0][j] && tmpG[j][0][i]) {
                G[i][0][j][0] = G[j][0][i][0] = 0;
            }
            // j0--Wj--j1:i0--Wi--i1
            if (tmpG[i][0][j] && tmpG[j][1][i]) {
                G[i][0][j][1] = G[j][1][i][0] = 0;
            }
            // j1--Wj--j0:i1--Wi--i0
            if (tmpG[i][1][j] && tmpG[j][0][i]) {
                G[i][1][j][0] = G[j][0][i][1] = 0;
            }
            // j0--Wj--j1:i1--Wi--i0
            if (tmpG[i][1][j] && tmpG[j][1][i]) {
                G[i][1][j][1] = G[j][1][i][1] = 0;
            }
        }
    }
    int minFence = 1000000000;
    for (int i = 1; i <= N; i++) {
        int dijkResult = dijk(i);
        if (dijkResult < minFence) minFence = dijkResult;
    }
    fout << minFence << endl;

    return 0;
}

