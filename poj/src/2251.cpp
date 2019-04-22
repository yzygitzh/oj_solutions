/*
 * POJ 2251 - Dungeon Master
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

int L, R, C;
char maze[50][50][50];
int visited[50][50][50];

class MazeState {
public:
    int l, r, c, step;
    MazeState() {}
    MazeState(int _l, int _r, int _c, int _step)
        :l(_l), r(_r), c(_c), step(_step) {}
};
MazeState startState, endState;

bool isEqualPos(const MazeState& s1, const MazeState& s2) {
    return s1.l == s2.l && s1.r == s2.r && s1.c == s2.c;
}

int bfs() {
    queue<MazeState> bfsQ;
    bfsQ.push(startState);
    visited[startState.l][startState.r][startState.c] = 1;
    while (!bfsQ.empty()) {
        MazeState s = bfsQ.front();
        bfsQ.pop();
        if (isEqualPos(s, endState)) return s.step;
        // try six directions
        if (s.l - 1 >= 0 && maze[s.l - 1][s.r][s.c] != '#' && !visited[s.l - 1][s.r][s.c]) {
            bfsQ.push(MazeState(s.l - 1, s.r, s.c, s.step + 1));
            visited[s.l - 1][s.r][s.c] = 1;
        }
        if (s.l + 1 < L && maze[s.l + 1][s.r][s.c] != '#' && !visited[s.l + 1][s.r][s.c]) {
            bfsQ.push(MazeState(s.l + 1, s.r, s.c, s.step + 1));
            visited[s.l + 1][s.r][s.c] = 1;
        }
        if (s.r - 1 >= 0 && maze[s.l][s.r - 1][s.c] != '#' && !visited[s.l][s.r - 1][s.c]) {
            bfsQ.push(MazeState(s.l, s.r - 1, s.c, s.step + 1));
            visited[s.l][s.r - 1][s.c] = 1;
        }
        if (s.r + 1 < R && maze[s.l][s.r + 1][s.c] != '#' && !visited[s.l][s.r + 1][s.c]) {
            bfsQ.push(MazeState(s.l, s.r + 1, s.c, s.step + 1));
            visited[s.l][s.r + 1][s.c] = 1;
        }
        if (s.c - 1 >= 0 && maze[s.l][s.r][s.c - 1] != '#' && !visited[s.l][s.r][s.c - 1]) {
            bfsQ.push(MazeState(s.l, s.r, s.c - 1, s.step + 1));
            visited[s.l][s.r][s.c - 1] = 1;
        }
        if (s.c + 1 < C && maze[s.l][s.r][s.c + 1] != '#' && !visited[s.l][s.r][s.c + 1]) {
            bfsQ.push(MazeState(s.l, s.r, s.c + 1, s.step + 1));
            visited[s.l][s.r][s.c + 1] = 1;
        }
    }
    return -1;
}

int main() {
    while (true) {
        cin >> L >> R >> C;
        if (L == 0 && R == 0 && C == 0) break;
        for (int i = 0; i < L; i++) {
            for (int j = 0; j < R; j++) {
                cin >> maze[i][j];
                for (int k = 0; k < C; k++) {
                    if (maze[i][j][k] == 'S') {
                        startState = MazeState(i, j, k, 0);
                    } else if (maze[i][j][k] == 'E') {
                        endState = MazeState(i, j, k, 0);
                    }
                }
            }
        }
        memset(visited, 0, sizeof(visited));
        int steps = bfs();
        if (steps < 0) {
            cout << "Trapped!" << endl;
        } else {
            cout << "Escaped in " << steps << " minute(s)." << endl;
        }
    }
    return 0;
}

