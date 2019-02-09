/*
 * POJ 1459 - Power Network
 *
 * Connect power plants to source and consumers to sink
 */

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

int n, np, nc, m;

vector<vector<long long> > adjMat(110, vector<long long>(110, 0));

vector<int> bfs() {
    vector<int> visited(n + 2, 0), prev(n + 2, -1);
    queue<int> bfsQ;
    bfsQ.push(0);
    visited[0] = 1;
    while (!bfsQ.empty()) {
        int node = bfsQ.front();
        bfsQ.pop();
        if (node == n + 1) break;
        for (int i = 0; i <= n + 1; i++) {
            if (!visited[i] && adjMat[node][i] > 0) {
                visited[i] = 1;
                prev[i] = node;
                bfsQ.push(i);
            }
        }
    }
    return prev;
}

int edmondKarp() {
    long long maxFlow = 0;
    while (true) {
        vector<int> prev = bfs();
        if (prev[n + 1] == -1) break;
        long long minCap = (1LL << 60);
        int node;
        node = n + 1;
        while (prev[node] != -1) {
            minCap = min(minCap, adjMat[prev[node]][node]);
            node = prev[node];
        }
        node = n + 1;
        while (prev[node] != -1) {
            adjMat[prev[node]][node] -= minCap;
            node = prev[node];
        }
        maxFlow += minCap;
    }
    return maxFlow;
}

int main() {
    while (cin >> n >> np >> nc >> m) {
        string inputLine;
        for (int i = 0; i <= n + 1; i++) {
            for (int j = 0; j <= n + 1; j++) {
                adjMat[i][j] = 0;
            }
        }
        for (int i = 0; i < m; i++) {
            int src, tgt, cap;
            cin >> inputLine;
            sscanf(inputLine.c_str(), "(%d,%d)%d", &src, &tgt, &cap);
            adjMat[src + 1][tgt + 1] += (long long)cap;
        }
        for (int i = 0; i < np; i++) {
            int node, nodeP;
            cin >> inputLine;
            sscanf(inputLine.c_str(), "(%d)%d", &node, &nodeP);
            adjMat[0][node + 1] += nodeP;
        }
        for (int i = 0; i < nc; i++) {
            int node, nodeC;
            cin >> inputLine;
            sscanf(inputLine.c_str(), "(%d)%d", &node, &nodeC);
            adjMat[node + 1][n + 1] += nodeC;
        }
        cout << edmondKarp() << endl;
    }
    return 0;
}

