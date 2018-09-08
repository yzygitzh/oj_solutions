/* Use the slash-star style comments or the system won't see your
   identification information */
/*
ID: yzylive1
TASK: concom
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

ifstream fin ("concom.in");
ofstream fout ("concom.out");

/*
 * DFS until fixed point
 * Walk through an edge A->B iff. start point BECOMES controlling A
 */

int control[110][110];
int totalControl[110];
int visited[110][110];
set<int> domSet;

void DFS(int currPoint, int startPoint) {
    for (int i = 1; i <= 100; i++) {
        if (i != currPoint && i != startPoint && control[currPoint][i]) {
            int before = totalControl[i];
            if (!visited[currPoint][i]) {
                totalControl[i] += control[currPoint][i];
                visited[currPoint][i] = 1;
            }
            int after = totalControl[i];
            // cout << before << " " << after << " " << endl;
            // cout << currPoint << " " << i << " " << totalControl[i] << endl;
            if (after > before && after > 50) {
                // cout << i << endl;
                domSet.insert(i);
                DFS(i, startPoint);
            }
        }
    }
}

int main() {
    int N;
    fin >> N;
    int c1, c2, p;
    for (int i = 0; i < N; i++) {
        fin >> c1 >> c2 >> p;
        control[c1][c2] = p;
    }
    for (int i = 1; i <= 100; i++) {
        for (int j = 0; j < 110; j++) {
            totalControl[j] = 0;
            for (int k = 0; k < 110; k++) {
                visited[j][k] = 0;
            }
        }
        domSet.clear();

        DFS(i, i);
        for (set<int>::iterator itr = domSet.begin();
             itr != domSet.end(); ++itr) {
            if (totalControl[*itr] > 50) fout << i << " " << *itr << endl;
        }
    }
    return 0;
}

