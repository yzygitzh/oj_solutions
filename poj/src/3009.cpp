/*
 * POJ 3009 - Curling 2.0
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

int W, H;
int maze[30][30];
int visited[30][30][4];
pair<int, int> startPos, endPos;
vector<pair<int, int> > dirs(4);
int minSteps;

void initDirs() {
    for (int i = 0; i < 4; i++) {
        dirs[i].first = dirs[i].second = 0;
    }
    dirs[0].first = -1;
    dirs[1].second = 1;
    dirs[2].first = 1;
    dirs[3].second = -1;
}

bool isValidPos(pair<int, int> pos) {
    return pos.first >= 0 && pos.first < H &&
           pos.second >= 0 && pos.second < W &&
           maze[pos.first][pos.second] != 1;
}

void dfs(int rest, pair<int, int> currPos) {
    if (10 - rest >= minSteps) {
        return;
    }
    if (currPos == endPos) {
        minSteps = 10 - rest;
        return;
    }

    for (int i = 0; i < 4; i++) {
        // throw stones into 4 dirs
        pair<int, int> pos = currPos;
        while (isValidPos(make_pair(pos.first + dirs[i].first,
                                    pos.second + dirs[i].second))) {
            pos = make_pair(pos.first + dirs[i].first,
                            pos.second + dirs[i].second);
            if (pos == endPos) {
                minSteps = 10 - rest + 1;
                return;
            }
        }
        if (pos == currPos ||
            pos.first + dirs[i].first < 0 ||
            pos.first + dirs[i].first >= H ||
            pos.second + dirs[i].second < 0 ||
            pos.second + dirs[i].second >= W) continue;

        pair<int, int> brickPos = make_pair(pos.first + dirs[i].first,
                                            pos.second + dirs[i].second);
        if (!visited[pos.first][pos.second][i]) {
            visited[pos.first][pos.second][i] = 1;
            maze[brickPos.first][brickPos.second] = 0;
            dfs(rest - 1, pos);
            maze[brickPos.first][brickPos.second] = 1;
            visited[pos.first][pos.second][i] = 0;
        }
    }
}

int main() {
    initDirs();
    while (true) {
        cin >> W >> H;
        if (W == 0 && H == 0) break;
        for (int i = 0; i < H; i++) {
            for (int j = 0; j < W; j++) {
                cin >> maze[i][j];
                if (maze[i][j] == 2) startPos.first = i, startPos.second = j;
                if (maze[i][j] == 3) endPos.first = i, endPos.second = j;
            }
        }
        minSteps = 11;
        memset(visited, 0, sizeof(visited));
        dfs(10, startPos);
        if (minSteps <= 10) cout << minSteps << endl;
        else cout << -1 << endl;
    }
    return 0;
}

