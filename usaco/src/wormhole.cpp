/* Use the slash-star style comments or the system won't see your
   identification information */
/*
ID: yzylive1
TASK: wormhole
LANG: C++
*/
/* LANG can be C++20 or C++14 for those more recent releases */
#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include <cstring>
#include <set>
#include <string>

using namespace std;

long wormholes[12][2];

int visited[12];
int pairArray[12];
int nextArray[12];
int loopPairNum = 0;
int loopVisited[12];

void findNext(int N) {
    for (int i = 0; i < N; i++) {
        long minDis = -1;
        nextArray[i] = -1;
        for (int j = 0; j < N; j++) {
            if (i == j || wormholes[i][1] != wormholes[j][1] ||
                wormholes[i][0] >= wormholes[j][0]) {
                continue;
            }
            if (minDis == -1 || wormholes[j][0] - wormholes[i][0] < minDis) {
                nextArray[i] = j;
                minDis = wormholes[j][0] - wormholes[i][0];
            }
        }
    }
}

bool isLoopPair(int N) {
    // try all start points
    int currPos, targetPos;
    for (int i = 0; i < N; i++) {
        memset(loopVisited, 0, sizeof(loopVisited));
        currPos = i;
        loopVisited[currPos] = 1;
        while (true) {
            targetPos = pairArray[currPos];
            currPos = nextArray[targetPos];
            if (currPos == -1) break;
            if (loopVisited[currPos]) return true;
            loopVisited[currPos] = 1;
        }
    }
    return false;
}

void tryAllPairs(int N, int rest) {
    if (rest == N / 2) memset(visited, 0, sizeof(visited));
    int p1, p2;
    // find the smallest unvisited p1 and fix it
    // to ensure the uniqueness of pair array
    for (p1 = 0; p1 < N; p1++) {
        if (!visited[p1]) {
            visited[p1] = 1;
            break;
        }
    }

    for (p2 = p1 + 1; p2 < N; p2++) {
        if (!visited[p2]) {
            pairArray[p1] = p2;
            pairArray[p2] = p1;
            visited[p2] = 1;
            if (rest == 1) {
                if (isLoopPair(N)) {
                    loopPairNum++;
                }
            } else {
                tryAllPairs(N, rest - 1);
            }
            visited[p2] = 0;
        }
    }
    
    visited[p1] = 0;
}

int main() {
    ofstream fout ("wormhole.out");
    ifstream fin ("wormhole.in");

    int N;
    fin >> N;
    for (int i = 0; i < N; i++) {
        fin >> wormholes[i][0] >> wormholes[i][1];
        // cout << wormholes[i][0] << endl;
        // cout << wormholes[i][1] << endl;
    }

    findNext(N);
    // for (int i = 0; i < N; i++) {
    //     cout << nextArray[i] << " ";
    // }
    // cout << endl;
    tryAllPairs(N, N / 2);
    fout << loopPairNum << endl;

    return 0;
}

