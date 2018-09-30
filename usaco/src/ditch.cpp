/* Use the slash-star style comments or the system won't see your
   identification information */
/*
ID: yzylive1
TASK: ditch
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

ifstream fin ("ditch.in");
ofstream fout ("ditch.out");

int N, M;
class Edge {
public:
    int src, tgt;
    Edge(int _src, int _tgt): src(_src), tgt(_tgt) {}
    Edge(): src(0), tgt(0) {}
};
vector<Edge> adjList[210];
int W[210][210] = {0};
int visited[210][210];
Edge prevEdge[210][210];

Edge BFS() {
    memset(visited, 0, sizeof(visited));
    memset(prevEdge, 0, sizeof(prevEdge));
    queue<Edge> bfsQ;
    for (vector<Edge>::iterator itr = adjList[1].begin();
         itr != adjList[1].end(); ++itr) {
        if (W[itr->src][itr->tgt]) {
            bfsQ.push(*itr);
            visited[itr->src][itr->tgt] = 1;
        }
    }
    while (!bfsQ.empty()) {
        Edge top = bfsQ.front();
        bfsQ.pop();
        if (top.tgt == M) return top;
        for (vector<Edge>::iterator itr = adjList[top.tgt].begin();
             itr != adjList[top.tgt].end(); ++itr) {
            if (!visited[itr->src][itr->tgt] && W[itr->src][itr->tgt]) {
                prevEdge[itr->src][itr->tgt] = top;
                visited[itr->src][itr->tgt] = 1;
                bfsQ.push(*itr);
            }
        }
    }
    return Edge();
}

int findMaxFlow() {
    int flow = 0;
    while (true) {
        // cout << "BFS" << endl;
        Edge finalEdge = BFS();
        if (!finalEdge.src) break;

        Edge currEdge = finalEdge;
        int minCap = 1000000000;
        while (true) {
            if (!currEdge.src) break;
            // cout << currEdge.src << " " << currEdge.tgt << endl;
            if (W[currEdge.src][currEdge.tgt] < minCap) {
                minCap = W[currEdge.src][currEdge.tgt];
            }
            currEdge = prevEdge[currEdge.src][currEdge.tgt];
        }
        // cout << "minCap " << minCap << endl;
        // update W
        currEdge = finalEdge;
        while (true) {
            if (!currEdge.src) break;
            W[currEdge.src][currEdge.tgt] -= minCap;
            W[currEdge.tgt][currEdge.src] += minCap;
            currEdge = prevEdge[currEdge.src][currEdge.tgt];
        }
        flow += minCap;
    }
    return flow;
}

int main() {
    fin >> N >> M;
    for (int i = 0; i < N; i++) {
        int src, tgt, flow;
        fin >> src >> tgt >> flow;
        W[src][tgt] += flow;
        adjList[src].push_back(Edge(src, tgt));
        adjList[tgt].push_back(Edge(tgt, src));
    }
    fout << findMaxFlow() << endl;

    return 0;
}

