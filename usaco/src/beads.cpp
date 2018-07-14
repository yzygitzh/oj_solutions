/* Use the slash-star style comments or the system won't see your
   identification information */
/*
ID: yzylive1
TASK: beads
LANG: C++
*/
/* LANG can be C++11 or C++14 for those more recent releases */
#include <iostream>
#include <fstream>
#include <string>

using namespace std;

int main() {
    ofstream fout ("beads.out");
    ifstream fin ("beads.in");

    int N;
    fin >> N;
    string seq;
    fin >> seq;
    
    int maxLen = 0;
    for (int i = 0; i < N; i++) {
        int rightIdx = i;
        int leftIdx = (i - 1 + N) % N;
        char rightColor = 'w';
        char leftColor = 'w';
        int currLen = 0;

        // right expansion
        while (rightIdx != leftIdx) {
            if (seq[rightIdx] == 'r' || seq[rightIdx] == 'b') {
                if (rightColor == 'w') {
                    rightColor = seq[rightIdx];
                } else if (rightColor != seq[rightIdx]) {
                    break;
                }
            }
            rightIdx = (rightIdx + 1) % N;
            currLen += 1;
        }

        // left expansion
        while (rightIdx != leftIdx) {
            if (seq[leftIdx] == 'r' || seq[leftIdx] == 'b') {
                if (leftColor == 'w') {
                    leftColor = seq[leftIdx];
                } else if (leftColor != seq[leftIdx]) {
                    break;
                }
            }
            leftIdx = (leftIdx - 1 + N) % N;
            currLen += 1;
        }

        if (rightIdx == leftIdx && (seq[leftIdx] == 'w' || leftColor == 'w' || seq[leftIdx] == leftColor)) {
            currLen += 1;
        }

        if (currLen > maxLen) {
            maxLen = currLen;
        }
    }
    fout << maxLen << endl;

    return 0;
}
