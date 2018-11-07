/* Use the slash-star style comments or the system won't see your
   identification information */
/*
ID: yzylive1
TASK: milk4
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

using namespace std;

/*
 * Use DFSID and DP
 * F[Q] = F[Q-pails(1)] || F[Q-pails(2)] ...
 */

ifstream fin ("milk4.in");
ofstream fout ("milk4.out");

int Q, P, N;
int pails[110];
vector<int> pailSet;
vector<int> ans;
unsigned char F[20010] = {0};
bool ansFound = false;

bool validate() {
    memset(F, 0, sizeof(F));
    // cout << "HHH" << endl;
    for (vector<int>::iterator itr = pailSet.begin();
         itr != pailSet.end(); ++itr) {
        // cout << (int)*itr << " ";
        F[*itr] = 1;
    }
    // cout << endl;
    for (int i = 1; i <= Q; i++) {
        for (vector<int>::iterator itr = pailSet.begin();
             itr != pailSet.end(); ++itr) {
            int q = i - *itr;
            if (q > 0) {
                F[i] |= F[q];
            }
        }
    }
    return (int)F[Q] != 0;
}

void DFSID(int p, int rest) {
    if (rest == 0) {
        if (validate()) {
            ansFound = true;
            ans = pailSet;
        }
    } else {
        for (int i = p; i <= P && !ansFound; i++) {
            pailSet.push_back(pails[i]);
            DFSID(i + 1, rest - 1);
            pailSet.pop_back();
        }
    }
}

int main() {
    fin >> Q >> P;
    N = P;
    for (int i = 1; i <= P; i++) {
        fin >> pails[i];
    }
    sort(pails + 1, pails + P + 1);

    for (int i = 1; i <= P; i++) {
        DFSID(1, i);
    }

    fout << ans.size();
    for (vector<int>::iterator itr = ans.begin();
         itr != ans.end(); ++itr) {
        fout << " " << *itr;
    }
    fout << endl;

    return 0;
}
