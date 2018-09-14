/* Use the slash-star style comments or the system won't see your
   identification information */
/*
ID: yzylive1
TASK: fact4
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

ifstream fin ("fact4.in");
ofstream fout ("fact4.out");

int main() {
    int N;
    fin >> N;

    int twoCount = 0, fiveCount = 0;
    for (int i = 1; i <= N; i++) {
        int tmpN = i;
        while (tmpN % 2 == 0) {
            tmpN /= 2;
            twoCount++;
        }
        while (tmpN % 5 == 0) {
            tmpN /= 5;
            fiveCount++;
        }
    }
    int tenCount = twoCount < fiveCount ? twoCount : fiveCount;
    twoCount = fiveCount = tenCount;

    int result = 1;
    for (int i = 1; i <= N; i++) {
        int tmpN = i;
        while (tmpN % 2 == 0 && twoCount) {
            tmpN /= 2;
            twoCount--;
        }
        while (tmpN % 5 == 0 && fiveCount) {
            tmpN /= 5;
            fiveCount--;
        }
        result *= tmpN;
        result %= 10;
    }

    fout << result << endl;

    return 0;
}

