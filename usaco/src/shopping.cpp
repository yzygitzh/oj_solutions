/* Use the slash-star style comments or the system won't see your
   identification information */
/*
ID: yzylive1
TASK: shopping
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

ifstream fin ("shopping.in");
ofstream fout ("shopping.out");

/*
 * Note there are at most 5 number of products and
 * 10 offers (including single product)
 * F[A][B][C][D][E][N]: money used in purchasing A-E
 * number of products using first N type of offers
 */

int S, B;
int offerSize[100];
int offerCost[100];
map<int, int> pId;
int pCount = 0;
int offerNum[100][6];
int products[6];
int target[6];
int F[6][6][6][6][6][100] = {0};
int vis[6][6][6][6][6][100] = {0};

int DFS(int A, int B, int C, int D, int E, int N) {
    // cout << "DFS " << A << " " << B << " " << C << " " << D << " " << E << " " << N << endl;
    // cout << "entering" << endl;
    if (A < 0 || B < 0 || C < 0 || D < 0 || E < 0 || N < 0) return 100000000;
    if (A == 0 && B == 0 && C == 0 && D == 0 && E == 0) return 0;
    if (vis[A][B][C][D][E][N]) return F[A][B][C][D][E][N];
    // try use first N - 1
    int cost1 = DFS(A, B, C, D, E, N-1);
    // try use first N
    int cost2 = DFS(A-offerNum[N][0], B-offerNum[N][1], C-offerNum[N][2],
                    D-offerNum[N][3], E-offerNum[N][4], N) + offerCost[N];
    // cout << "DFS " << A << " " << B << " " << C << " " << D << " " << E << " " << N << endl;
    // cout << "cost1 " << cost1 << " cost2 " << cost2 << " offerCost " << offerCost[N] << endl;
    F[A][B][C][D][E][N] = cost1 < cost2 ? cost1 : cost2;
    vis[A][B][C][D][E][N] = 1;
    return F[A][B][C][D][E][N];
}

int main() {
    fin >> S;
    for (int i = 0; i < S; i++) {
        fin >> offerSize[i];
        for (int j = 0; j < offerSize[i]; j++) {
            int rawId, count;
            fin >> rawId >> count;
            if (!pId[rawId]) {
                pId[rawId] = ++pCount;
            }
            offerNum[i][pId[rawId] - 1] = count;
        }
        fin >> offerCost[i];
        // cout << "cost " << offerCost[i] << endl;
    }
    
    fin >> B;
    if (S == 0 && B == 0) {
        fout << 0 << endl;
        return 0;
    }
    for (int i = 0; i < B; i++) {
        // cout << "i " << i << " S " << S << endl;
        int c, k, p;
        fin >> c >> k >> p;
        if (!pId[c]) {
            pId[c] = ++pCount;
            // cout << "HI " << pId[c] << endl;
        }
        target[pId[c] - 1] = k;
        products[pId[c] - 1] = p;
        offerSize[S + pId[c] - 1] = 1;
        offerCost[S + pId[c] - 1] = p;
        offerNum[S + pId[c] - 1][pId[c] - 1] = 1;
    }
    // make unavailable products cost infinite
    for (int i = 0; i < pCount; i++) {
        if (offerSize[S + i] == 0) {
            offerCost[S + i] = 100000000;
            offerNum[S + i][i] = 1;
        }
    }
    
    /*
    cout << "S " << S << endl;
    cout << "B " << B << endl;
    for (int i = 0; i < S + pCount; i++) {
        cout << offerSize[i] << " ";
        for (int j = 0; j < 5; j++) {
            cout << offerNum[i][j] << " ";
        }
        cout << offerCost[i] << endl;
    }
    */

    int minCost = DFS(target[0], target[1], target[2], target[3], target[4], S + pCount - 1);
    fout << minCost << endl;

    return 0;
}

