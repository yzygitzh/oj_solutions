/* Use the slash-star style comments or the system won't see your
   identification information */
/*
ID: yzylive1
TASK: picture
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
#include <utility>
#include <bitset>

#pragma pack(1)
using namespace std;

ifstream fin ("picture.in");
ofstream fout ("picture.out");

/*
 * Line sweeping
 */

int N;
set<int> xVals, yVals;
map<int, int> xVal2Idx, yVal2Idx;
vector<int> xValVec, yValVec;

map<int, int> xStack, yStack;

class Line {
public:
    int low, high, level;
    bool isStart;
    Line (int _low, int _high, int _level, bool _isStart)
        : low(_low), high(_high), level(_level), isStart(_isStart) {}
    bool operator< (const Line &l) const {
        if (level != l.level) return level < l.level;
        if (isStart != l.isStart) return isStart;
        if (low != l.low) return low < l.low;
        return high < l.high;
    }
};
vector<Line> horizon, vertical;
int perimeter = 0;

int main() {
    fin >> N;
    for (int i = 0; i < N; i++) {
        int lx, ly, ux, uy;
        fin >> lx >> ly >> ux >> uy;
        xVals.insert(lx);
        xVals.insert(ux);
        yVals.insert(ly);
        yVals.insert(uy);
        horizon.push_back(Line(lx, ux, ly, true));
        horizon.push_back(Line(lx, ux, uy, false));
        vertical.push_back(Line(ly, uy, lx, true));
        vertical.push_back(Line(ly, uy, ux, false));
    }
    sort(horizon.begin(), horizon.end());
    sort(vertical.begin(), vertical.end());
    int idx = 0;
    for (set<int>::iterator itr = xVals.begin();
         itr != xVals.end(); ++itr) {
        xValVec.push_back(*itr);
        xVal2Idx[*itr] = idx++;
        xStack[*itr] = 0;
    }
    idx = 0;
    for (set<int>::iterator itr = yVals.begin();
         itr != yVals.end(); ++itr) {
        yValVec.push_back(*itr);
        yVal2Idx[*itr] = idx++;
        yStack[*itr] = 0;
    }

    for (vector<Line>::iterator itr = horizon.begin();
         itr != horizon.end(); ++itr) {
        int low = itr->low;
        int high = itr->high;
        int lowIdx = xVal2Idx[low], highIdx = xVal2Idx[high];
        while (lowIdx < highIdx) {
            if (itr->isStart) {
                if (!xStack[lowIdx]++) {
                    perimeter += xValVec[lowIdx + 1] - xValVec[lowIdx];
                }
            } else {
                if (!--xStack[lowIdx]) {
                    perimeter += xValVec[lowIdx + 1] - xValVec[lowIdx];
                }
            }
            lowIdx++;
        }
    }

    for (vector<Line>::iterator itr = vertical.begin();
         itr != vertical.end(); ++itr) {
        int low = itr->low;
        int high = itr->high;
        int lowIdx = yVal2Idx[low], highIdx = yVal2Idx[high];
        while (lowIdx < highIdx) {
            if (itr->isStart) {
                if (!yStack[lowIdx]++) {
                    perimeter += yValVec[lowIdx + 1] - yValVec[lowIdx];
                }
            } else {
                if (!--yStack[lowIdx]) {
                    perimeter += yValVec[lowIdx + 1] - yValVec[lowIdx];
                }
            }
            lowIdx++;
        }
    }

    fout << perimeter << endl;

    return 0;
}
