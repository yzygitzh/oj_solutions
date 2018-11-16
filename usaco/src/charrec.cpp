/* Use the slash-star style comments or the system won't see your
   identification information */
/*
ID: yzylive1
TASK: charrec
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

ifstream fin ("charrec.in");
ifstream fin_font ("font.in");
ofstream fout ("charrec.out");

/*
 * F[M]: minimum corruptions until M-th line
 * F[M] = max(F[M-19]+corrupt(missing),
 *            F[M-20]+corrupt(normal),
 *            F[M-21]+corrupt(duplicate))
 * Use bitset to save time
 */

int F[1210];
int prevF[1210];
char answer[1210];

int fontNum;
int inLineNum;

vector<bitset<20> > font[27];
vector<bitset<20> > inChar;

// O(8000)
int checkChar(vector<bitset<20> >& fc, vector<bitset<20> >& ic) {
    int minDiff = 1000000000;
    if (ic.size() == 19) {
        // missing, enumerate missing line
        for (int i = 0; i < 20; i++) {
            int fcIdx = 0, icIdx = 0;
            int diff = 0;
            for (int j = 0; j < 20; j++) {
                if (i != j) {
                    diff += (fc[fcIdx] ^ ic[icIdx]).count();
                    icIdx++;
                }
                fcIdx++;
            }
            if (minDiff > diff) minDiff = diff;
        }
    } else if (ic.size() == 20) {
        int diff = 0;
        for (int j = 0; j < 20; j++) {
            diff += (fc[j] ^ ic[j]).count();
        }
        if (minDiff > diff) minDiff = diff;
    } else if (ic.size() == 21) {
        // duplicating
        for (int i = 0; i < 21; i++) {
            int fcIdx = 0, icIdx = 0;
            int diff = 0;
            for (int j = 0; j < 21; j++) {
                if (i != j) {
                    diff += (fc[fcIdx] ^ ic[icIdx]).count();
                    fcIdx++;
                }
                icIdx++;
            }
            if (minDiff > diff) minDiff = diff;
        }
    }
    return minDiff;
}

int main() {
    fin_font >> fontNum;
    fontNum /= 20;
    for (int i = 0; i < fontNum; i++) {
        for (int j = 0; j < 20; j++) {
            string inLine;
            fin_font >> inLine;
            font[i].push_back(bitset<20>(inLine));
        }
    }
    fin >> inLineNum;
    for (int i = 0; i < inLineNum; i++) {
        string inLine;
        fin >> inLine;
        inChar.push_back(bitset<20>(inLine));
    }

    // init first F's
    for (int i = 0; i < 18; i++) {
        F[i] = 1000000000;
    }
    // init first guesses (19, 20, 21)
    for (int i = 18; i <= 20 && i < inLineNum; i++) {
        F[i] = 1000000000;
        vector<bitset<20> > tmpIC;
        for (int j = 0; j <= i; j++) tmpIC.push_back(inChar[j]);
        for (int j = 0; j < 27; j++) {
            int corrupt = checkChar(font[j], tmpIC);
            if (corrupt < F[i]) {
                F[i] = corrupt;
                prevF[i] = -1;
                if (corrupt <= 120) answer[i] = j == 0 ? ' ' : 'a' + j - 1;
                else answer[i] = '?';
            }
        }
    }

    for (int i = 21; i < inLineNum; i++) {
        F[i] = 1000000000;
        // try missing, normal and duplicate
        for (int j = 19; j <= 21; j++) {
            if (F[i - j] == 1000000000) continue;
            vector<bitset<20> > tmpIC;
            for (int k = i - j + 1; k <= i; k++) tmpIC.push_back(inChar[k]);
            for (int k = 0; k < 27; k++) {
                int corrupt = checkChar(font[k], tmpIC);
                if (corrupt + F[i - j] < F[i]) {
                    F[i] = corrupt + F[i - j];
                    prevF[i] = i - j;
                    if (corrupt <= 120) answer[i] = k == 0 ? ' ' : 'a' + k - 1;
                    else answer[i] = '?';
                }
            }
        }
    }

    vector<char> finalAns;
    int idx = inLineNum - 1;
    while (idx > 0) {
        // cout << idx << " " << answer[idx] << endl;
        finalAns.push_back(answer[idx]);
        idx = prevF[idx];
    }
    for (vector<char>::reverse_iterator itr = finalAns.rbegin();
         itr != finalAns.rend(); ++itr) {
        fout << *itr;
    }
    fout << endl;

    return 0;
}
