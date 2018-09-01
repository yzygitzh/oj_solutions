/* Use the slash-star style comments or the system won't see your
   identification information */
/*
ID: yzylive1
TASK: numtri
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

using namespace std;

int tri[1010][1010] = {0};

int main() {
    ofstream fout ("numtri.out");
    ifstream fin ("numtri.in");

    int R;
    fin >> R;
    for (int i = 1; i <= R; i++) {
        for (int j = 0; j < i; j++) {
            fin >> tri[i - 1][j];
        }
    }

    for (int i = R - 1; i >= 0; i--) {
        for (int j = 0; j <= i; j++) {
            int tmp1 = tri[i + 1][j];
            int tmp2 = tri[i + 1][j + 1];
            int maxTmp = tmp1 > tmp2 ? tmp1 : tmp2;
            tri[i][j] += maxTmp;
        }
    }

    fout << tri[0][0] << endl;

    return 0;
}

