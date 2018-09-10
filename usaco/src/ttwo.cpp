/* Use the slash-star style comments or the system won't see your
   identification information */
/*
ID: yzylive1
TASK: ttwo
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

ifstream fin ("ttwo.in");
ofstream fout ("ttwo.out");

char farm[10][10];
int visited[10][10][4];

class Pos {
public:
    // dir: 0-N, 1-E, 2-S, 3-W
    int x, y, dir;
    Pos() {}
    Pos(int _x, int _y, int _dir): x(_x), y(_y), dir(_dir) {}
    bool operator==(const Pos &p) {
        return x == p.x && y == p.y && dir == p.dir;
    }
    bool operator!=(const Pos &p) {
        return !(*this == p);
    }
};

Pos nextStep(Pos currPos) {
    // cout << currPos.x << " " << currPos.y << " " << currPos.dir << endl;
    if (currPos.dir == 0 && currPos.x - 1 >= 0 && farm[currPos.x - 1][currPos.y] != '*') {
        return Pos(currPos.x - 1, currPos.y, currPos.dir);
    } else if (currPos.dir == 1 && currPos.y + 1 < 10 && farm[currPos.x][currPos.y + 1] != '*') {
        return Pos(currPos.x, currPos.y + 1, currPos.dir);
    } else if (currPos.dir == 2 && currPos.x + 1 < 10 && farm[currPos.x + 1][currPos.y] != '*') {
        return Pos(currPos.x + 1, currPos.y, currPos.dir);
    } else if (currPos.dir == 3 && currPos.y - 1 >= 0 && farm[currPos.x][currPos.y - 1] != '*') {
        return Pos(currPos.x, currPos.y - 1, currPos.dir);
    } else {
        return Pos(currPos.x, currPos.y, (currPos.dir + 1) % 4);
    }
}

int main() {
    vector<Pos> fCyc, cCyc;
    Pos fPos, cPos;
    Pos initFPos, initCPos, rFPos, rCPos;
    string tmpInput;
    int cycCount;

    for (int i = 0; i < 10; i++) {
        fin >> tmpInput;
        memcpy(farm[i], tmpInput.c_str(), 10);
        for (int j = 0; j < 10; j++) {
            if (farm[i][j] == 'F') {
                fPos = Pos(i, j, 0);
                initFPos = fPos;
            }
            else if (farm[i][j] == 'C') {
                cPos = Pos(i, j, 0);
                initCPos = cPos;
            }
        }
    }

    // build farmer cycle
    for (int i = 0; i < 10; i++) {
        for (int j = 0; j < 10; j++) {
            for (int k = 0; k < 4; k++) {
                visited[i][j][k] = 0;
            }
        }
    }
    cycCount = 1;
    while (!visited[fPos.x][fPos.y][fPos.dir]) {
        // cout << fPos.x << " " << fPos.y << " " << fPos.dir << endl;
        visited[fPos.x][fPos.y][fPos.dir] = cycCount++;
        fCyc.push_back(fPos);
        fPos = nextStep(fPos);
        // cout << fCyc[0].x << " " << fCyc[0].y << " " << fCyc[0].dir << endl;
    }
    int fOffset = visited[fPos.x][fPos.y][fPos.dir] - 1;
    // cout << fOffset << endl;
    
    // build cow cycle
    for (int i = 0; i < 10; i++) {
        for (int j = 0; j < 10; j++) {
            for (int k = 0; k < 4; k++) {
                visited[i][j][k] = 0;
            }
        }
    }
    cycCount = 1;
    while (!visited[cPos.x][cPos.y][cPos.dir]) {
        // cout << cPos.x << " " << cPos.y << " " << cPos.dir << endl;
        visited[cPos.x][cPos.y][cPos.dir] = cycCount++;
        cCyc.push_back(cPos);
        cPos = nextStep(cPos);
    }
    int cOffset = visited[cPos.x][cPos.y][cPos.dir] - 1;

    int maxOffset = fOffset > cOffset ? fOffset : cOffset;
    rFPos = fCyc[((maxOffset - fOffset) % (fCyc.size() - fOffset)) + fOffset];
    rCPos = cCyc[((maxOffset - cOffset) % (cCyc.size() - cOffset)) + cOffset];
    // cout << "rCPos " << rCPos.x << " " << rCPos.y << " " << rCPos.dir << endl;
    
    int steps = 0;
    fPos = initFPos;
    cPos = initCPos;
    int encounter = 0;
    do {
        steps++;
        // cout << steps << endl;
        // cout << "fPos " << fPos.x << " " << fPos.y << " " << fPos.dir << endl;
        // cout << "cPos " << cPos.x << " " << cPos.y << " " << cPos.dir << endl;
        fPos = nextStep(fPos);
        cPos = nextStep(cPos);
        if (fPos == rFPos && cPos == rCPos) encounter++;
    } while (!(fPos.x == cPos.x && fPos.y == cPos.y) &&
             !(fPos == rFPos && cPos == rCPos && encounter > 1));

    if (fPos.x == cPos.x && fPos.y == cPos.y) {
        fout << steps << endl;
    } else {
        fout << 0 << endl;
    }

    return 0;
}

