/* Use the slash-star style comments or the system won't see your
   identification information */
/*
ID: yzylive1
TASK: nocows
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
 * F[N][K]: number of structures with N nodes within at most K depth
 * F[N][K] = F[N-2][K-1]*F[1][K-1] + F[N-4][K-1]*F[3][K-1] + ...
 */

int N, K;
int F[300][150] = {0};

int main() {
    ofstream fout ("nocows.out");
    ifstream fin ("nocows.in");

    fin >> N >> K;
    if (N % 2 == 0) {
        fout << 0 << endl;
        return 0;
    }

    // init all depth single node structures
    for (int i = 1; i <= K; i++) {
        F[1][i] = 1;
    }

    for (int i = 2; i <= K; i++) {
        for (int j = 3; j <= N; j += 2) {
            int sum = 0;
            // total j nodes, with k nodes for left structure
            for (int k = 1; k < j; k += 2) {
                sum += F[k][i - 1] * F[j - 1 - k][i - 1];
                sum %= 9901;
            }
            F[j][i] = sum;
        }
    }

    fout << (F[N][K] + 9901 - F[N][K - 1]) % 9901 << endl;

    return 0;
}

