/*
 * POJ 1258 - Agri-Net
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

int N;
int mat[110][110];
int inTree[110] = {0};
int dist[110] = {0};
int edgeSum = 0;

void prim() {
    edgeSum = 0;
    int nodeNum = 1;
    // init dist array
    for (int i = 0; i < N; i++) {
        inTree[i] = 0;
        dist[i] = mat[0][i];
    }
    inTree[0] = 1;
    while (nodeNum < N) {
        int minDis = 1000000;
        int node;
        for (int i = 0; i < N; i++) {
            if (!inTree[i] && dist[i] < minDis) {
                node = i;
                minDis = dist[i];
            }
        }
        inTree[node] = 1;
        edgeSum += minDis;
        // update dist
        for (int i = 0; i < N; i++) {
            if (!inTree[i] && dist[i] > mat[node][i]) {
                dist[i] = mat[node][i];
            }
        }
        nodeNum++;
    }
}

int main() {
    while (cin >> N) {
        for (int i = 0; i < N; i++) {
            for (int j = 0; j < N; j++) {
                cin >> mat[i][j];
            }
        }
        prim();
        cout << edgeSum << endl;
    }
    return 0;
}

