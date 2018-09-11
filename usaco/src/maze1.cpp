/* Use the slash-star style comments or the system won't see your
   identification information */
/*
ID: yzylive1
TASK: maze1
LANG: C++
*/
/* LANG can be C++20 or C++14 for those more recent releases */
#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include <cstring>
#include <queue>
#include <set>
#include <string>
#include <map>

using namespace std;

/*
 * Be careful to set visited array immediately after push
 * element in BFS...
 */

ifstream fin ("maze1.in");
ofstream fout ("maze1.out");

int W, H;
char maze[210][80];
int step[2][210][80];

class Pos {
public:
    int h, w, step;
    Pos(int _h, int _w, int _step): h(_h), w(_w), step(_step) {}
    Pos(){}
};

queue<Pos> bfsQ;

void BFS(Pos startPos, int stepIdx) {
    static int count = 0;
    bfsQ.push(startPos);
    step[stepIdx][startPos.h][startPos.w] = startPos.step;
    while (!bfsQ.empty()) {
        Pos p = bfsQ.front();
        bfsQ.pop();
        // cout << p.h << " " << p.w << " " << p.step << endl;
        if (p.h - 2 >= 0 && maze[p.h - 1][p.w] == ' ' && step[stepIdx][p.h - 2][p.w] < 0) {
            bfsQ.push(Pos(p.h - 2, p.w, p.step + 1));
            step[stepIdx][p.h - 2][p.w] = p.step + 1;
        }
        if (p.h + 2 < 2 * H + 1 && maze[p.h + 1][p.w] == ' ' && step[stepIdx][p.h + 2][p.w] < 0) {
            bfsQ.push(Pos(p.h + 2, p.w, p.step + 1));
            step[stepIdx][p.h + 2][p.w] = p.step + 1;
        }
        if (p.w - 2 >= 0 && maze[p.h][p.w - 1] == ' ' && step[stepIdx][p.h][p.w - 2] < 0) {
            bfsQ.push(Pos(p.h, p.w - 2, p.step + 1));
            step[stepIdx][p.h][p.w - 2] = p.step + 1;
        }
        if (p.w + 2 < 2 * W + 1 && maze[p.h][p.w + 1] == ' ' && step[stepIdx][p.h][p.w + 2] < 0) {
            bfsQ.push(Pos(p.h, p.w + 2, p.step + 1));
            step[stepIdx][p.h][p.w + 2] = p.step + 1;
        }
    }
}

int main() {
    fin >> W >> H;

    string mazeLine;
    getline(fin, mazeLine);
    for (int i = 0; i < 2 * H + 1; i++) {
        getline(fin, mazeLine);
        memcpy(maze[i], mazeLine.c_str(), 2 * W + 1);
        for (int j = 0; j < 2 * W + 1; j++) {
            step[0][i][j] = -1;
            step[1][i][j] = -1;
        }
    }

    // find two exits
    Pos exits[2];
    int exitCount = 0;
    // find in left and right edge
    for (int i = 0; i < 2 * H + 1; i++) {
        if (maze[i][0] == ' ') {
            exits[exitCount] = Pos(i, 1, 0);
            exitCount++;
        }
        if (maze[i][2 * W] == ' ') {
            exits[exitCount] = Pos(i, 2 * W - 1, 0);
            exitCount++;
        }
    }
    // find in up and down edge 
    for (int i = 0; i < 2 * W + 1; i++) {
        if (maze[0][i] == ' ') {
            exits[exitCount] = Pos(1, i, 0);
            exitCount++;
        }
        if (maze[2 * H][i] == ' ') {
            exits[exitCount] = Pos(2 * H - 1, i, 0);
            exitCount++;
        }
    }

    BFS(exits[0], 0);
    BFS(exits[1], 1);

    int maxStep = step[0][1][1] < step[1][1][1] ? step[0][1][1] : step[1][1][1];
    for (int i = 0; i < 2 * H + 1; i++) {
        for (int j = 0; j < 2 * W + 1; j++) {
            if (step[0][i][j] < 0) continue;
            // cout << i << " " << j << " " << step[0][i][j] << " " << step[1][i][j] << endl;
            int minStep = step[0][i][j] < step[1][i][j] ? step[0][i][j] : step[1][i][j];
            if (maxStep < minStep) maxStep = minStep;
        }
    }

    fout << maxStep + 1 << endl;

    return 0;
}

