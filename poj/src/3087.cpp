/*
 * POJ 3087 - Shuffle'm Up
 *
 * Shuffle can be seen as one (or sometimes two) cycle transformations
 * i.e. total state is 2 * C.
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

