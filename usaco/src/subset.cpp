/* Use the slash-star style comments or the system won't see your
   identification information */
/*
ID: yzylive1
TASK: subset
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
 * F[N][M] = F[N-1][M] + F[N-1][M-N]
 * where F[N][M] means ways to sum to M in first N numbers
 */
long long F[40][1000];

int main() {
    ofstream fout ("subset.out");
    ifstream fin ("subset.in");

    int N, M;
    fin >> N;
    M = N * (N + 1) / 2;

    if (M % 2) {
        fout << 0 << endl;
        return 0;
    }

    M /= 2;

    for (int i = 1; i <= N; i++) {
        for (int j = 0; j <= M; j++) {
            if (i == 1) {
                if (j <= 1) F[i][j] = 1;
                else F[i][j] = 0;
            } else {
                F[i][j] = F[i - 1][j];
                if (j - i >= 0) F[i][j] += F[i - 1][j - i];
            }
            // cout << i << " " << j << " " << F[i][j] << endl;
        }
    }

    // answer should be F[N][M] / 2
    fout << F[N][M] / 2 << endl;

    return 0;
}

