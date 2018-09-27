/* Use the slash-star style comments or the system won't see your
   identification information */
/*
ID: yzylive1
TASK: nuggets
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

ifstream fin ("nuggets.in");
ofstream fout ("nuggets.out");

/*
 * if gcd of numbers != 1, then no largest number that cannot be represented
 * if numbers contain 1, then all numbers are representable
 * else if gcd of numbers == 1, check 256 continuous 1 bits
 */

int N;
int num[20];
int F[300] = {0};
int maxNum = 0;
int minNum = 300;
int product = 1;

int gcd(int x, int y) {
    if (x < y) return gcd(y, x);
    if (x % y == 0) return y;
    return gcd(y, x % y);
}

int main() {
    fin >> N;
    for (int i = 0; i < N; i++) {
        fin >> num[i];
        if (num[i] > maxNum) maxNum = num[i];
        if (num[i] < minNum) minNum = num[i];
    }
    int allGcd = num[0];
    for (int i = 1; i < N; i++) {
        allGcd = gcd(allGcd, num[i]);
    }
    for (int i = 0; i < N; i++) {
        product *= num[i] / allGcd;
    }
    // cout << product << endl;

    if (allGcd > 1 || minNum == 1) {
        fout << 0 << endl;
        return 0;
    }

    int maxAnswer, currIdx = 1, contSum = 0, lastZero;
    F[0] = 1;
    while (currIdx < 2000000000) {
        F[currIdx % 300] = 0;
        for (int i = 0; i < N; i++) {
            // cout << num[i] << endl;
            if (currIdx - num[i] >= 0) F[currIdx % 300] |= F[(currIdx - num[i]) % 300];
        }

        if (F[currIdx % 300]) {
            contSum++;
        }
        else {
            // cout << currIdx << " " << lastZero << endl;
            lastZero = currIdx;
            contSum = 0;
        }
        if (contSum > 300) {
            // cout << currIdx << " " << product << " " << contSum << endl;
            break;
        }
        currIdx++;
    }
    fout << lastZero << endl;

    return 0;
}

