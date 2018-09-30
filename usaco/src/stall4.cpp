/* Use the slash-star style comments or the system won't see your
   identification information */
/*
ID: yzylive1
TASK: stall4
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

ifstream fin ("stall4.in");
ofstream fout ("stall4.out");

/* virtual source: N+M+1
 * cows: 1...N
 * stalls: N+1...N+M
 * virtual sink: N+M+2
 */

int N, M;
int W[410][410] = {0};
class Edge {
public:
    int src, tgt;
    Edge(int _src, int _tgt): src(_src), tgt(_tgt) {}
    Edge(): src(0), tgt(0) {}
};
vector<Edge> adjMat[410];
Edge prevEdge[410][410];
int visited[410][410];

Edge BFS() {
    memset(prevEdge, 0, sizeof(prevEdge));
    memset(visited, 0, sizeof(visited));
    queue<Edge> bfsQ;
    for (vector<Edge>::iterator itr = adjMat[N + M + 1].begin();
         itr != adjMat[N + M + 1].end(); ++itr) {
        if (W[itr->src][itr->tgt]) {
            bfsQ.push(*itr);
            visited[itr->src][itr->tgt] = 1;
        }
    }
    while (!bfsQ.empty()) {
        Edge top = bfsQ.front();
        bfsQ.pop();
        if (top.tgt == N + M + 2) return top;
        for (vector<Edge>::iterator itr = adjMat[top.tgt].begin();
             itr != adjMat[top.tgt].end(); ++itr) {
            if (!visited[itr->src][itr->tgt] && W[itr->src][itr->tgt]) {
                visited[itr->src][itr->tgt] = 1;
                prevEdge[itr->src][itr->tgt] = top;
                bfsQ.push(*itr);
            }
        }
    }
    return Edge();
}

int findMaxFlow() {
    int maxFlow = 0;
    while (true) {
        Edge finalEdge = BFS();
        if (finalEdge.tgt != N + M + 2) break;
        Edge currEdge = finalEdge;
        // minCap must be 1
        while (currEdge.src) {
            W[currEdge.src][currEdge.tgt] -= 1;
            W[currEdge.tgt][currEdge.src] += 1;
            currEdge = prevEdge[currEdge.src][currEdge.tgt];
        }
        maxFlow++;
    }
    return maxFlow;
}

int main() {
    fin >> N >> M;
    for (int i = 0; i < N; i++) {
        W[N + M + 1][i + 1] += 1;
        adjMat[N + M + 1].push_back(Edge(N + M + 1, i + 1));
        adjMat[i + 1].push_back(Edge(i + 1, N + M + 1));
        int stallNum;
        fin >> stallNum;
        for (int j = 0; j < stallNum; j++) {
            int stall;
            fin >> stall;
            W[i + 1][N + stall] = 1;
            adjMat[i + 1].push_back(Edge(i + 1, N + stall));
            adjMat[N + stall].push_back(Edge(N + stall, i + 1));
            W[N + stall][N + M + 2] = 1;
            adjMat[N + stall].push_back(Edge(N + stall, N + M + 2));
            adjMat[N + M + 2].push_back(Edge(N + M + 2, N + stall));
        }
    }
    fout << findMaxFlow() << endl;
    return 0;
}

