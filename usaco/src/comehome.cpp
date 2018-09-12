/* Use the slash-star style comments or the system won't see your
   identification information */
/*
ID: yzylive1
TASK: comehome
LANG: C++
*/
/* LANG can be C++20 or C++14 for those more recent releases */
#include <iostream>
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

ifstream fin ("comehome.in");
ofstream fout ("comehome.out");

int P;
int mat[60][60];
set<int> cowSet;

int nid(char c) {
    if (c >= 'A' && c <= 'Z') return c - 'A';
    else if (c >= 'a' && c <= 'z') return c - 'a' + 26;
    return -1;
}

void floyd() {
    for (int k = 0; k < 60; k++) {
        for (int i = 0; i < 60; i++) {
            for (int j = i + 1; j < 60; j++) {
                int newDis = mat[i][k] + mat[k][j];
                if (newDis < mat[i][j]) {
                    mat[i][j] = mat[j][i] = newDis;
                }
            }
        }
    }
}

int main() {
    fin >> P;
    string edge;
    int dis;

    for (int i = 0; i < 60; i++) {
        for (int j = 0; j < 60; j++) {
            if (i == j) mat[i][j] = 0;
            else mat[i][j] = 1000000000;
        }
    }
    getline(fin, edge);
    for (int i = 0; i < P; i++) {
        getline(fin, edge);
        sscanf(edge.substr(4).c_str(), "%d", &dis);
        if (dis < mat[nid(edge[0])][nid(edge[2])]) {
            mat[nid(edge[0])][nid(edge[2])] = dis;
            mat[nid(edge[2])][nid(edge[0])] = dis;
        }
        if (edge[0] >= 'A' && edge[0] < 'Z') cowSet.insert(edge[0] - 'A');
        if (edge[2] >= 'A' && edge[2] < 'Z') cowSet.insert(edge[2] - 'A');
    }

    floyd();

    char fastCow;
    int fastDis = 1000000000;
    for (set<int>::iterator itr = cowSet.begin();
         itr != cowSet.end(); ++itr) {
        if (mat[*itr]['Z' - 'A'] < fastDis) {
            fastDis = mat[*itr]['Z' - 'A'];
            fastCow = 'A' + (char)(*itr);
        }
    }

    fout << fastCow << " " << fastDis << endl;

    return 0;
}

