/*
 * POJ 1850 - Code
 *
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

int C[30][30] = {0};

int calcCode(const string &word) {
    int wordLen = word.length();
    int code = 0;
    for (int i = 0; i < wordLen; i++) {
        if (i > 0 && word[i] <= word[i - 1]) {
            return 0;
        }
        int baseIdx = i == 0 ? 0 : word[i - 1] - 'a' + 1;
        for (int j = baseIdx; 'a' + j < word[i]; j++) {
            code += C[26 - j - 1][wordLen - i - 1];
        }
    }
    // add words shorter
    for (int i = 1; i < wordLen; i++) {
        code += C[26][i];
    }
    // add itself
    code += 1;
    return code;
}

void calcC() {
    // calculate composition, C[>=0][0] = 1, C[0][>0] = 0
    for (int i = 0; i <= 26; i++) {
        C[i][0] = 1;
    }
    for (int i = 1; i <= 26; i++) {
        for (int j = 1; j <= i; j++) {
            C[i][j] = C[i - 1][j] + C[i - 1][j - 1];
        }
    }
}

int main() {
    string word;
    cin >> word;
    calcC();
    cout << calcCode(word) << endl;
    return 0;
}

