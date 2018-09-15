/* Use the slash-star style comments or the system won't see your
   identification information */
/*
ID: yzylive1
TASK: spin
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

ifstream fin ("spin.in");
ofstream fout ("spin.out");

/*
 * Each wheel somes to initial state every 360 seconds
 * So just check for 360 seconds
 */

int speed[5];
int wedgeNum[5];
int wedges[5][5][2];
int checkBuf[360];

void move() {
    for (int i = 0; i < 5; i++) {
        for (int j = 0; j < wedgeNum[i]; j++) {
            wedges[i][j][0] = (wedges[i][j][0] + speed[i]) % 360;
            wedges[i][j][1] = (wedges[i][j][1] + speed[i]) % 360;
        }
    }
}

bool checkValid() {
    memset(checkBuf, 0, sizeof(checkBuf));
    for (int i = 0; i < 5; i++) {
        for (int j = 0; j < wedgeNum[i]; j++) {
            // cout << wedges[i][j][0] << " " << wedges[i][j][1] << endl;
            for (int k = wedges[i][j][0]; k != wedges[i][j][1]; k = (k + 1) % 360) {
                checkBuf[k]++;
                // if (k == 185) cout << i << " " << j << " " << checkBuf[k] << endl;
            }
            checkBuf[wedges[i][j][1]]++;
        }
    }
    for (int i = 0; i < 360; i++) {
        if (checkBuf[i] == 5) return true;
    }
    return false;
}

int main() {
    for (int i = 0; i < 5; i++) {
        fin >> speed[i] >> wedgeNum[i];
        for (int j = 0; j < wedgeNum[i]; j++) {
            fin >> wedges[i][j][0] >> wedges[i][j][1];
            wedges[i][j][1] += wedges[i][j][0];
            wedges[i][j][1] %= 360;
            // cout << wedges[i][j][0] << " " << wedges[i][j][1] << endl;
        }
    }

    for (int i = 0; i < 360; i++) {
        if (checkValid()) {
            fout << i << endl;
            return 0;
        }
        move();
    }
    fout << "none" << endl;

    return 0;
}

