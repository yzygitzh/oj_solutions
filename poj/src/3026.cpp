/*
 * POJ 3026 - Borg Maze
 *
 * STL queue is too slow, use array for BFS.
 */

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

int row, col;
int nodeNum;
map<pair<int, int>, int> posToId;
vector<pair<int, int> > idToPos;
char maze[60][60];
int mVisited[60][60];
int G[110][110];
int GVisited[110];
int minDis[110];
int bfsQ[3000][3];

int main() {
    int caseNum;
    cin >> caseNum;
    while (caseNum--) {
        nodeNum = 0;
        posToId.clear();
        idToPos.clear();

        string inputLine;
        cin >> col >> row;
        getline(cin, inputLine);
        for (int i = 0; i < row; i++) {
            getline(cin, inputLine);
            memcpy(maze[i], inputLine.c_str(), col);
            for (int j = 0; j < col; j++) {
                if (maze[i][j] == 'A' || maze[i][j] == 'S') {
                    posToId[make_pair(i, j)] = nodeNum;
                    idToPos.push_back(make_pair(i, j));
                    nodeNum++;
                }
            }
        }

        // bfs on maze, fill G
        for (int i = 0; i < nodeNum; i++) {
            GVisited[i] = 0;
            minDis[i] = ~(1 << 31);
            int qL = 0, qR = 0;
            for (int j = 0; j < row; j++) {
                for (int k = 0; k < col; k++) {
                    mVisited[j][k] = 0;
                }
            }
            bfsQ[qR][0] = idToPos[i].first, bfsQ[qR][1] = idToPos[i].second, bfsQ[qR][2] = 0;
            qR++;
            mVisited[idToPos[i].first][idToPos[i].second] = 1;
            while (qL != qR) {
                int *p = bfsQ[qL];
                qL++;
                if (posToId.count(make_pair(p[0], p[1]))) {
                    G[i][posToId[make_pair(p[0], p[1])]] = p[2];
                }
                if (p[0] - 1 >= 0 && !mVisited[p[0] - 1][p[1]] && maze[p[0] - 1][p[1]] != '#') {
                    mVisited[p[0] - 1][p[1]] = 1;
                    bfsQ[qR][0] = p[0] - 1, bfsQ[qR][1] = p[1], bfsQ[qR][2] = p[2] + 1;
                    qR++;
                }
                if (p[0] + 1 < row && !mVisited[p[0] + 1][p[1]] && maze[p[0] + 1][p[1]] != '#') {
                    mVisited[p[0] + 1][p[1]] = 1;
                    bfsQ[qR][0] = p[0] + 1, bfsQ[qR][1] = p[1], bfsQ[qR][2] = p[2] + 1;
                    qR++;
                }
                if (p[1] - 1 >= 0 && !mVisited[p[0]][p[1] - 1] && maze[p[0]][p[1] - 1] != '#') {
                    mVisited[p[0]][p[1] - 1] = 1;
                    bfsQ[qR][0] = p[0], bfsQ[qR][1] = p[1] - 1, bfsQ[qR][2] = p[2] + 1;
                    qR++;
                }
                if (p[1] + 1 < col && !mVisited[p[0]][p[1] + 1] && maze[p[0]][p[1] + 1] != '#') {
                    mVisited[p[0]][p[1] + 1] = 1;
                    bfsQ[qR][0] = p[0], bfsQ[qR][1] = p[1] + 1, bfsQ[qR][2] = p[2] + 1;
                    qR++;
                }
            }
        }

        // prim
        minDis[0] = 0;
        int treeCost = 0;
        for (int i = 0; i < nodeNum; i++) {
            // find min node
            int currMinDis = ~(1 << 31), minNode;
            for (int j = 0; j < nodeNum; j++) {
                if (!GVisited[j] && minDis[j] < currMinDis) {
                    currMinDis = minDis[j];
                    minNode = j;
                }
            }
            GVisited[minNode] = 1;
            treeCost += currMinDis;
            // update minDis
            for (int j = 0; j < nodeNum; j++) {
                minDis[j] = min(minDis[j], G[minNode][j]);
            }
        }
        cout << treeCost << endl;
    }
    return 0;
}

