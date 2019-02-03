/*
 * POJ 1125 - Stockbroker Grapevine
 * 
 */

#include <cmath>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <iostream>
#include <algorithm>
#include <vector>
#include <map>
#include <map>
#include <set>
#include <set>
#include <queue>

using namespace std;

int G[110][110];

int main() {
    while (true) {
        int nodeNum;
        cin >> nodeNum;
        if (nodeNum == 0) break;
        for (int i = 0; i < nodeNum; i++) {
            for (int j = 0; j < nodeNum; j++) {
                G[i][j] = (1 << 29);
            }
        }
        for (int i = 0; i < nodeNum; i++) {
            int srcNum;
            cin >> srcNum;
            for (int j = 0; j < srcNum; j++) {
                int tgtNode;
                int cost;
                cin >> tgtNode >> cost;
                G[i][tgtNode - 1] = cost;
            }
        }
        // floyd
        for (int k = 0; k < nodeNum; k++) {
            for (int i = 0; i < nodeNum; i++) {
                for (int j = 0; j < nodeNum; j++) {
                    G[i][j] = min(G[i][j], G[i][k] + G[k][j]);
                }
            }
        }
        // scan G
        int minSpan = (1 << 29);
        int minNode;
        for (int i = 0; i < nodeNum; i++) {
            int maxSpan = 0;
            for (int j = 0; j < nodeNum; j++) {
                if (i == j) continue;
                maxSpan = max(maxSpan, G[i][j]);
            }
            if (maxSpan < minSpan) {
                minSpan = maxSpan;
                minNode = i;
            }
        }
        if (minSpan == (1 << 29)) {
            cout << "disjoint" << endl;
        } else {
            cout << minNode + 1 << " " << minSpan << endl;
        }
    }
    return 0;
}
