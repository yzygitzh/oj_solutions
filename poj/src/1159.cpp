/*
 * POJ 1159 - Palindrome
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

int minInsert[5000][3] = {0};

int main() {
    int seqLen;
    cin >> seqLen;
    string seq;
    cin >> seq;
    // start from length-2 substring
    for (int len = 2; len <= seqLen; len++) {
        for (int j = 0; j + len <= seqLen; j++) {
            minInsert[j][len % 3] = seqLen * 2;
            // try left
            minInsert[j][len % 3] = min(minInsert[j][len % 3],
                                        minInsert[j][(len - 1) % 3] + 1);
            // try right
            minInsert[j][len % 3] = min(minInsert[j][len % 3],
                                        minInsert[j + 1][(len - 1) % 3] + 1);
            // try expand
            if (seq[j] == seq[j + len - 1]) {
                minInsert[j][len % 3] = min(minInsert[j][len % 3],
                                            minInsert[j + 1][(len - 2) % 3]);
            }
        }
    }
    cout << minInsert[0][seqLen % 3] << endl;

    return 0;
}

