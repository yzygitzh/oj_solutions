/* Use the slash-star style comments or the system won't see your
   identification information */
/*
ID: yzylive1
TASK: ratios
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

ifstream fin ("ratios.in");
ofstream fout ("ratios.out");

int origin[3][3];
int target[3];
int tmpBuf[3];

int main() {
    for (int i = 0; i < 3; i++) {
        fin >> target[i];
    }
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            fin >> origin[i][j];
        }
    }

    int minMix = 300;
    int minI1, minI2, minI3, minRatio;
    for (int i1 = 0; i1 < 100; i1++) {
        for (int i2 = 0; i2 < 100; i2++) {
            for (int i3 = 0; i3 < 100; i3++) {
                memset(tmpBuf, 0, sizeof(tmpBuf));
                for (int j = 0; j < 3; j++) {
                    tmpBuf[j] += i1 * origin[0][j];
                    tmpBuf[j] += i2 * origin[1][j];
                    tmpBuf[j] += i3 * origin[2][j];
                }
                int ratio = 0;
                for (int j = 0; j < 3; j++) {
                    if (tmpBuf[j] && target[j]) {
                        ratio = tmpBuf[j] / target[j];
                        break;
                    }
                }

                // if ratio == 0 here, means no non-zero pairs
                // i.e. any non-zero ratio is wrong.
                // however, ratio should never not be zero
                // unless target is all zero
                if (!ratio && (target[0] || target[1] || target[2])) continue;

                if (ratio * target[0] == tmpBuf[0] &&
                    ratio * target[1] == tmpBuf[1] &&
                    ratio * target[2] == tmpBuf[2] &&
                    i1 + i2 + i3 < minMix) {
                    minMix = i1 + i2 + i3;
                    minI1 = i1;
                    minI2 = i2;
                    minI3 = i3;
                    minRatio = ratio;
                }
            }
        }
    }

    if (minMix == 300) {
        fout << "NONE" << endl;
    } else {
        fout << minI1 << " " << minI2 << " " << minI3 << " " << minRatio << endl;
    }

    return 0;
}

