/*
 * POJ 3083 - Children of the Candy Corn
 *
 */

#include <cstdio>
#include <cstdlib>
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

char maze[50][50];
int H, W;
pair<int, int> startPos, endPos, startDir;

bool isValidPos(pair<int, int> pos) {
    return pos.first >= 0 && pos.first < H &&
           pos.second >= 0 && pos.second < W &&
           maze[pos.first][pos.second] != '#';
}

pair<int, int> nextDir(pair<int, int> dir, bool alongLeftWall) {
    // -1,0 0,1 1,0 0,-1
    if (alongLeftWall && dir.second == 0) dir.first = -dir.first;
    // -1,0 0,-1 1,0 0,1
    else if (!alongLeftWall && dir.first == 0) dir.second = -dir.second;
    swap(dir.first, dir.second);
    return dir;
}

int walkAlongWall(bool alongLeftWall) {
    pair<int, int> pos = startPos, dir = startDir;
    int squares = 1;
    while (pos != endPos) {
        pair<int, int> lossWallDir;
        lossWallDir = nextDir(dir, !alongLeftWall);
        if (isValidPos(make_pair(pos.first + lossWallDir.first,
                                 pos.second + lossWallDir.second))) {
            dir = lossWallDir;
        } else {
            while (!isValidPos(make_pair(pos.first + dir.first,
                                         pos.second + dir.second))) {
                dir = nextDir(dir, alongLeftWall);
            }
        }
        pos = make_pair(pos.first + dir.first, pos.second + dir.second);
        squares += 1;
    }
    return squares;
}

int bfs() {
    queue<pair<pair<int, int>, int> > bfsQ;
    bfsQ.push(make_pair(startPos, 1));
    maze[startPos.first][startPos.second] = '#';
    while (!bfsQ.empty()) {
        pair<int, int> pos = bfsQ.front().first;
        int squares = bfsQ.front().second;
        bfsQ.pop();
        if (pos == endPos) return squares;
        pair<int, int> dir = startDir;
        for (int i = 0; i < 4; i++) {
            dir = nextDir(dir, true);
            if (isValidPos(make_pair(pos.first + dir.first,
                                     pos.second + dir.second))) {
                pair<int, int> newPos = make_pair(pos.first + dir.first,
                                                  pos.second + dir.second);
                maze[newPos.first][newPos.second] = '#';
                bfsQ.push(make_pair(newPos, squares + 1));
            }
        }
    } 
}

int main() {
    int caseNum;
    cin >> caseNum;
    for (int k = 0; k < caseNum; k++) {
        startDir.first = startDir.second = 0;
        cin >> W >> H;
        for (int i = 0; i < H; i++) {
            cin >> maze[i];
            for (int j = 0; j < W; j++) {
                if (maze[i][j] == 'S') {
                    startPos.first = i, startPos.second = j;
                    if (i == 0) startDir.first = 1;
                    else if (i == H - 1) startDir.first = -1;
                    else if (j == 0) startDir.second = 1;
                    else startDir.second = -1;
                } else if (maze[i][j] == 'E') {
                    endPos.first = i, endPos.second = j;
                }
            }
        }
        int leftDis = walkAlongWall(true);
        int rightDis = walkAlongWall(false);
        int bfsDis = bfs();
        cout << leftDis << " " << rightDis << " " << bfsDis << endl;
    }
    return 0;
}

