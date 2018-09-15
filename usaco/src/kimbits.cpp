/* Use the slash-star style comments or the system won't see your
   identification information */
/*
ID: yzylive1
TASK: kimbits
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

/*
 * F[M][N]: number of cases when at most N 1-bits within M slots
 * F[M][N] = F[M-1][N] + F[M-1][N-1]
 */

ifstream fin ("kimbits.in");
ofstream fout ("kimbits.out");

unsigned N, L, I;
unsigned F[40][40] = {0};

int main() {
    fin >> N >> L >> I;

    for (unsigned i = 1; i <= N; i++) {
        F[1][i] = 2; // 0 or 1
    }
    for (unsigned i = 1; i <= N; i++) {
        F[i][0] = 1;
        F[i][1] = i + 1; // all 0 or single 1
    }

    for (unsigned i = 2; i <= N; i++) {
        for (unsigned j = 2; j <= N; j++) {
            F[i][j] = F[i - 1][j] + F[i - 1][j - 1];
        }
    }

    // withBit -> lowerPart, withoutBit -> higherPart
    string result = "";
    unsigned restBit = L;
    for (unsigned i = N; i >= 2; i--) {
        if (restBit == 0) {
            result += "0";
            continue;
        }
        unsigned withBit = F[i - 1][restBit - 1];
        unsigned withOutBit = F[i - 1][restBit];
        // cout << I << " " << i << " " << restBit << " " << withBit << " " << withOutBit << endl;
        if (withOutBit < I) {
            // answer falls in higher part, append one
            I -= withOutBit;
            restBit--;
            result += "1";
        } else {
            result += "0";
        }
    }
    if (I == 1) result += "0";
    else result += "1";

    fout << result << endl;

    return 0;
}

