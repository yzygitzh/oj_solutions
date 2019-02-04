/*
 * POJ 1789 - Truck History
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

int truckNum;
string trucks[2010];
int G[2010][2010];
int minDis[2010];
int visited[2010];

int main() {
    while (true) {
        cin >> truckNum;
        if (truckNum == 0) break;
        for (int i = 0; i < truckNum; i++) {
            cin >> trucks[i];
            minDis[i] = (1 << 20);
            visited[i] = 0;
        }
        // calculate distances between truck pairs
        for (int i = 0; i < truckNum; i++) {
            for (int j = i; j < truckNum; j++) {
                int dis = 0;
                for (int k = 0; k < 7; k++) {
                    if (trucks[i][k] != trucks[j][k]) dis++;
                }
                G[j][i] = G[i][j] = dis;
            }
        }
        // prim
        minDis[0] = 0;
        int treeCost = 0;
        for (int i = 0; i < truckNum; i++) {
            // select min node
            int minNode, currMinDis = (1 << 20);
            for (int j = 0; j < truckNum; j++) {
                if (!visited[j] && minDis[j] < currMinDis) {
                    minNode = j;
                    currMinDis = minDis[j];
                }
            }
            visited[minNode] = 1;
            treeCost += currMinDis;
            // update minDis
            for (int j = 0; j < truckNum; j++) {
                minDis[j] = min(G[minNode][j], minDis[j]);
            }
        }
        cout << "The highest possible quality is 1/" << treeCost << "." << endl;
    }
    return 0;
}
