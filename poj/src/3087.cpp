/*
 * POJ 3087 - Shuffle'm Up
 *
 * The problem is a out perfect shuffle.
 * The states are bounded by the multiplicative order of 2 (mod 2n + 1)
 * which can be proved is O(2n).
 *
 * If we know that 2^k=1 mod 2n+1, where k is the smallest cycle length of 1,
 * then we also know that p*2^k=p mod 2n-1, for any p!=1.
 * So even if p has a shorter cycle k', k' must divide k in order to fulfill this equivalence.
 * So the order is bounded by 1's cycle length, which is O(2n).
 */

#include <cstdio>
#include <cstdlib>
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

int main() {
    int caseNum, C;
    string s1, s2, s3;
    cin >> caseNum;
    for (int i = 0; i < caseNum; i++) {
        cin >> C;
        cin >> s1 >> s2 >> s3;
        string s12 = s1;
        s12 += s2;
        int tryNum, maxTry = 2 * C;
        for (tryNum = 1; tryNum <= maxTry; tryNum++) {
            string newS12;
            for (int k = 0; k < C; k++) {
                newS12 += s12[k + C];
                newS12 += s12[k];
            }
            s12 = newS12;
            if (s12 == s3) break;
        }
        cout << i + 1 << " ";
        if (tryNum > maxTry) {
            cout << -1;
        } else {
            cout << tryNum;
        }
        cout << endl;
    }
    return 0;
}

