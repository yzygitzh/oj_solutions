/*
 * POJ 3267 - The Cow Lexicon
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

string msg;
vector<string> dict;
int dictLen, msgLen;
int minCut[310] = {0}; // minimum cut needed for first n characters

int main() {
    cin >> dictLen >> msgLen;
    cin >> msg;
    for (int i = 0; i < dictLen; i++) {
        string word;
        cin >> word;
        dict.push_back(word);
    }
    for (int i = 1; i <= msgLen; i++) {
        // drop current character
        minCut[i] = minCut[i - 1] + 1;
        // use current character, find minimum cut possible
        for (int j = 0; j < dictLen; j++) {
            string word = dict[j];
            int wordLen = word.length();
            // greedy match
            int wordIdx = wordLen - 1, msgIdx = i - 1;
            while (wordIdx >= 0 && msgIdx >= 0) {
                if (word[wordIdx] == msg[msgIdx]) {
                    wordIdx--;
                }
                msgIdx--;
            }
            if (wordIdx < 0) {
                minCut[i] = min(minCut[i], minCut[msgIdx + 1] + i - 1 - msgIdx - wordLen);
            }
        }
    }
    cout << minCut[msgLen] << endl;
    return 0;
}

