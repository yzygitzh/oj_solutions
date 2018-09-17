/* Use the slash-star style comments or the system won't see your
   identification information */
/*
ID: yzylive1
TASK: fence
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

ifstream fin ("fence.in");
ofstream fout ("fence.out");

/*
 * Finding Eulerian path is not the same as DFS...
 */

int F;
int adjMat[510][510] = {0};
int visited[510][510] = {0};
int degree[510] = {0};
int result[510];
int resultIdx = 0;
bool found = false;

void DFS(int currNode) {
    if (resultIdx == F) return;
    for (int i = 1; i <= 500; i++) {
        if (adjMat[currNode][i]) {
            if (visited[currNode][i] < adjMat[currNode][i]) {
                visited[currNode][i] += 1;
                visited[i][currNode] += 1;
                DFS(i);
                if (resultIdx == F) return;
            }
        }
    }
    result[resultIdx++] = currNode;
    // cout << resultIdx - 1 << " " << currNode << endl;
}

int main() {
    fin >> F;
    for (int i = 0; i < F; i++) {
        int src, tgt;
        fin >> src >> tgt;
        adjMat[src][tgt] += 1;
        adjMat[tgt][src] += 1;
        degree[src]++;
        degree[tgt]++;
    }
    // find start node
    int startNode = 0;
    int backupNode = 0;
    for (int i = 1; i <= 500; i++) {
        if (degree[i] % 2) {
            startNode = i;
            break;
        }
        if (!backupNode && degree[i]) backupNode = i;
    }
    if (!startNode) startNode = backupNode; 
    DFS(startNode);

    fout << startNode << endl;
    for (int i = F - 1; i >= 0; i--) {
        fout << result[i] << endl;
    }
    return 0;
}

