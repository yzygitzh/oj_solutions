/* Use the slash-star style comments or the system won't see your
   identification information */
/*
ID: yzylive1
TASK: telecow
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
#include <utility>

#pragma pack(1)
using namespace std;

/*
 * Must use BFS in Edmond-Karp!
 */

ifstream fin ("telecow.in");
ofstream fout ("telecow.out");

int N, M;
int c1, c2;
vector<int> adjMat[210];
int originW[210][210] = {0};
int W[210][210] = {0};
int visited[210];
int prevNode[210];

bool BFS() {
    queue<vector<int> > bfsQ;
    memset(prevNode, 0, sizeof(prevNode));
    memset(visited, 0, sizeof(visited));

    vector<int> initElem;
    initElem.push_back(c1);
    bfsQ.push(initElem);
    visited[c1] = 1;

    while (!bfsQ.empty()) {
        vector<int> top = bfsQ.front();
        bfsQ.pop();
        if (*top.rbegin() == c2) {
            for (vector<int>::iterator itr = top.begin();
                 itr + 1 != top.end(); ++itr) {
                prevNode[*(itr + 1)] = *itr;
            }
            return true;
        } 
        for (vector<int>::iterator itr = adjMat[*top.rbegin()].begin();
             itr != adjMat[*top.rbegin()].end(); ++itr) {
            if (!visited[*itr] && W[*top.rbegin()][*itr]) {
                visited[*itr] = 1;
                vector<int> newElem = top;
                newElem.push_back(*itr);
                bfsQ.push(newElem);
            }
        }
    }
    return false;
}

int maxFlow() {
    memcpy(W, originW, sizeof(W));
    int flow = 0;
    while (BFS()) {
        int node = c2;
        // cout << "Path Start" << endl;
        while (node) {
            // if (node % 2 == 0) cout << "Path " << node / 2 << endl;
            W[node][prevNode[node]] += 1;
            W[prevNode[node]][node] -= 1;
            node = prevNode[node];
        }
        flow += 1;
    }
    return flow;
}

int main() {
    fin >> N >> M >> c1 >> c2;

    // split node i into node 2i-1 and node 2i
    for (int i = 1; i <= N; i++) {
        adjMat[2 * i - 1].push_back(2 * i);
        if (i == c1 || i == c2) {
            W[2 * i - 1][2 * i] = 1000000000;
        } else {
            W[2 * i - 1][2 * i] = 1;
        }
    }
    c1 = 2 * c1 - 1;
    c2 = 2 * c2;

    for (int i = 0; i < M; i++) {
        int tc1, tc2;
        fin >> tc1 >> tc2;
        adjMat[2 * tc1].push_back(2 * tc2 - 1);
        adjMat[2 * tc2].push_back(2 * tc1 - 1);
        W[2 * tc1][2 * tc2 - 1] = W[2 * tc2][2 * tc1 - 1] = 1000000000;
    }
    memcpy(originW, W, sizeof(W));

    vector<int> minCut;
    int initFlow = maxFlow();
    // cout << "F " << initFlow << endl;
    while (initFlow) {
        // try some edge
        for (int i = 1; i <= N; i++) {
            if (2 * i - 1 == c1 || 2 * i == c2) continue;
            if (originW[2 * i - 1][2 * i]) {
                // cout << "TRY " << i << endl;
                originW[2 * i - 1][2 * i] = 0;
                int newFlow = maxFlow();
                // cout << "F " << newFlow << endl;
                if (newFlow < initFlow) {
                    initFlow = newFlow;
                    minCut.push_back(i);
                    break;
                } else {
                    originW[2 * i - 1][2 * i] = 1;
                }
            }
        }
    }

    fout << minCut.size() << endl;
    for (vector<int>::iterator itr = minCut.begin();
         itr != minCut.end(); ++itr) {
        fout << *itr;
        if (itr + 1 == minCut.end()) fout << endl;
        else fout << " ";
    }
    return 0;
}
