/* Use the slash-star style comments or the system won't see your
   identification information */
/*
ID: yzylive1
TASK: butter
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

ifstream fin ("butter.in");
ofstream fout ("butter.out");

class DijkElem {
public:
    int dis, src, tgt;
    DijkElem(int _d, int _s, int _t): dis(_d), src(_s), tgt(_t) {}
    bool operator<(const DijkElem &d) const {
        return dis > d.dis;
    }
};

int N, P, C;
vector<DijkElem> adjList[1000];
int disMat[1000][1000];
int cows[1000];

int visited[1000];
int nodeCost[1000] = {0};
int disVec[1000];
priority_queue<DijkElem> dijkQ;

void floyd() {
    for (int k = 1; k <= P; k++) {
        for (int i = 1; i <= P; i++) {
            for (int j = i + 1; j <= P; j++) {
                if (disMat[i][k] + disMat[k][j] < disMat[i][j]) {
                    disMat[i][j] = disMat[j][i] = disMat[i][k] + disMat[k][j];
                }
            }
        }
    }
}

void dijk(int origin) {
    // init visited
    memset(visited, 0, sizeof(visited));
    visited[origin] = 1;
    // init disVec
    for (int i = 1; i <= P; i++) {
        disVec[i] = 1000000000;
    }
    for (vector<DijkElem>::iterator itr = adjList[origin].begin();
         itr != adjList[origin].end(); ++itr) {
        disVec[itr->tgt] = itr->dis;
    }
    disVec[origin] = 0;
    // cout << "HI " << origin << endl;
    // init dijkQ
    while (!dijkQ.empty()) dijkQ.pop();
    for (vector<DijkElem>::iterator itr = adjList[origin].begin();
         itr != adjList[origin].end(); ++itr) {
        // cout << "ORI " << itr->src << " " << itr->tgt << " " << itr->dis << endl;
        dijkQ.push(*itr);
    }
    // start dijk
    while (!dijkQ.empty()) {
        DijkElem top = dijkQ.top();
        dijkQ.pop();
        if (visited[top.tgt]) continue;
        else (visited[top.tgt]) = 1;
        // cout << "HA " << top.src << " " << top.tgt << " " << top.dis << endl;
        // update rest points through top->tgt
        for (vector<DijkElem>::iterator itr = adjList[top.tgt].begin();
             itr != adjList[top.tgt].end(); ++itr) {
            // cout << "SEE " << origin << " " << itr->tgt << " " << disVec[itr->tgt] << endl;
            if (disVec[itr->tgt] > disVec[top.tgt] + itr->dis) {
                disVec[itr->tgt] = disVec[top.tgt] + itr->dis;
                // cout << "PUSH " << origin << " " << itr->tgt << " " << disVec[itr->tgt] << endl;
                dijkQ.push(DijkElem(disVec[itr->tgt], origin, itr->tgt));
            }
        }
    }
    for (int i = 1; i <= P; i++) {
        // if (disVec[i] != disMat[origin][i]) {
        //     cout << "WRONG " << origin << " " << i << " " << disVec[i] << " " << disMat[origin][i] << endl;
        // }
        if (disVec[i] != 1000000000 && nodeCost[i] != 1000000000) nodeCost[i] += disVec[i];
        else nodeCost[i] = 1000000000;
        // cout << origin << " " << nodeCost[i] << endl;
    }
}

int main() {
    fin >> N >> P >> C;
    for (int i = 0; i < N; i++) {
        fin >> cows[i]; 
    }
    for (int i = 1; i <= P; i++) {
        for (int j = 1; j <= P; j++) {
            disMat[i][j] = 1000000000;
            if (i == j) disMat[i][j] = 0;
        }
    }
    for (int i = 0; i < C; i++) {
        int src, tgt, dis;
        fin >> src >> tgt >> dis;
        if (src == tgt) continue;
        adjList[src].push_back(DijkElem(dis, src, tgt));
        adjList[tgt].push_back(DijkElem(dis, tgt, src));
        disMat[src][tgt] = disMat[tgt][src] = dis;
    }
    // floyd();
    for (int i = 0; i < N; i++) {
        dijk(cows[i]);
    }
    int minCost = 1000000000;
    for (int i = 1; i <= P; i++) {
        if (minCost > nodeCost[i]) {
            minCost = nodeCost[i];
        }
    }
    fout << minCost << endl;

    return 0;
}

