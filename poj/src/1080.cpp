/*
 * POJ 1080 - Human Gene Functions
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

int score[110][110];
int match[128][128] = {0};

int main() {
    match['A']['A'] = match['C']['C'] = match['G']['G'] = match['T']['T'] = 5;
    match['A']['C'] = match['C']['A'] = match['A']['T'] = match['T']['A'] =
    match[' ']['T'] = match['T'][' '] = -1;
    match['A']['G'] = match['G']['A'] = match['C']['T'] = match['T']['C'] = 
    match['G']['T'] = match['T']['G'] = match[' ']['G'] = match['G'][' '] = -2;
    match['C']['G'] = match['G']['C'] = match[' ']['A'] = match['A'][' '] = -3;
    match[' ']['C'] = match['C'][' '] = -4;

    int caseNum;
    cin >> caseNum;
    while (caseNum--) {
        memset(score, 0, sizeof(score));
        int gene1Len, gene2Len;
        string gene1, gene2;
        cin >> gene1Len >> gene1 >> gene2Len >> gene2;
        for (int i = 0; i <= gene1Len; i++) {
            for (int j = 0; j <= gene2Len; j++) {
                if (i != 0 || j != 0) {
                    score[i][j] = (1 << 31);
                    if (i != 0) {
                        score[i][j] = max(score[i][j],
                                          score[i - 1][j] + match[gene1[i - 1]][' ']);
                    }
                    if (j != 0) {
                        score[i][j] = max(score[i][j],
                                          score[i][j - 1] + match[gene2[j - 1]][' ']);
                    }
                    if (i != 0 && j != 0) {
                        score[i][j] = max(score[i][j],
                                          score[i - 1][j - 1] + match[gene1[i - 1]][gene2[j - 1]]);
                    }
                }
            }
        }
        cout << score[gene1Len][gene2Len] << endl;
    }
    return 0;
}

