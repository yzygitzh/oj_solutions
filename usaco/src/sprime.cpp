/* Use the slash-star style comments or the system won't see your
   identification information */
/*
ID: yzylive1
TASK: sprime
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

set<int> superPrimeSet;
int N;
char genBuf[10];

bool isPrime(int x) {
    if (x <= 1) {
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

void genSuperPrime(int idx) {
    int num;
    if (idx == N) {
        sscanf(genBuf, "%d", &num);
        superPrimeSet.insert(num);
    } else {
        for (int i = 0; i <= 9; i++) {
            genBuf[idx] = '0' + i;
            genBuf[idx + 1] = '\0';
            sscanf(genBuf, "%d", &num);
            if (isPrime(num)) genSuperPrime(idx + 1);
        }
    }
}

int main() {
    ofstream fout ("sprime.out");
    ifstream fin ("sprime.in");

    fin >> N;
    genSuperPrime(0);

    for (set<int>::iterator itr = superPrimeSet.begin();
         itr != superPrimeSet.end(); ++itr) {
        fout << *itr << endl;
    }

    return 0;
}

