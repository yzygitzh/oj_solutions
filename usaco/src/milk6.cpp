/* Use the slash-star style comments or the system won't see your
   identification information */
/*
ID: yzylive1
TASK: milk6
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

ifstream fin ("milk6.in");
ofstream fout ("milk6.out");

/*
 * 1. build new network using weight as capacity
 *    and solve minimum cut
 * 2. to find minimum edge num, note that every
 *    edge with full capacity must belong to some
 *    minimum cut. build a new network, mark origin
 *    full-capacity edge's weights as 1, and solve
 *    minimum cut among these edges. as a result,
 *    the edge num is minimized.
 * 3. merge edges to decrease complexity
 */

class Edge {
public:
    int src, tgt;
    Edge(int _src, int _tgt): src(_src), tgt(_tgt) {}
    Edge(): src(0), tgt(0) {}
};
int N, M;
int originW[40][40] = {0};
int W[40][40];
vector<Edge> adjMat[40];
vector<Edge> edgeVec;

int prevNode[40];
int visited[40];

void recovW() {
    memcpy(W, originW, sizeof(originW));
}

void BFS() {
    memset(visited, 0, sizeof(visited));
    memset(prevNode, 0, sizeof(visited));
    queue<int> bfsQ;
    visited[1] = 1;
    bfsQ.push(1);
    while (!bfsQ.empty()) {
        int top = bfsQ.front();
        bfsQ.pop();
        for (int i = 0; i < adjMat[top].size(); i++) {
            int tgt = adjMat[top][i].tgt;
            if (!visited[tgt] && W[top][tgt]) {
                // cout << "C " << top << " " << tgt << endl;
                visited[tgt] = 1;
                prevNode[tgt] = top;
                bfsQ.push(tgt);
            }
        }
    }
}

int findMaxFlow() {
    int maxFlow = 0;
    while (true) {
        BFS();
        if (!prevNode[N]) break;
        // cout << prevNode[N] << endl;
        int minCap = 2000010, currP = N;
        while (currP != 1) {
            int src = prevNode[currP];
            int currCap = W[src][currP];
            if (currCap < minCap) minCap = currCap;
            currP = src;
        }
        currP = N;
        while (currP != 1) {
            int src = prevNode[currP];
            W[src][currP] -= minCap;
            W[currP][src] += minCap;
            currP = src;
        }
        // cout << "B " << W[4][5][0] << endl;
        maxFlow += minCap;
    }
    return maxFlow;
}

void binW() {
    memset(originW, 0, sizeof(originW));
    for (vector<Edge>::iterator itr = edgeVec.begin() + 1;
         itr != edgeVec.end(); ++itr) {
        if (!W[itr->src][itr->tgt]) {
            originW[itr->src][itr->tgt]++;
        } else {
            originW[itr->src][itr->tgt] = 2000000;
        }
        // cout << itr->src << " " << itr->tgt << " " << originW[itr->src][itr->tgt][itr->wid] << endl;
    }
}

vector<int> edgeIdList;
int findMinCut() {
    binW();
    recovW();
    int maxFlow = findMaxFlow();
    int minEdgeNum = maxFlow;
    for (int i = 1; i < edgeVec.size(); i++) {
        // try delete edge
        originW[edgeVec[i].src][edgeVec[i].tgt] -= 1;
        recovW();
        int currFlow = findMaxFlow();
        if (currFlow < maxFlow) {
            edgeIdList.push_back(i);
            maxFlow = currFlow;
            if (!maxFlow) break;
        } else {
            originW[edgeVec[i].src][edgeVec[i].tgt] += 1;
        }
    }
    return minEdgeNum;
}

int main() {
    fin >> N >> M;
    // skip edge id 0
    edgeVec.push_back(Edge());
    for (int i = 0; i < M; i++) {
        int src, tgt, weight;
        fin >> src >> tgt >> weight;

        edgeVec.push_back(Edge(src, tgt));
        adjMat[src].push_back(Edge(src, tgt));
        adjMat[tgt].push_back(Edge(tgt, src));

        originW[src][tgt] += weight;
    }
    // 1. find min cost
    recovW();
    int minCost = findMaxFlow();
    // cout << "==========2" << endl;
    // 2. change edge weight, find min edge num
    int minEdgeNum = findMinCut();

    fout << minCost << " " << minEdgeNum << endl;
    for (vector<int>::iterator itr = edgeIdList.begin();
         itr != edgeIdList.end(); ++itr) {
        fout << *itr << endl;
    }

    return 0;
}

