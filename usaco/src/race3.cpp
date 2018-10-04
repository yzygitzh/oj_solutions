/* Use the slash-star style comments or the system won't see your
   identification information */
/*
ID: yzylive1
TASK: race3
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

ifstream fin ("race3.in");
ofstream fout ("race3.out");

int N = 0;
class Edge {
public:
    int src, tgt;
    Edge(int _src, int _tgt): src(_src), tgt(_tgt) {}
};
vector<Edge> adjMat[60];
vector<Edge> revAdjMat[60];
int visited[60];
int edgeVisited[60][60];

set<int> vitalPoints;
void findVitalPoints() {
    for (int i = 1; i < N; i++) {
        bool isVitalPoint = true;
        memset(visited, 0, sizeof(visited));
        queue<int> bfsQ;
        bfsQ.push(0);
        visited[0] = 1;
        while (!bfsQ.empty()) {
            int currPoint = bfsQ.front();
            bfsQ.pop();
            if (currPoint == N) isVitalPoint = false;
            for (vector<Edge>::iterator itr = adjMat[currPoint].begin();
                 itr != adjMat[currPoint].end(); ++itr) {
                if (itr->tgt != i && !visited[itr->tgt]) {
                    visited[itr->tgt] = 1;
                    bfsQ.push(itr->tgt);
                }
            }
        }
        if (isVitalPoint) vitalPoints.insert(i);
    }
}

set<int> splitPoints;
void findSplitPoints() {
    for (set<int>::iterator itr1 = vitalPoints.begin();
         itr1 != vitalPoints.end(); ++itr1) {
        queue<int> bfsQ;

        memset(edgeVisited, 0, sizeof(edgeVisited));

        set<int> phase1FromStart;
        memset(visited, 0, sizeof(visited));
        bfsQ.push(0); phase1FromStart.insert(0); visited[0] = 1;
        while (!bfsQ.empty()) {
            int p = bfsQ.front(); bfsQ.pop();
            for (vector<Edge>::iterator itr2 = adjMat[p].begin();
                 itr2 != adjMat[p].end(); ++itr2) {
                if (itr2->src != *itr1) {
                    edgeVisited[itr2->src][itr2->tgt] = 1;
                    if (!visited[itr2->tgt]) {
                        bfsQ.push(itr2->tgt); phase1FromStart.insert(itr2->tgt); visited[itr2->tgt] = 1;
                    }
                }
            }
        }

        set<int> phase1FromEnd;
        memset(visited, 0, sizeof(visited));
        bfsQ.push(*itr1); phase1FromEnd.insert(*itr1); visited[*itr1] = 1;
        while (!bfsQ.empty()) {
            int p = bfsQ.front(); bfsQ.pop();
            for (vector<Edge>::iterator itr2 = revAdjMat[p].begin();
                 itr2 != revAdjMat[p].end(); ++itr2) {
                if (itr2->tgt != *itr1 && !visited[itr2->tgt] &&
                    edgeVisited[itr2->tgt][itr2->src]) {
                    bfsQ.push(itr2->tgt); phase1FromEnd.insert(itr2->tgt); visited[itr2->tgt] = 1;
                }
            }
        }

        set<int> phase1Bi;
        memset(visited, 0, sizeof(visited));
        bfsQ.push(0); phase1Bi.insert(0); visited[0] = 1;
        while (!bfsQ.empty()) {
            int p = bfsQ.front(); bfsQ.pop();
            for (vector<Edge>::iterator itr2 = adjMat[p].begin();
                 itr2 != adjMat[p].end(); ++itr2) {
                if (itr2->src != *itr1 && !visited[itr2->tgt]) {
                    bfsQ.push(itr2->tgt); phase1Bi.insert(itr2->tgt); visited[itr2->tgt] = 1;
                }
            }
            for (vector<Edge>::iterator itr2 = revAdjMat[p].begin();
                 itr2 != revAdjMat[p].end(); ++itr2) {
                if (itr2->tgt != *itr1 && !visited[itr2->tgt] &&
                    edgeVisited[itr2->tgt][itr2->src]) {
                    bfsQ.push(itr2->tgt); phase1Bi.insert(itr2->tgt); visited[itr2->tgt] = 1;
                }
            }
        }

        memset(edgeVisited, 0, sizeof(edgeVisited));

        set<int> phase2FromStart;
        memset(visited, 0, sizeof(visited));
        bfsQ.push(*itr1); phase2FromStart.insert(*itr1); visited[*itr1] = 1;
        while (!bfsQ.empty()) {
            int p = bfsQ.front(); bfsQ.pop();
            for (vector<Edge>::iterator itr2 = adjMat[p].begin();
                 itr2 != adjMat[p].end(); ++itr2) {
                if (itr2->tgt != *itr1) {
                    edgeVisited[itr2->src][itr2->tgt] = 1;
                    if (!visited[itr2->tgt]) {
                        bfsQ.push(itr2->tgt); phase2FromStart.insert(itr2->tgt); visited[itr2->tgt] = 1;
                    }
                }
            }
        }

        set<int> phase2FromEnd;
        memset(visited, 0, sizeof(visited));
        bfsQ.push(N); phase2FromEnd.insert(N); visited[N] = 1;
        while (!bfsQ.empty()) {
            int p = bfsQ.front(); bfsQ.pop();
            for (vector<Edge>::iterator itr2 = revAdjMat[p].begin();
                 itr2 != revAdjMat[p].end(); ++itr2) {
                if (itr2->src != *itr1 && !visited[itr2->tgt] &&
                    edgeVisited[itr2->tgt][itr2->src]) {
                    bfsQ.push(itr2->tgt); phase2FromEnd.insert(itr2->tgt); visited[itr2->tgt] = 1;
                }
            }
        }

        set<int> phase2Bi;
        memset(visited, 0, sizeof(visited));
        bfsQ.push(*itr1); phase2Bi.insert(*itr1); visited[*itr1] = 1;
        while (!bfsQ.empty()) {
            int p = bfsQ.front(); bfsQ.pop();
            for (vector<Edge>::iterator itr2 = adjMat[p].begin();
                 itr2 != adjMat[p].end(); ++itr2) {
                if (itr2->tgt != *itr1 && !visited[itr2->tgt]) {
                    bfsQ.push(itr2->tgt); phase2Bi.insert(itr2->tgt); visited[itr2->tgt] = 1;
                }
            }
            for (vector<Edge>::iterator itr2 = revAdjMat[p].begin();
                 itr2 != revAdjMat[p].end(); ++itr2) {
                if (itr2->src != *itr1 && !visited[itr2->tgt] &&
                    edgeVisited[itr2->tgt][itr2->src]) {
                    bfsQ.push(itr2->tgt); phase2Bi.insert(itr2->tgt); visited[itr2->tgt] = 1;
                }
            }
        }

        set<int> intersect;
        set_intersection(phase1Bi.begin(), phase1Bi.end(),
                         phase2Bi.begin(), phase2Bi.end(),
                         inserter(intersect, intersect.begin()));
        if (phase1FromStart == phase1FromEnd && phase1FromEnd == phase1Bi &&
            phase2FromStart == phase2FromEnd && phase2FromEnd == phase2Bi &&
            phase1Bi.size() + phase2Bi.size() == N + 2 &&
            intersect.size() == 1) {
            splitPoints.insert(*itr1);
        }
    }
}

int main() {
    while (true) {
        int inputNum;
        fin >> inputNum;
        if (inputNum == -1) break;
        else if (inputNum == -2) N++;
        else {
            adjMat[N].push_back(Edge(N, inputNum));
            revAdjMat[inputNum].push_back(Edge(inputNum, N));
        }
    }
    N--;
    findVitalPoints();
    fout << vitalPoints.size();
    for (set<int>::iterator itr = vitalPoints.begin();
         itr != vitalPoints.end(); ++itr) {
        fout << " " << *itr;
    }
    fout << endl;
    findSplitPoints();
    fout << splitPoints.size();
    for (set<int>::iterator itr = splitPoints.begin();
         itr != splitPoints.end(); ++itr) {
        fout << " " << *itr;
    }
    fout << endl;
    return 0;
}

