/* Use the slash-star style comments or the system won't see your
   identification information */
/*
ID: yzylive1
TASK: cowtour
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

/*
 * For two pastures A, B and edge E connecting them,
 * Dia(A-E-B) = max(Dia(A), Dia(B), len(E)+maxdis(E.A)+maxdis(E.B)) 
 */

ifstream fin ("cowtour.in");
ofstream fout ("cowtour.out");

const double MAX_DIS = 200000000.0;

int N;
double X[160], Y[160];
char mat[160][160];
double disMat[160][160];
double dia[160];
double maxDis[160];

double getDis(int i, int j) {
    return sqrt(pow(X[i] - X[j], 2) + pow(Y[i] - Y[j], 2));
}

void floyd() {
    // init disMat
    for (int i = 0; i < N; i++) {
        for (int j = i; j < N; j++) {
            if (i == j) {
                disMat[i][j] = 0.0;
            } else if (mat[i][j] == '1') {
                disMat[i][j] = disMat[j][i] = getDis(i, j);
            } else if (mat[i][j] == '0') {
                disMat[i][j] = disMat[j][i] = MAX_DIS;
            }
        }
    }
    // dyn prog
    for (int k = 0; k < N; k++) {
        for (int i = 0; i < N; i++) {
            for (int j = i + 1; j < N; j++) {
                double newDis = disMat[i][k] + disMat[k][j];
                if (newDis < disMat[i][j]) disMat[i][j] = disMat[j][i] = newDis;
            }
        }
    }
    // find diameter and maxDis
    for (int i = 0; i < N; i++) {
        dia[i] = 0.0;
        maxDis[i] = 0.0;
    }
    for (int i = 0; i < N; i++) {
        double maxDia = 0.0;
        for (int j = 0; j < N; j++) {
            if (disMat[i][j] != MAX_DIS && maxDia < disMat[i][j]) {
                maxDia = disMat[i][j];
                // cout << i << " " << j << " " << disMat[i][j]  << endl;
            }
        }
        // current maxDia is maxDis for i
        maxDis[i] = maxDia;
        // update diameter for the same group
        for (int j = 0; j < N; j++) {
            if (disMat[i][j] != MAX_DIS && dia[j] < maxDia) {
                dia[j] = maxDia;
            }
        }
    }
}

double findEdge() {
    double minDia = MAX_DIS;
    // for each point pair with MAX_DIS, try connect them
    for (int i = 0; i < N; i++) {
        for (int j = i + 1; j < N; j++) {
            if (disMat[i][j] == MAX_DIS) {
                double maxDia = 0.0;
                double diaI = dia[i];
                double diaJ = dia[j];
                double diaEdge = maxDis[i] + maxDis[j] + getDis(i, j);
                if (diaI > maxDia) maxDia = diaI;
                if (diaJ > maxDia) maxDia = diaJ;
                if (diaEdge > maxDia) maxDia = diaEdge;
                if (maxDia < minDia) minDia = maxDia;
            }
        }
    }
    return minDia;
}

int main() {
    string matLine;
    fin >> N;
    for (int i = 0; i < N; i++) {
        fin >> X[i] >> Y[i];
    }
    for (int i = 0; i < N; i++) {
        fin >> matLine;
        memcpy(mat[i], matLine.c_str(), N);    
    }
    floyd();
    fout << fixed << setprecision(6) << findEdge() << endl;

    return 0;
}

