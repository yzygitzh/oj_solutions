/*
 * POJ 2485 - Highways
 * 
 * MST.
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
#include <queue>

using namespace std;

int G[510][510];
int visited[510];
int minDis[510];

int main() {
    int caseNum;
    scanf("%d", &caseNum);
    for (int i = 0; i < caseNum; i++) {
        int nodeNum;
        scanf("%d", &nodeNum);
        for (int j = 0; j < nodeNum; j++) {
            visited[j] = 0;
            minDis[j] = ~(1 << 31);
            for (int k = 0; k < nodeNum; k++) {
                scanf("%d", &G[j][k]);
            }
        }
        // prim
        minDis[0] = 0;
        int treeCost = 0;
        for (int j = 0; j < nodeNum; j++) {
            // find min node
            int currMinDis = ~(1 << 31), minNode;
            for (int k = 0; k < nodeNum; k++) {
                if (!visited[k] && minDis[k] < currMinDis) {
                    currMinDis = minDis[k];
                    minNode = k;
                }
            }
            visited[minNode] = 1;
            treeCost = max(treeCost, currMinDis);
            // update minDis
            for (int k = 0; k < nodeNum; k++) {
                minDis[k] = min(minDis[k], G[minNode][k]);
            }
        }
        cout << treeCost << endl;
    }
    return 0;
}
