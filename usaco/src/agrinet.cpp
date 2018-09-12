/* Use the slash-star style comments or the system won't see your
   identification information */
/*
ID: yzylive1
TASK: agrinet
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

ifstream fin ("agrinet.in");
ofstream fout ("agrinet.out");

int N;
int mat[110][110];
int inTree[110] = {0};
int dist[110] = {0};
int edgeSum = 0;

void prim() {
    int nodeNum = 1;
    inTree[0] = 1;
    // init dist array
    for (int i = 0; i < N; i++) {
        dist[i] = mat[0][i];
    }
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
    fin >> N;
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            fin >> mat[i][j];
        }
    }
    prim();
    fout << edgeSum << endl;

    return 0;
}

