/*
 * POJ 1936 - All in All
 *
 */

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

bool isSubSeq(string &s1, string &s2) {
    int len1 = s1.length(), len2 = s2.length();
    int idx1 = 0, idx2 = 0;
    while (idx1 < len1 && idx2 < len2) {
        if (s1[idx1] == s2[idx2]) idx1++;
        idx2++;
    }
    return idx1 == len1;
}

int main() {
    string s1, s2;
    while (cin >> s1 >> s2) {
        if (isSubSeq(s1, s2)) cout << "Yes" << endl;
        else cout << "No" << endl;
    }
    return 0;
}

