/* Use the slash-star style comments or the system won't see your
   identification information */
/*
ID: yzylive1
TASK: money
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

ifstream fin ("money.in");
ofstream fout ("money.out");

/*
 * F[V][N]: ways to construct money N by first V coins
 * F[V][N] = F[V-1][N] + F[V][N-coin[V]]
 */

unsigned long long V, N;
unsigned long long coin[30];
unsigned long long F[30][10010] = {0};

int main() {
    fin >> V >> N;
    for (unsigned long long i = 0; i < V; i++) {
        fin >> coin[i + 1];
    }

    // zero money is always constructable
    for (unsigned long long i = 0; i <= V; i++) {
        F[i][0] = 1;
    }
    // zero coin never constructs money other than zero

    for (unsigned long long i = 1; i <= V; i++) {
        for (unsigned long long j = 1; j <= N; j++) {
            F[i][j] = F[i - 1][j];
            /* NOTE unsigned arithmetic doesn't support < 0 */
            if (j >= coin[i]) F[i][j] += F[i][j - coin[i]];
            // cout << i << " " << j << " " << F[i][j] << endl;
        }
    }

    fout << F[V][N] << endl;

    return 0;
}

