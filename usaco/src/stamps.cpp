/* Use the slash-star style comments or the system won't see your
   identification information */
/*
ID: yzylive1
TASK: stamps
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

ifstream fin ("stamps.in");
ofstream fout ("stamps.out");

/*
 * F[N][M]: the minimum stamp number within which
 * M value can be constructed using first N types
 * of stamps.
 *
 * F[N][M] = min(F[N][M-stamp(N)] + 1, F[N-1][M])
 *
 * Reuse dim N
 * F[1][M] = min(F[1][M-stamp(N)] + 1, F[0][M])
 *
 * Mind overflow!
 */

int K, N;
int stamp[60];
unsigned char F[2][2000010];

int main() {
    fin >> K >> N;
    for (int i = 1; i <= N; i++) fin >> stamp[i];

    // first type only constructs n * itself
    for (int m = 1; m < 2000010; m++) {
        if ((m % stamp[1]) == 0 &&
            m / stamp[1] <= K) {
            F[1][m] = m / stamp[1];
        }
        else F[1][m] = K + 1;
    }
    // 0 value can be constructed by 0 stamps
    F[0][0] = F[1][0] = 0;

    for (int n = 2; n <= N; n++) {
        for (int m = 1; m < 2000010; m++) {
            F[n % 2][m] = F[(n - 1) % 2][m];
            if (m - stamp[n] >= 0 &&
                F[n % 2][m - stamp[n]] < K &&
                F[n % 2][m - stamp[n]] + 1 < F[n % 2][m]) {
                F[n % 2][m] = F[n % 2][m - stamp[n]] + 1;
            }
            // cout << n << " " << m << " " << (unsigned int)F[n % 2][m] << endl;
        }
        // break;
    }

    int count = 0;
    for (int m = 1; m < 2000010; m++) {
        if (F[N % 2][m] > K) {
            break;
        } else {
            count++;
        }
    }
    fout << count << endl;

    return 0;
}

