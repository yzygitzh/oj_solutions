/* Use the slash-star style comments or the system won't see your
   identification information */
/*
ID: yzylive1
TASK: inflate
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

ifstream fin ("inflate.in");
ofstream fout ("inflate.out");

/*
 * F[M][N]: maximum probScore get within M time with first N problems
 * F[M][N] = max(F[M][N-1], F[M-time(N)][N] + probScore(N))
 *
 * reuse 2nd dim: F[1][M] = max(F[0][M], F[1][M-time(N)] + probScore(N))
 */

int M, N;
int probScore[10010], probTime[10010];

int F[2][10010] = {0}; // within 0 problem, only get 0 probScore

int main() {
    fin >> M >> N;
    for (int i = 0; i < N; i++) {
        fin >> probScore[i] >> probTime[i];
    }

    for (int i = 0; i <= N; i++) {
        for (int j = 0; j <= M; j++) {
            F[1][j] = F[0][j];
            if (j - probTime[i] >= 0 && F[1][j - probTime[i]] + probScore[i] > F[0][j]) {
                F[1][j] = F[1][j - probTime[i]] + probScore[i];
            }
        }
        memcpy(F[0], F[1], sizeof(F[0]));
    }

    fout << F[0][M] << endl;

    return 0;
}

