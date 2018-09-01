/* Use the slash-star style comments or the system won't see your
   identification information */
/*
ID: yzylive1
TASK: pprime
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

set<int> primePalinSet;
int a, b;
char genBuf[10];

bool isSpecialPrime(int x) {
    if (x < a || x > b) {
        return false;
    } else {
        for (int i = 2; i * i <= x; i++) {
            if (!(x % i)) {
                return false;
            }
        }
        return true;
    }
}

void genPrimePalin(int len, int idx) {
    if (idx < 0) {
        for (int i = len / 2; i < len; i++) {
            genBuf[i] = genBuf[len - i - 1];
        }
        genBuf[len] = '\0';
        int palin;
        sscanf(genBuf, "%d", &palin);
        // cout << palin << endl;
        if (isSpecialPrime(palin)) primePalinSet.insert(palin);
        // cout << isSpecialPrime(palin) << endl;
    } else {
        for (int i = 0; i <= 9; i++) {
            genBuf[idx] = '0' + i;
            genPrimePalin(len, idx - 1);
        }
    }
}

int main() {
    ofstream fout ("pprime.out");
    ifstream fin ("pprime.in");

    fin >> a >> b;
    int maxLen = 0, tmpB = b;
    while (tmpB) {
        maxLen++;
        tmpB /= 10;
    }
    for (int i = 1; i <= maxLen; i++) {
        genPrimePalin(i, (i - 1) / 2);
    }

    for (set<int>::iterator itr = primePalinSet.begin();
         itr != primePalinSet.end(); ++itr) {
        fout << *itr << endl;
    }

    return 0;
}

