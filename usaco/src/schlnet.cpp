/* Use the slash-star style comments or the system won't see your
   identification information */
/*
ID: yzylive1
TASK: schlnet
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

ifstream fin ("schlnet.in");
ofstream fout ("schlnet.out");

int N;
vector<int> adjMat[110];
vector<int> newAdjMat[110];

int newNode[110];

int tLow[110] = {0};
int tDfn[110] = {0};
int tInStack[110] = {0};
int tIdx = 0;
int tStack[110] = {0};
int tSIdx = 0;
vector<vector<int> > scrs;

void tarjan(int node) {
    // cout << "T " << node << endl;
    tDfn[node] = tLow[node] = ++tIdx;
    tStack[tSIdx++] = node;
    tInStack[node] = 1;
    for (vector<int>::iterator itr = adjMat[node].begin();
         itr != adjMat[node].end(); ++itr) {
        if (tDfn[*itr] == 0) {
            tarjan(*itr);
            if (tLow[node] > tLow[*itr]) tLow[node] = tLow[*itr];
        } else if (tInStack[*itr]) {
            if (tLow[node] > tDfn[*itr]) tLow[node] = tDfn[*itr];
        }
    }

    // cout << "TEQUAL " << node << " " << tDfn[node] << " " << tLow[node] << endl;
    if (tDfn[node] == tLow[node]) {
        // cout << "TNode " << node << endl;
        vector<int> scr;
        while (true) {
            int top = tStack[--tSIdx];
            scr.push_back(top);
            tInStack[top] = 0;
            // cout << " " << top << endl;
            if (top == node) break;
        }
        // cout << endl;
        sort(scr.begin(), scr.end());
        for (vector<int>::iterator itr = scr.begin();
             itr != scr.end(); ++itr) {
            newNode[*itr] = scr[0];
        }
        scrs.push_back(scr);
    }
}

void compressG() {
    for (int i = 1; i <= N; i++) {
        for (vector<int>::iterator itr = adjMat[i].begin();
             itr != adjMat[i].end(); ++itr) {
            // cout << "G " << i << " " << *itr << " " << newNode[*itr] << endl;
            if (newNode[i] != newNode[*itr]) {
                newAdjMat[newNode[i]].push_back(newNode[*itr]);
            }
        }
    }
    for (int i = 1; i <= N; i++) {
        sort(newAdjMat[i].begin(), newAdjMat[i].end());
        unique(newAdjMat[i].begin(), newAdjMat[i].end());
    }
}

int computeSrcNum() {
    set<int> nonSrc;
    for (int i = 1; i <= N; i++) {
        for (vector<int>::iterator itr = newAdjMat[i].begin();
             itr != newAdjMat[i].end(); ++itr) {
            // cout << i << " " << *itr << endl;
            nonSrc.insert(*itr);
        }
    }
    return scrs.size() - nonSrc.size();
}

int computeSinkNum() {
    set<int> nonSink;
    for (int i = 1; i <= N; i++) {
        if (newAdjMat[i].size()) nonSink.insert(i);
    }
    return scrs.size() - nonSink.size();
}

int main() {
    fin >> N;
    for (int i = 1; i <= N; i++) {
        while (true) {
            int tgt;
            fin >> tgt;
            if (!tgt) break;
            if (i != tgt) adjMat[i].push_back(tgt);
        }
    }
    for (int i = 1; i <= N; i++) {
        if (!tDfn[i]) tarjan(i);
        // cout << "tSIdx " << tSIdx << endl;
    }
    sort(scrs.begin(), scrs.end());
    compressG();

    int srcNum = computeSrcNum();
    int sinkNum = computeSinkNum();
    fout << srcNum << endl;
    if (scrs.size() == 1) {
        fout << 0 << endl;
    } else {
        fout << (srcNum > sinkNum ? srcNum : sinkNum) << endl;
    }

    return 0;
}
