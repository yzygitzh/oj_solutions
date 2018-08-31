/* Use the slash-star style comments or the system won't see your
   identification information */
/*
ID: yzylive1
TASK: ariprog
LANG: C++
*/
/* LANG can be C++20 or C++14 for those more recent releases */
#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include <cstring>
#include <set>
#include <string>

using namespace std;

/*
 * Search in bisqList only
 */

int N, M;
int isBisq[125010] = {0};
int bisqList[125010] = {0};
int bisqNum = 0;

void genBisq() {
    for (int i = 0; i <= M; i++) {
        for (int j = i; j <= M; j++) {
            isBisq[i * i + j * j] = 1;
        }
    }
    for (int i = 0; i <= M * M * 2; i++) {
        if (isBisq[i]) bisqList[bisqNum++] = i;
    }
}

class SeqPara {
public:
    int a;
    int b;
    SeqPara(int _a, int _b): a(_a), b(_b) {}
    bool operator<(const SeqPara &p) {
        if (this->b == p.b) {
            return this->a < p.a;
        } else {
            return this->b < p.b;
        }
    }
};

int main() {
    ofstream fout ("ariprog.out");
    ifstream fin ("ariprog.in");

    fin >> N >> M;

    genBisq();
    /*int bisqNum = 0;
    for (int i = 0; i < M*M*2; i++) {
        if (isBisq[i]) bisqNum++;
        if (isBisq[i]) cout << i << " " << nextBisq[i] << endl;
    }*/

    int seqLen = 0, seqCnt = 0;
    long loopCnt = 0;
    vector<SeqPara> result;

    // b: which bisq choose for N
    // a: which bisq choose for start
    for (int aI = 0; aI + N - 1 < bisqNum; aI++) {
        for (int bI = aI + 1;
             bisqList[aI] + (bisqList[bI] - bisqList[aI]) * (N - 1) <= bisqList[bisqNum - 1];
             bI++) {
            int a = bisqList[aI];
            int b = bisqList[bI] - bisqList[aI];
            // cout << a << " " << b << endl;
            seqLen = 2;
            for (int i = 2; i < N; i++) {
                loopCnt += 1;
                // if (a == 1 && b == 4) cout << a+i*b << " " << isBisq[a + i * b] << endl;
                if (isBisq[a + b * i]) {
                    seqLen++;
                } else {
                    break;
                }
            }
            if (seqLen == N) {
                // fout << a << " " << b << endl;
                result.push_back(SeqPara(a, b));
                seqCnt += 1;
            }
        }
    }
    sort(result.begin(), result.end());

    // cout << loopCnt << endl;

    if (!seqCnt) {
        fout << "NONE" << endl;
    } else {
        for (int i = 0; i < seqCnt; i++) {
            fout << result[i].a << " " << result[i].b << endl;
        }
    }

    return 0;
}

